#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <sqlite_orm.h>
namespace slo = sqlite_orm;

#include "Model/DefinitionSource.hpp"

enum class Ownership : uint8_t { Unique, Shared };
enum class Visibility : uint8_t { None, Private, Protected, Internal, Public };
enum class Mutability : uint8_t { Immutable, Mutable };
enum class Nullability : uint8_t { None, Nullable };
enum class StorageType : uint8_t { Static, Instance };
enum class CyclePossibility : uint8_t { Unknown, None, Some };
enum class InstanceDependency : uint8_t { Value, Reference }; // Independent, Interdependent
enum class ThreadShareability : uint8_t { Local, Global };

enum class Type : uint8_t { Namespace, Type, Function, Field, Property };

struct Symbol {
	int id;
	std::string_view name;
	Type type;
	decltype(DefinitionSource::id) definitionSourceId;
	std::optional<decltype(Symbol::id)> parentId;

	static inline auto make_table() {
		return slo::make_table("Symbol",
			slo::make_column("id", &Symbol::id, slo::primary_key()),
			slo::make_column("name", &Symbol::name),
			slo::make_column("type", &Symbol::type),
			slo::make_column("definitionSourceId", &Symbol::definitionSourceId),
			slo::make_column("parentId", &Symbol::parentId),

			slo::foreign_key(&Symbol::parentId).references(&Symbol::id),
			slo::foreign_key(&Symbol::definitionSourceId).references(&DefinitionSource::id)
		);
	}
};