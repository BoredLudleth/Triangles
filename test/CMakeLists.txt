cmake_minimum_required(VERSION 3.0)

project("testing")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${INCLUDE_DIR})

add_executable(trg_test triangle_test.cpp ../src/tools.cpp)

target_link_libraries(trg_test GTest::gtest_main)

add_test(trg_gtest trg_test)