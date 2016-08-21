cmake_minimum_required(VERSION 3.6)
project(Assignment_4)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB StanfordCPPlibSources StanfordCPPlib/*h StanfordCPPlib/*.cpp StanfordCPPlib/private/*.h)

set(SOURCE_FILES main.cpp Boggle.cpp Boggle.h ${StanfordCPPlibSources})
add_executable(Assignment_4 ${SOURCE_FILES} Boggle.cpp Boggle.h ${StanfordCPPlibSources})