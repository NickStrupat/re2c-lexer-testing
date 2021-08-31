#pragma once

#include "Model/Repository.hpp"

class Listener {
	Repository & repository;
	Symbol const * current;
	Listener(Repository& repository, Symbol const * symbol) : repository(repository), current(symbol) {}

	void enterNamespace(Token const & identifier) {}
	void exitNamespace() {}

	void enterType(Token const & identifier, Token const & kind, Token const & visibility) {}
	void exitType() {}
};