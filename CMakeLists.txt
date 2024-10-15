cmake_minimum_required(VERSION 3.0)

project(cache)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_TESTING "Build tests" ON)


include_directories(${INCLUDE_DIR})

add_executable (trg src/main.cpp src/tools.cpp)

add_executable(trg_gen src/trg_gen.cpp)

if(BUILD_TESTING)
  include(CTest)
  enable_testing()
  add_subdirectory(test/)
endif()
