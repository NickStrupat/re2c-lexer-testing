#ifndef UNESCAPE_HPP_UNCLUDED
#define UNESCAPE_HPP_UNCLUDED

#include <cstddef>
#include <type_traits>

enum class DecodedType : std::underlying_type<std::byte>::type {
	Raw,
	Unescaped1,
	Unescaped2,
	Unescaped4,
	Unescaped8,
	Invalid,
};

struct Unescaped {
	DecodedType decodedType;
	char32_t value;
	std::byte length;
};

Unescaped unescape(char const* YYCURSOR);

#endif