cmake_minimum_required(VERSION 3.12)
project(TrackFitter)

# Essential ROOT configuration
find_package(ROOT REQUIRED COMPONENTS MathCore RIO)
include(${ROOT_USE_FILE})

# Enable C++17
set(CMAKE_CXX_STANDARD 17)

# Executable
add_executable(track_fitter
  src/main.cxx
  src/TrackFitter.cxx
)

# Link ROOT libraries
target_link_libraries(track_fitter 
  ROOT::Core 
  ROOT::MathCore 
  ROOT::RIO 
  ROOT::Gpad
)

# Include paths
target_include_directories(track_fitter PRIVATE include)