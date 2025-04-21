cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(modular_synth VERSION 0.1.0 LANGUAGES CXX C)

find_library(PORTAUDIO portaudio)
find_library(MATH_LIBRARY m)

add_executable(modular_synth src/main.c
                            src/main.h
                            src/osc.c
                            src/osc.h
                            src/vca.c
                            src/vca.h)

if(PORTAUDIO)
    target_link_libraries(modular_synth PRIVATE ${PORTAUDIO})
endif()
if(MATH_LIBRARY)
    target_link_libraries(modular_synth PUBLIC ${MATH_LIBRARY})
endif()
