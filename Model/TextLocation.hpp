#pragma once

#include <string_view>

struct TextLocation {
	std::string_view text;
	int offset;
	int	line;
	int column;
};

struct TextFileLocation {
	std::string_view path;
	int offset;
	int	line;
	int column;
};

struct MetadataFileLocation {
	std::string_view path;
	int offset;
};