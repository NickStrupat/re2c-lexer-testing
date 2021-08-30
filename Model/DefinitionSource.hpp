#pragma once

struct DefinitionSource {
	~DefinitionSource() = 0;
};

struct TextSourceSpan : DefinitionSource {
	TextLocation begin;
	TextLocation end;
};