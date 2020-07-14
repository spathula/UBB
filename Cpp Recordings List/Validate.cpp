#include "Validate.h"


void Validate::validate_new_recording(const Recording& recording)
{
	std::string errors = "";

	if (recording.get_footagePreview().compare("") == 0)
		errors += "Invalid footage preview! \n";

	if (recording.get_location().compare("") == 0)
		errors += "Invalid location! \n";

	if (recording.get_timeOfCreation().get_day() < 1 || recording.get_timeOfCreation().get_day() > 31)
		errors += "Invalid day! \n";

	if (recording.get_timeOfCreation().get_month() < 1 || recording.get_timeOfCreation().get_month() > 12)
		errors += "Invalid month! \n";

	if (recording.get_timeOfCreation().get_year() < 1)
		errors += "Invalid year! \n";

	if (recording.get_timesAccessed() < 0)
		errors += "Invalid times accessed! \n";

	if (recording.get_title().compare("") == 0)
		errors += "Invalid title! \n";

	if (errors.size() > 0)
		throw ValidationException(errors);
}

void Validate::validate_deleted_recording(const std::string& title)
{
	std::string errors = "";

	if (title.compare("") == 0)
		errors += "Invalid title! \n";

	if (errors.size() > 0)
		throw ValidationException(errors);
}
