cmake_minimum_required(VERSION 3.6)
project(Assignment_4)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp random/random.h random/random.cpp random/private/randompatch.h Boggle.cpp Boggle.h strlib/strlib.cpp strlib/strlib.h)
add_executable(Assignment_4 ${SOURCE_FILES} random/random.cpp random/private/randompatch.h Boggle.cpp Boggle.h strlib/strlib.cpp strlib/strlib.h)