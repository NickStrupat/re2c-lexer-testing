cmake_minimum_required(VERSION 3.10)
project(re2c_lexer_testing)

set(CMAKE_CXX_STANDARD 17)

if (UNIX AND NOT APPLE)
	set(re2cPath "linux/re2c")
endif()
if (APPLE)
	set(re2cPath "macos/re2c")
endif()
if (WIN32)
	set(re2cPath "windows/re2c.exe")
endif()


add_custom_command(
		OUTPUT ${CMAKE_SOURCE_DIR}/lexer.cpp
		PRE_BUILD
		COMMAND ${CMAKE_SOURCE_DIR}/tools/re2c/${re2cPath} --utf-8 ${CMAKE_SOURCE_DIR}/lexer.re.cpp -o ${CMAKE_SOURCE_DIR}/lexer.cpp)

add_executable(re2c_lexer_testing main.cpp lexer.cpp)

#target_sources(re2c_lexer_testing PRIVATE lexer.cpp)
