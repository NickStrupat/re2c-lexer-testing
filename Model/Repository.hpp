#pragma once

#include <string>

#include "sqlite_orm.h"
namespace slo = sqlite_orm;

#include "Model/Symbol.hpp"
#include "Model/Namespace.hpp"

struct Repository {
	slo::internal::storage_t<
		Symbol,
		Namespace
	> storage;

	Repository(std::string const & filename) : storage(
			slo::make_storage(filename,
				Symbol::make_table(),
				Namespace::make_table()
			)
		)
	) {}
};