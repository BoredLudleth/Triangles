cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable (trg src/main.cpp src/tools.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(trg_test src/triangle_test.cpp src/tools.cpp)
target_link_libraries(
  trg_test
  GTest::gtest_main
)