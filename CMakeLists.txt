cmake_minimum_required(VERSION 3.24)
project(solve-polynomial-big-numbers)

set(CMAKE_CXX_STANDARD
  20)
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/cmake
  ${CMAKE_MODULE_PATH})

add_executable(${PROJECT_NAME}
  src/main.cpp)

find_package(GMP 6.2.0)
include_directories(${PROJECT_NAME}
  ${GMP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${GMP_LIBRARIES}
  ${GMPXX_LIBRARIES})
