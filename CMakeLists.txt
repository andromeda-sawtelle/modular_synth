cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(modular_synth VERSION 0.1.0 LANGUAGES CXX C)

find_library(PORTAUDIO portaudio)

add_executable(modular_synth src/rack.cpp
                             src/modules.cpp
                             src/modules.hpp)

target_link_libraries(modular_synth PRIVATE ${PORTAUDIO})
