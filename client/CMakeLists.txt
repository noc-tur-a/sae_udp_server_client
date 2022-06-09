cmake_minimum_required(VERSION 3.16)
project(client C)

set(CMAKE_C_STANDARD 99)

add_executable(client main.c ../errorCode.c ../errorCode.h ../sharedFunctions.c ../sharedFunctions.h clientFunctions.c clientFunctions.h)
target_link_libraries(client pthread)