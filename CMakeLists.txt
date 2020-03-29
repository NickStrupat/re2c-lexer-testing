cmake_minimum_required(VERSION 3.15)
project(re2c_lexer_testing)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/lexer.cpp
            PRE_BUILD
            COMMAND ${CMAKE_SOURCE_DIR}/tools/re2c/windows/re2c.exe --utf-8 ${CMAKE_SOURCE_DIR}/lexer.re.cpp -o ${CMAKE_SOURCE_DIR}/lexer.cpp)
endif()

add_executable(re2c_lexer_testing main.cpp lexer.cpp)

#target_sources(re2c_lexer_testing PRIVATE lexer.cpp)