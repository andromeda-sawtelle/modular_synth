cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(modular_synth VERSION 0.1.0 LANGUAGES CXX)

find_library(PORTAUDIO portaudio)

add_executable(modular_synth src/rack.cpp
                             src/modules.cpp
                             src/modules.hpp
                             src/osc.cpp
                             src/osc.hpp
                             src/audio.cpp
                             src/audio.hpp)

target_link_libraries(modular_synth PRIVATE ${PORTAUDIO})
