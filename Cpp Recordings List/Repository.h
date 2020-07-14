#pragma once
#include "Domain.h"
#include "Exception.h"
#include <vector>

class Repository {

protected:

	std::string file_path;

	int next_position;

public:

	Repository() { this->next_position = 0; }

	void save_file_path(const std::string& file_path);

	void add_recording(const Recording& recording);

	Recording delete_recording(const std::string& title);

	Recording update_recording(const Recording& updated_recording);

	int search_file(const std::string& title);

	Recording next_recording();

	virtual void save_recording(const std::string& title) {};

	std::vector <Recording> get_all_from_file();

	void clear_file(const std::string& file_path);

	void write_all_to_file(std::vector<Recording> recordings);

};

class mylist_CSV : public Repository {
private:
	std::string mylist_path_CSV;

public:

	mylist_CSV() {}

	void save_mylist_path_CSV(const std::string& mylist_path);

	void save_recording(const std::string& title) override;

	std::vector<Recording> get_myList_CSV();

	std::string get_mylist_path() { return this->mylist_path_CSV; }
};

class mylist_HTML : public Repository {
private:
	std::string mylist_path_HTML;

public:

	mylist_HTML() {}

	void save_mylist_path_HTML(const std::string& mylist_path);

	void save_recording(const std::string& title) override;

	std::vector<Recording> get_myList_HTML();

	std::string get_mylist_path() { return this->mylist_path_HTML; }

	void write_to_HTML(std::vector <Recording> recordings);
	
	void read_from_HTML();
};

class Repository_InMemory {
private:
	std::vector<Recording> recordings;
	std::vector<Recording> myList_recordings;
	int nextPosition;

public:

	Repository_InMemory() { this->nextPosition = 0; }

	void add_recording(const Recording& recording);

	Recording delete_recording(const std::string& title);

	Recording update_recording(const Recording& updated_recording);

	bool search_recording(const std::string& title);

	Recording next_recording();

	void save_recording(const std::string& title);

	std::vector<Recording> get_myList();

	std::vector <Recording> get_all_recordings();

};