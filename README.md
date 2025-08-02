# 🧠 CERN Track Reconstruction Simulator  
*A Kalman Filter-based simulation using ROOT to model particle tracks through synthetic detector hits.*

---

## 🎯 Project Overview

This project simulates a simplified version of **particle track reconstruction**, inspired by workflows used at **CERN experiments** like ATLAS and CMS.  
It uses:

- **ROOT** for data modeling, visualization, and numerical tools  
- A hand-built **Kalman Filter** for estimating particle trajectories from noisy synthetic hits  
- A modular C++ structure for future extension (e.g., GNN integration or ROOT I/O support)

---

## 🚀 Why This Project?

High-energy physics experiments like those at the **LHC** produce vast amounts of hit data from detectors. Reconstructing the underlying particle trajectories from this data is computationally intensive.

This simulator is built to:

- Explore the **mathematical foundations** of tracking (starting with Kalman filtering)
- Practice using ROOT in real experimental-style workflows
- Serve as a foundation for **AI/GNN-assisted track reconstruction** research
- Build readiness for future contributions to CERN or LHC software stacks

---

## 🛠️ Technologies Used

- **ROOT**: `TCanvas`, `TF1`, `TGraph`, `TRandom`, `SMatrix`, and `TVectorD`
- **C++**: Core logic, memory management, data structures
- **CMake**: Cross-platform build system

---

## 🗂️ Project Structure

