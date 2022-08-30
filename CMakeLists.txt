cmake_minimum_required(VERSION 3.24)
project(04-format)
add_executable(${PROJECT_NAME} src/main.cpp)
find_package(fmt)
target_link_libraries(${PROJECT_NAME}
  fmt)
