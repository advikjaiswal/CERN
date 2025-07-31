#ifndef TRACK_FITTER_H
#define TRACK_FITTER_H

#include <vector>
#include <ROOT/RVec.hxx>
#include <Math/SVector.h>
#include <Math/SMatrix.h>
#include <TCanvas.h>

class TrackFitter {
public:
  // State vector: [x, y, tx, ty, q/p]
  using Vector5 = ROOT::Math::SVector<double, 5>;
  
  // Covariance matrices
  using Matrix5 = ROOT::Math::SMatrix<double, 5, 5>;
  using Matrix2 = ROOT::Math::SMatrix<double, 2, 2>;
  using Matrix25 = ROOT::Math::SMatrix<double, 2, 5>;
  using Vector2 = ROOT::Math::SVector<double, 2>;
  using Matrix52 = ROOT::Math::SMatrix<double, 5, 2>;

  void AddHit(double x, double y, double z);
  void Fit();
  void Draw();

private:
  std::vector<double> m_hitsX, m_hitsY, m_hitsZ;
  Vector5 m_state;    // Current state estimate
  Matrix5 m_cov;      // Covariance matrix
  TCanvas* m_canvas = nullptr;
};

#endif