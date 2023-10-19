
cmake_minimum_required(VERSION 3.6)
project(example)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/../)
message("binary dir" ${EXECUTABLE_OUTPUT_PATH})
add_executable(${PROJECT_NAME} example.c)