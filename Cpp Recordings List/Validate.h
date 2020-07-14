#pragma once
#include "Repository.h"

class Validate {
public:
	Validate() {}

	void validate_new_recording(const Recording& recording);
	void validate_deleted_recording(const std::string& title);
};