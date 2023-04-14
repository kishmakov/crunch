cmake_minimum_required(VERSION 3.24)
project(crunch)

set(CMAKE_CXX_STANDARD 20)

add_executable(crunch main.cpp wallace.cpp wallace.h activation_functions.cpp activation_functions.h utilites.cpp utilites.h common.h network.cpp network.h)
