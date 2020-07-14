#include <iostream>
#pragma once

class Exception : public std::exception {

	virtual std::string throw_error() const throw() = 0;
};


class RepositoryException : public Exception {
public:
	std::string errors;

	std::string throw_error() const throw() override { return "Repository errors ->  " + errors + "\n"; }

	RepositoryException(const std::string errors) { this->errors = errors; }
};

class ValidationException : public Exception {
public:
	std::string errors;

	std::string throw_error() const throw() override { return "Validation errors ->  " + errors + "\n"; }

	ValidationException(const std::string errors) { this->errors = errors; }
};