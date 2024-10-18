find_package(GTest REQUIRED)

include_directories(${INCLUDE_DIR})

add_executable(trg_test triangle_test.cpp ${SOURCE_DIR}/tools.cpp)

target_link_libraries(trg_test GTest::gtest_main)

add_test(trg_gtest trg_test)

add_custom_command(TARGET trg_test
                   COMMENT "Run tests"
                   POST_BUILD 
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND ${CMAKE_CTEST_COMMAND})
