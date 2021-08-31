#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include <sqlite_orm.h>
namespace slo = sqlite_orm;

struct Namespace {
	int id;
	std::string path;

	static inline auto make_table() {
		return slo::make_table("Namespace",
			slo::make_column("id", &Namespace::id, slo::primary_key()),
			slo::make_column("path", &Namespace::path)
		);
	}
};