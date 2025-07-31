import uproot
import torch

# Load a ROOT file (e.g., CMS OpenData)
file = uproot.open("track_data.root")
hits = file["events"].arrays(library="np")  # Convert to NumPy
hits_tensor = torch.tensor(hits)  # -> PyTorch