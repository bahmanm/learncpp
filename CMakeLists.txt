cmake_minimum_required(VERSION 3.24)
project(05-basic-zip-file)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(ZLIB 1.2.10)
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
