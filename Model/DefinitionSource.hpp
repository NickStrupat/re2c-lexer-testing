#pragma once

#include <cstdint>

//enum class DefinitionSourceType : uint8_t { Text, File, Metadata };

struct DefinitionSource {
	int id;
	std::string_view data;
	std::string_view path;
	int beginOffset;
	int	beginLine;
	int beginColumn;
	int endOffset;
	int	endLine;
	int endColumn;

	static inline auto make_table() {
		return slo::make_table("DefinitionSource",
			slo::make_column("id", &DefinitionSource::id, slo::primary_key()),
			slo::make_column("data", &DefinitionSource::data),
			slo::make_column("path", &DefinitionSource::path),
			slo::make_column("beginOffset", &DefinitionSource::beginOffset),
			slo::make_column("beginLine", &DefinitionSource::beginLine),
			slo::make_column("beginColumn", &DefinitionSource::beginColumn),
			slo::make_column("endOffset", &DefinitionSource::endOffset),
			slo::make_column("endLine", &DefinitionSource::endLine),
			slo::make_column("endColumn", &DefinitionSource::endColumn),

			slo::make_index("idx_DefinitionSource_path", &DefinitionSource::path)
		);
	}
};