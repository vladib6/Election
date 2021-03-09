#pragma once
#include <exception>
#include "STRING.h"
class Generalexcep : std::exception {
private:
	STRING error;
public:
	Generalexcep(const char* msg) :error(msg) {}
	const char* what() const throw() {
		return error.getString();
	}
};
