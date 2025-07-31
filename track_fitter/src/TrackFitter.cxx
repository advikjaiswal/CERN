#include "TrackFitter.h"
#include <TGraph.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>

void TrackFitter::AddHit(double x, double y, double z) {
  m_hitsX.push_back(x);
  m_hitsY.push_back(y);
  m_hitsZ.push_back(z);
}

void TrackFitter::Fit() {
  std::cout << "Starting fit with " << m_hitsX.size() << " hits..." << std::endl;
  const int nHits = m_hitsX.size();
  if (nHits < 2) return;

  // Initialize with first hit
  m_state = Vector5(m_hitsX[0], m_hitsY[0], 0, 0, 0.1);
  m_cov = Matrix5(ROOT::Math::SMatrixIdentity());

  // Noise parameters
  const double Q = 1e-4;  // Process noise
  const double R = 0.01;  // Measurement noise

  for (int i = 1; i < nHits; ++i) {
    // Prediction step (constant velocity)
    double dz = m_hitsZ[i] - m_hitsZ[i-1];
    m_state[0] += m_state[2] * dz;  // x += tx*dz
    m_state[1] += m_state[3] * dz;  // y += ty*dz
    m_cov += Q * Matrix5(ROOT::Math::SMatrixIdentity());

    // --- FIXED MATRIX INITIALIZATION ---
    Matrix25 H;  // 2x5 measurement matrix (DO NOT initialize with value)
    H(0,0) = 1;  // Measures x
    H(1,1) = 1;  // Measures y

    Vector2 z(m_hitsX[i], m_hitsY[i]);  // Actual measurement
    Vector2 y = z - H * m_state;        // Innovation

    // --- FIXED MATRIX OPERATIONS ---
    Matrix2 S;
    ROOT::Math::AssignSym::Evaluate(S, H * m_cov * ROOT::Math::Transpose(H));
    S += R * Matrix2(ROOT::Math::SMatrixIdentity());

    int ifail = 0;
    Matrix2 S_inv = S.Inverse(ifail);
    if (ifail != 0) {
      std::cerr << "Matrix inversion failed!" << std::endl;
      continue;
    }

    Matrix52 K = m_cov * ROOT::Math::Transpose(H) * S_inv;

    m_state += K * y;  // Updates ALL state variables
    m_cov -= K * H * m_cov;
  }

  std::cout << "Fitted state:\n"
            << "  x = " << m_state[0] << "\n"
            << "  y = " << m_state[1] << "\n"
            << " tx = " << m_state[2] << "\n"
            << " ty = " << m_state[3] << "\n"
            << "q/p = " << m_state[4] << std::endl;
}

void TrackFitter::Draw() {
  std::cout << "[TrackFitter] Drawing canvas..." << std::endl;
  
  // Create canvas if it doesn't exist
  if (!m_canvas) {
    m_canvas = new TCanvas("c1", "Track Canvas", 800, 600);
  }
  
  m_canvas->cd();
  
  // Draw hits
  TGraph gr(m_hitsX.size(), m_hitsX.data(), m_hitsY.data());
  gr.SetMarkerStyle(20);
  gr.SetTitle("Track Hits;X [cm];Y [cm]");
  gr.Draw("AP");

  // Draw fitted line (only x direction for simplicity)
  TF1 f("fit", "[0] + [1]*x", -10, 10);
  f.SetParameters(m_state[0], m_state[2]);
  f.SetLineColor(kRed);
  f.Draw("same");

  // Force update
  m_canvas->Modified();
  m_canvas->Update();
  std::cout << "[TrackFitter] Canvas drawn successfully." << std::endl;
}