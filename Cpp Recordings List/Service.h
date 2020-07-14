#pragma once
#include "Validate.h"
#include "UndoRedo.h"
#include <memory>

class Service {
private:
	Repository& repository;
	mylist_CSV& my_CSV;
	mylist_HTML& my_HTML;
	Validate& validator;
	std::string mylist_extension;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;

public:
	Service(Repository& repository, mylist_CSV& my_CSV, mylist_HTML& my_HTML, Validate& validator) : repository{ repository }, my_CSV{ my_CSV }, my_HTML{ my_HTML }, validator{ validator } {}

	void add_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview);
	void delete_recording_service(const std::string& title);
	void update_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview);
	void save_file_path_service(const std::string& file_path);
	void save_mylist_path_service(const std::string& mylist_path);
	std::vector<Recording> get_all_from_file_service();
	Recording next_recording_service();
	void save_recording_service(const std::string& title);
	std::vector<Recording> list_location_service(const std::string& title, int timesAccessed);
	std::vector<Recording> myList_service();
	void open_myList_service();
	void undoAction();
	void redoAction();
};

class Service_InMemory {
private:
	Repository_InMemory& repository;
	Validate& validator;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;
	
public:
	Service_InMemory(Repository_InMemory& repository, Validate& validator) : repository{ repository }, validator{ validator } {}

	void add_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview);
	void delete_recording_service(const std::string& title);
	void update_recording_service(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview);
	std::vector<Recording> get_all_recordings_service();
	Recording next_recording_service();
	void save_recording_service(const std::string& title);
	std::vector<Recording> list_location_service(const std::string& title, int timesAccessed);
	std::vector<Recording> myList_service();
	void undoAction();
	void redoAction();
};