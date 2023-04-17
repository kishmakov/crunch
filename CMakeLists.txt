cmake_minimum_required(VERSION 3.24)
project(crunch)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/matplotplusplus/1.1.0_3/include)

add_executable(crunch main.cpp wallace.cpp wallace.h activation_functions.cpp activation_functions.h utilities.cpp utilities.h NetworkComputation.cpp NetworkComputation.h Case.cpp Case.h Weights.cpp Weights.h training.cpp training.h)

target_link_libraries(crunch /opt/homebrew/Cellar/matplotplusplus/1.1.0_3/lib/libmatplot.dylib)
