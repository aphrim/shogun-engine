cmake_minimum_required(VERSION 3.0)
project(Glad)

add_library(glad lib/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC lib/)
