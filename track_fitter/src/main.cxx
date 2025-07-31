#include <iostream>
#include "TrackFitter.h"
#include <TApplication.h>
#include <TSystem.h>
#include <TRandom.h>

void generate_hits(TrackFitter& fitter) {
  TRandom r;
  // Generate 20 synthetic hits
  for (int i = 0; i < 20; i++) {
    double z = i * 1.0;
    double x = 0.5 * z + r.Gaus(0, 0.1);  // Linear track + noise
    double y = 0.3 * z + r.Gaus(0, 0.1);
    fitter.AddHit(x, y, z);
  }
}

int main(int argc, char** argv) {
  // Configure ROOT to show all output
  gErrorIgnoreLevel = kPrint;  // Show even debug messages
  TApplication app("app", &argc, argv);

  TrackFitter fitter;
  generate_hits(fitter);

  std::cout << "=== FIT START ===" << std::endl;
  fitter.Fit();
  std::cout << "=== FIT COMPLETE ===" << std::endl;

  fitter.Draw();

  // Force-flush all buffers
  std::cout.flush();
  std::cerr.flush();
  gSystem->ProcessEvents();

  app.Run();
  return 0;
}                                           