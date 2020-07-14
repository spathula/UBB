#include "Test.h"
#include <assert.h>

/////////DOMAIN TESTS/////////

void test__get_title__returns_title(const Recording& test_recording)
{
	assert(test_recording.get_title().compare("test_title") == 0);
}

void test__get_location__returns_location(const Recording& test_recording)
{
	assert(test_recording.get_location().compare("test_location") == 0);
}

void test__get_timeOfCreation__returns_timeOfCreation(const Recording& test_recording)
{
	assert(test_recording.get_timeOfCreation().get_day() == 1);
}

void test_get_timeOfCreationYear__returns_timeOfCreation_year(const Recording& test_recording)
{
	assert(test_recording.get_timeOfCreation().get_year() == 2000);
}

void test__get_timesAccessed__returns_timesAccessed(const Recording& test_recording)
{
	assert(test_recording.get_timesAccessed() == 5);
}

void test__get_footagePreview__returns_footagePreview(const Recording& test_recording)
{
	assert(test_recording.get_footagePreview().compare("test_preview.mp15") == 0);
}

void test__set_location__validInput__sets_title(Recording& test_recording)
{
	test_recording.set_location("new_test_location");
	assert(test_recording.get_location().compare("new_test_location") == 0);
}

void test__set_timeOfCreation__validInput__sets_timeOfCreation(Recording& test_recording)
{
	test_recording.set_timeOfCreation(1, 2, 2000);
	assert(test_recording.get_timeOfCreation().get_month() == 2);
}

void test__set_timesAccessed__validInput__sets_timesAccessed(Recording& test_recording)
{
	test_recording.set_timesAccessed(10);
	assert(test_recording.get_timesAccessed() == 10);
}

void test__set_footagePreview__validInput__sets_footagePreview(Recording& test_recording)
{
	test_recording.set_footagePreview("new_test_preview.mp15");
	assert(test_recording.get_footagePreview().compare("new_test_preview.mp15") == 0);
}

void test_domain(Recording& test_recording)
{
	test__get_title__returns_title(test_recording);
	test__get_location__returns_location(test_recording);
	test__get_timeOfCreation__returns_timeOfCreation(test_recording);
	test_get_timeOfCreationYear__returns_timeOfCreation_year(test_recording);
	test__get_timesAccessed__returns_timesAccessed(test_recording);
	test__get_footagePreview__returns_footagePreview(test_recording);

	test__set_location__validInput__sets_title(test_recording);
	test__set_timeOfCreation__validInput__sets_timeOfCreation(test_recording);
	test__set_timesAccessed__validInput__sets_timesAccessed(test_recording);
	test__set_footagePreview__validInput__sets_footagePreview(test_recording);
}

/////////SERVICE TESTS/////////


void test__add_recording_service__validRecording__adds_recording(Service& test_service, const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	try { 
		test_service.add_recording_service(title, location, timeOfCreation, timesAccessed, footagePreview);
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void test__delete_recording_service__validRecording__deletes_recording(Service& test_service, const std::string& title)
{
	try {
		test_service.delete_recording_service(title);
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void test__update_recording_service__validRecording__updates_recording(Service& test_service, const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	test_service.add_recording_service(title, location, timeOfCreation, timesAccessed, footagePreview);
	try {
		test_service.update_recording_service(title, "New_Test_Location", Date(1, 2, 2020), 5, "New_Test_Preview");
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void test__add_recording_service__invalidRecording__returns_warning(Service& test_service, const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	try {
		test_service.add_recording_service(title, location, timeOfCreation, timesAccessed, footagePreview);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test__delete_recording_service__invalidRecording__returns_warning(Service& test_service, const std::string& title)
{
	try {
		test_service.delete_recording_service(title);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test__update_recording_service__invalidRecording__returns_warning(Service& test_service, const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	try {
		test_service.update_recording_service(title, "New_Test_Location", Date(1, 2, 2020), 5, "New_Test_Preview");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test__get_all_from_file_service__validInput__returns_all_recordings(Service& test_service)
{
	assert(test_service.get_all_from_file_service().size() == 1);
}

void test__next_recording_service__validInput__returns_next_recording(Service& test_service, const std::string& title)
{
	assert(test_service.next_recording_service().get_title().compare(title) == 0);
}

void test__list_location_service__validInput__returns_filtered_recordings(Service& test_service, const std::string& title, int timesAccessed)
{
	assert(test_service.list_location_service(title, timesAccessed).size() == 0);
}

void test_of_service(Service& test_service, Recording& test_recording, Recording& invalid_recording)
{
	test_service.save_file_path_service("test.txt");
	test__add_recording_service__validRecording__adds_recording(test_service, test_recording.get_title(), test_recording.get_location(), test_recording.get_timeOfCreation(), test_recording.get_timesAccessed(), test_recording.get_footagePreview());
	test__delete_recording_service__validRecording__deletes_recording(test_service, test_recording.get_title());
	test__update_recording_service__validRecording__updates_recording(test_service, test_recording.get_title(), test_recording.get_location(), test_recording.get_timeOfCreation(), test_recording.get_timesAccessed(), test_recording.get_footagePreview());
	test__add_recording_service__invalidRecording__returns_warning(test_service, invalid_recording.get_title(), invalid_recording.get_location(), invalid_recording.get_timeOfCreation(), invalid_recording.get_timesAccessed(), invalid_recording.get_footagePreview());
	test__delete_recording_service__invalidRecording__returns_warning(test_service, invalid_recording.get_title());
	test__update_recording_service__invalidRecording__returns_warning(test_service, invalid_recording.get_title(), invalid_recording.get_location(), invalid_recording.get_timeOfCreation(), invalid_recording.get_timesAccessed(), invalid_recording.get_footagePreview());
	test__get_all_from_file_service__validInput__returns_all_recordings(test_service);
	test__next_recording_service__validInput__returns_next_recording(test_service, test_recording.get_title());
	test__list_location_service__validInput__returns_filtered_recordings(test_service, test_recording.get_title(), 0);
}

/////////REPOSITORY TESTS/////////

void test__add_recording__invalidRecording__returns_warning(Repository& test_repository, Recording& test_recording)
{
	try {
		test_repository.add_recording(test_recording);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

}

void test__delete_recording__invalidRecording__returns_warning(Repository& test_repository, const std::string& title)
{
	try {
		test_repository.delete_recording(title);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test__delete_recording__validRecording__deletes_recording(Repository& test_repository, const std::string& title)
{
	try {
		test_repository.delete_recording(title);
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void test__update_recording__invalidRecording__returns_warning(Repository& test_repository, Recording& test_recording)
{
	try {
		test_repository.update_recording(test_recording);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void test__update_recording__validRecording__updates_recording(Repository& test_repository, Recording& test_recording)
{
	Recording updated_recording{ test_recording.get_title(), "update_location", Date(4,20,2020), 69, "update_preview.mp47" };
	try {
		test_repository.update_recording(updated_recording);
		assert(true);
	}
	catch (...) {
		assert(false);
	}
}

void test_of_repository(Repository& test_repository, Recording& test_recording, Recording& test_recording2)
{
	test__add_recording__invalidRecording__returns_warning(test_repository, test_recording);
	test__delete_recording__invalidRecording__returns_warning(test_repository, test_recording2.get_title());
	test_repository.add_recording(test_recording2);
	test__delete_recording__validRecording__deletes_recording(test_repository, test_recording2.get_title());
	test__update_recording__invalidRecording__returns_warning(test_repository, test_recording2);
	test_repository.add_recording(test_recording2);
	test__update_recording__validRecording__updates_recording(test_repository, test_recording2);
}


void test_all()
{
	Recording test_recording{ "test_title", "test_location", Date(1, 1, 2000), 5, "test_preview.mp15" };
	Recording test_recording2{ "title_test", "location_test", Date(30,11,9999), 3, "preview_test.mp15" };
	Recording invalid_recording{ "", "" , Date(0,0,0), -1, "" };
	Repository test_repository{};
	mylist_CSV test_CSV{};
	mylist_HTML test_HTML{};
	Validate test_validator{};
	Service test_service{ test_repository, test_CSV, test_HTML, test_validator };
	test_domain(test_recording);
	std::cout << "DOMAIN TESTED\n";
	test_of_service(test_service, test_recording, invalid_recording);
	std::cout << "SERVICE TESTED\n";
	test_of_repository(test_repository, test_recording, test_recording2);
	std::cout << "REPOSITORY TESTED\n";
}