cmake_minimum_required(VERSION 3.24)
project(crunch)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/matplotplusplus/1.1.0_3/include)

add_executable(crunch main.cpp wallace.cpp wallace.h network/activation_functions.cpp network/activation_functions.h utilities.cpp utilities.h NetworkComputation.cpp NetworkComputation.h Case.cpp Case.h Weights.cpp Weights.h training.cpp training.h Plotter.cpp Plotter.h network/Neuron.cpp network/Neuron.h)

target_link_libraries(crunch /opt/homebrew/Cellar/matplotplusplus/1.1.0_3/lib/libmatplot.dylib)
