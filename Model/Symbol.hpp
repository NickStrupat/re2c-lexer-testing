#pragma once

#include <cstddef>
#include <string>
#include <vector>
using namespace std;

#include <sqlite_orm.h>
namespace slo = sqlite_orm;

enum class Ownership : char unsigned { Unique, Shared };
enum class Visibility : char unsigned { None, Private, Protected, Internal, Public };
enum class Mutability : char unsigned { Immutable, Mutable };
enum class Nullability : char unsigned { None, Nullable };
enum class StorageType : char unsigned { Static, Instance };
enum class CyclePossibility : char unsigned { Unknown, None, Some };
enum class InstanceDependency : char unsigned { Value, Reference }; // Independent, Interdependent
enum class ThreadShareability : char unsigned { Local, Global };

template<typename TParent>
struct HasParent { TParent parent; };

template<typename TParent>
struct HasParent { TParent parent; };

template<typename TParent>
struct HasParent { TParent parent; };

struct Symbol : HasParent<optional<Symbol>>, HasChildren<Symbol>, HasDefinitionSource {};