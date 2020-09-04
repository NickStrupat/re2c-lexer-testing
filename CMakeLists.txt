cmake_minimum_required(VERSION 3.10)
project(re2c_lexer_testing)

set(CMAKE_CXX_STANDARD 20)

if (UNIX AND NOT APPLE)
	set(re2cPath "linux/re2c")
endif()
if (APPLE)
	set(re2cPath "macos/re2c")
endif()
if (WIN32)
	set(re2cPath "windows/re2c.exe")
endif()

include_directories(unilib/unilib)

add_library(unilib STATIC
	unilib/unilib/unicode.cpp
	unilib/unilib/uninorms.cpp
	unilib/unilib/unistrip.cpp
	unilib/unilib/utf16.cpp
	unilib/unilib/utf8.cpp
	unilib/unilib/version.cpp
)

add_custom_command(
		OUTPUT ${CMAKE_SOURCE_DIR}/lexer.cpp
		PRE_BUILD
		COMMAND ${CMAKE_SOURCE_DIR}/tools/re2c/${re2cPath} --utf-8 --encoding-policy fail ${CMAKE_SOURCE_DIR}/lexer.re.cpp -o ${CMAKE_SOURCE_DIR}/lexer.cpp)

#add_custom_command(
#		OUTPUT ${CMAKE_SOURCE_DIR}/Utf8UnicodeEscapeSequenceIterator.cpp
#		PRE_BUILD
#		COMMAND ${CMAKE_SOURCE_DIR}/tools/re2c/${re2cPath} --utf-8 --encoding-policy fail ${CMAKE_SOURCE_DIR}/Utf8UnicodeEscapeSequenceIterator.re.cpp -o ${CMAKE_SOURCE_DIR}/#Utf8UnicodeEscapeSequenceIterator.cpp)
#
#add_custom_command(
#		OUTPUT ${CMAKE_SOURCE_DIR}/unescape.cpp
#		PRE_BUILD
#		COMMAND ${CMAKE_SOURCE_DIR}/tools/re2c/${re2cPath} --utf-8 --encoding-policy fail ${CMAKE_SOURCE_DIR}/unescape.re.cpp -o ${CMAKE_SOURCE_DIR}/unescape.cpp)

add_executable(re2c_lexer_testing
	main.cpp
	lexer.cpp
	TokenIterator.cpp
	DentedTokenIterator.cpp
)

target_link_libraries(re2c_lexer_testing unilib)