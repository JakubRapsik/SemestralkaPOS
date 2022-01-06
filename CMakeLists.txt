cmake_minimum_required(VERSION 3.7)
project(SemestralkaServer C)

set(CMAKE_C_STANDARD 99)



add_executable(SemestralkaServer server.c hra.c hra.h)
target_link_libraries(SemestralkaServer pthread m)

