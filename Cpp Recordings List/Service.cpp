#include "Service.h"
#include <assert.h>
#include <algorithm>
#include <Windows.h>

void Service::add_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{

	Recording new_recording{ title, location, timeOfCreation, timesAccessed, footagePreview };

	this->validator.validate_new_recording(new_recording);

	this->repository.add_recording(new_recording);

	std::unique_ptr<ActionAdd> new_action = std::make_unique<ActionAdd>(this->repository, new_recording);

	this->undoStack.push_back(std::move(new_action));

}

void Service::delete_recording_service(const std::string& title)
{
	this->validator.validate_deleted_recording(title);

	Recording deleted_recording = this->repository.delete_recording(title);

	std::unique_ptr<ActionRemove> new_action = std::make_unique<ActionRemove>(this->repository, deleted_recording);

	this->undoStack.push_back(std::move(new_action));
}

void Service::update_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	Recording updated_recording{ title, location, timeOfCreation, timesAccessed, footagePreview };

	this->validator.validate_new_recording(updated_recording);

	Recording old_recording = this->repository.update_recording(updated_recording);

	std::unique_ptr<ActionUpdate> new_action = std::make_unique<ActionUpdate>(this->repository, old_recording);

	this->undoStack.push_back(std::move(new_action));
}

void Service::save_file_path_service(const std::string& file_path)
{
	this->repository.save_file_path(file_path);
	this->my_CSV.save_file_path(file_path);
	this->my_HTML.save_file_path(file_path);
}

void Service::save_mylist_path_service(const std::string& mylist_path)
{
	if (mylist_path.substr(mylist_path.size() - 4) == ".csv")
	{
		this->mylist_extension = "csv";
		this->my_CSV.save_mylist_path_CSV(mylist_path);
	}
	else
	{
		this->mylist_extension = "html";
		this->my_HTML.save_mylist_path_HTML(mylist_path);
	}
}

std::vector<Recording> Service::get_all_from_file_service()
{
	return this->repository.get_all_from_file();
}

Recording Service::next_recording_service()
{
	return this->repository.next_recording();
}

void Service::save_recording_service(const std::string& title)
{
	this->validator.validate_deleted_recording(title);
	if (this->mylist_extension == "csv")
		this->my_CSV.save_recording(title);
	else
		this->my_HTML.save_recording(title);
}

std::vector<Recording> Service::list_location_service(const std::string& title, int timesAccessed)
{
	std::vector<Recording> all_recordings = this->repository.get_all_from_file();
	std::vector<Recording> filtered_recordings(all_recordings.size());
	auto iterator = std::copy_if(all_recordings.begin(), all_recordings.end(), filtered_recordings.begin(), [title, timesAccessed](Recording recording)  { return (recording.get_location().compare(title) == 0 && recording.get_timesAccessed() < timesAccessed); });
	filtered_recordings.resize(std::distance(filtered_recordings.begin(),iterator));
	return filtered_recordings;
}

std::vector<Recording> Service::myList_service()
{
	if (this->mylist_extension == "csv")
		return this->my_CSV.get_myList_CSV();
	else
		return this->my_HTML.get_myList_HTML();
}

void Service::open_myList_service()
{
	if (this->mylist_extension == "csv")
		ShellExecuteA(0, 0, this->my_CSV.get_mylist_path().c_str(), 0, 0, SW_SHOW);
	else
		ShellExecuteA(0, 0, this->my_HTML.get_mylist_path().c_str(), 0, 0, SW_SHOW);

}

void Service::undoAction()
{
	if (this->undoStack.size() == 0)
		return;

	this->undoStack.back()->executeUndo();
	this->redoStack.push_back(std::move(this->undoStack.back()));
	this->undoStack.pop_back();
}

void Service::redoAction()
{
	if (this->redoStack.size() == 0)
		return;

	this->redoStack.back()->executeRedo();
	this->undoStack.push_back(std::move(this->redoStack.back()));
	this->redoStack.pop_back();
}

/////////////////////////
//==In-memory service==//
/////////////////////////

void Service_InMemory::add_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{

	Recording new_recording{ title, location, timeOfCreation, timesAccessed, footagePreview };

	this->validator.validate_new_recording(new_recording);

	this->repository.add_recording(new_recording);

	std::unique_ptr<ActionAdd_InMemory> new_action = std::make_unique<ActionAdd_InMemory>(this->repository, new_recording);

	this->undoStack.push_back(std::move(new_action));

}

void Service_InMemory::delete_recording_service(const std::string& title)
{
	this->validator.validate_deleted_recording(title);

	Recording deleted_recording = this->repository.delete_recording(title);

	std::unique_ptr<ActionRemove_InMemory> new_action = std::make_unique<ActionRemove_InMemory>(this->repository, deleted_recording);

	this->undoStack.push_back(std::move(new_action));
}

void Service_InMemory::update_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview)
{
	Recording updated_recording{ title, location, timeOfCreation, timesAccessed, footagePreview };

	this->validator.validate_new_recording(updated_recording);

	Recording old_recording = this->repository.update_recording(updated_recording);

	std::unique_ptr<ActionUpdate_InMemory> new_action = std::make_unique<ActionUpdate_InMemory>(this->repository, old_recording);

	this->undoStack.push_back(std::move(new_action));
}


std::vector<Recording> Service_InMemory::get_all_recordings_service()
{
	return this->repository.get_all_recordings();
}

Recording Service_InMemory::next_recording_service()
{
	return this->repository.next_recording();
}

void Service_InMemory::save_recording_service(const std::string& title)
{
	this->validator.validate_deleted_recording(title);
	this->repository.save_recording(title);
}

std::vector<Recording> Service_InMemory::list_location_service(const std::string& title, int timesAccessed)
{
	std::vector<Recording> all_recordings = this->repository.get_all_recordings();
	std::vector<Recording> filtered_recordings(all_recordings.size());
	auto iterator = std::copy_if(all_recordings.begin(), all_recordings.end(), filtered_recordings.begin(), [title, timesAccessed](Recording recording) { return (recording.get_location().compare(title) == 0 && recording.get_timesAccessed() < timesAccessed); });
	filtered_recordings.resize(std::distance(filtered_recordings.begin(), iterator));
	return filtered_recordings;
}

std::vector<Recording> Service_InMemory::myList_service()
{
	return this->repository.get_myList();
}

void Service_InMemory::undoAction()
{
	if (this->undoStack.size() == 0)
		return;

	this->undoStack.back()->executeUndo();
	this->redoStack.push_back(std::move(this->undoStack.back()));
	this->undoStack.pop_back();
}

void Service_InMemory::redoAction()
{
	if (this->redoStack.size() == 0)
		return;

	this->redoStack.back()->executeRedo();
	this->undoStack.push_back(std::move(this->redoStack.back()));
	this->redoStack.pop_back();
}
