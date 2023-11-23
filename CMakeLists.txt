cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(sampler_test VERSION 0.1.0 LANGUAGES CXX C)

find_library(PORTAUDIO portaudio)

add_executable(sampler_test src/main.c)

target_link_libraries(sampler_test PRIVATE ${PORTAUDIO})