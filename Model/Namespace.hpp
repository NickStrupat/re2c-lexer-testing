#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include <sqlite_orm.h>
namespace slo = sqlite_orm;

struct Namespace {
	std::int64_t id;
	std::string path;
	std::vector<std::byte> hash;

	static inline auto make_table() {
		return slo::make_table("namespace",
			slo::make_column("id", &Namespace::id, slo::primary_key()),
			slo::make_column("path", &Namespace::path),
			slo::make_column("hash", &Namespace::hash)
		);
	}
};