#include "Repository.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

void Repository::save_file_path(const string& file_path)
{
	ofstream create_file;
	create_file.open(file_path, ios::out | ios::trunc);
	create_file.close();
	this->file_path = file_path;
}

void Repository::add_recording(const Recording& recording)
{
	ofstream file(this->file_path, ios::app);

	if (this->search_file(recording.get_title()) == -1)
		file << recording;
	else
		throw RepositoryException("Recording already exists!");
}

Recording Repository::delete_recording(const string& title)
{
	if (search_file(title) == -1)
		throw RepositoryException("Recording doesn't exist!");

	vector <Recording> recordings = get_all_from_file();
	int position = 0;
	Recording deleted_recording;

	for (auto recording : recordings)
		if (recording.get_title().compare(title) == 0)
		{
			deleted_recording = recording;
			recordings.erase(recordings.begin()+position);
			break;
		}
		else
			position++;
	write_all_to_file(recordings);
	return deleted_recording;
}

Recording Repository::update_recording(const Recording& updated_recording)
{
	if (search_file(updated_recording.get_title()) == -1)
		throw RepositoryException("Recording doesn't exist!");

	vector <Recording> recordings = get_all_from_file();
	int position = 0;
	Recording returned_recording;

	for (auto recording : recordings)
		if (recording.get_title().compare(updated_recording.get_title()) == 0)
		{
			returned_recording = recording;
			recordings.erase(recordings.begin() + position);
			recordings.insert(recordings.begin() + position, updated_recording);
			break;
		}
		else
			position++;

	write_all_to_file(recordings);
	return returned_recording;
}

int Repository::search_file(const string& title)
{
	ifstream file(this->file_path);
	string line;

	while (getline(file, line))
		if (line.find(title) != string::npos)
			return 1;
	return -1;
}

Recording Repository::next_recording()
{
	vector<Recording> recordings = get_all_from_file();
	if (this->next_position == recordings.size())
		this->next_position = 0;
	return recordings[this->next_position++];
}

vector <Recording> Repository::get_all_from_file()
{
	ifstream file(this->file_path);
	vector <Recording> recordings;
	Recording recording{};

	while (file >> recording)
	{
		recordings.push_back(recording);
	}

	return recordings;
}

void Repository::clear_file(const string& file_path)
{
	ofstream clear_file;
	clear_file.open(file_path, ios::out | ios::trunc);
	clear_file.close();
}

void Repository::write_all_to_file(vector <Recording> recordings)
{
	this->clear_file(this->file_path);
	if (recordings.size() == 0)
		return;

	ofstream file(this->file_path, ios::app);

	for (auto recording : recordings)
		file << recording;

	file.close();
}

void mylist_CSV::save_mylist_path_CSV(const string& mylist_path)
{
	ofstream create_file;
	create_file.open(mylist_path, ios::out | ios::trunc);
	create_file.close();
	this->mylist_path_CSV = mylist_path;
}

void mylist_CSV::save_recording(const string& title)
{
	ofstream file(this->mylist_path_CSV, ios::app);
	vector<Recording> recordings = get_all_from_file();
	for (auto recording : recordings)
		if (recording.get_title().compare(title) == 0)
		{
			file << recording;
			return;
		}
	throw RepositoryException("Recording doesn't exist!");
}

vector<Recording> mylist_CSV::get_myList_CSV()
{
	ifstream file(this->mylist_path_CSV);
	vector <Recording> recordings;
	Recording recording{};

	while (file >> recording)
	{
		recordings.push_back(recording);
	}

	return recordings;
}

void mylist_HTML::save_mylist_path_HTML(const string& mylist_path)
{
	ofstream create_file;
	create_file.open(mylist_path, ios::out | ios::trunc);
	create_file.close();
	this->mylist_path_HTML = mylist_path;
}

void mylist_HTML::save_recording(const string& title)
{
	vector<Recording> recordings_from_html = this->get_myList_HTML();
	vector<Recording> recordings_from_file = this->get_all_from_file();
	for (auto recording : recordings_from_file)
		if (recording.get_title() == title)
		{
			recordings_from_html.push_back(recording);
			this->write_to_HTML(recordings_from_html);
			return;
		}
}

Date convert_timeOfCreation_HTML(const string& timeOfCreation_string)
{
	int day, month, year;
	string split_timeOfCreation[3];
	regex words_regex("[^\\s-.,:;!?]+");
	auto words_begin = sregex_iterator(timeOfCreation_string.begin(), timeOfCreation_string.end(), words_regex);
	auto words_end = sregex_iterator();
	int counter = 0;
	for (sregex_iterator timeOfCreation_word = words_begin; timeOfCreation_word != words_end; ++timeOfCreation_word)
		split_timeOfCreation[counter++] = (*timeOfCreation_word).str();
	day = stoi(split_timeOfCreation[0]);
	month = stoi(split_timeOfCreation[1]);
	year = stoi(split_timeOfCreation[2]);
	Date timeOfCreation{ day, month, year };
	return timeOfCreation;
}

vector<Recording> mylist_HTML::get_myList_HTML()
{
	ifstream file(this->mylist_path_HTML);
	vector <Recording> recordings;
	
	string line_read;
	for (int i = 0; i < 14; i++)
		getline(file, line_read);
	while (line_read.size() != 0)
	{
		string title, location, timeOfCreation_string, footagePreview;
		int timesAccessed;
		getline(file, line_read);
		if (line_read == "</tr>")
			getline(file, line_read);
		if (line_read == "</table>")
			break;
		if (line_read == "<tr>")
			getline(file, line_read);
		title = line_read.substr(4, line_read.size() - 9);
		getline(file, line_read);
		location = line_read.substr(4, line_read.size() - 9);
		getline(file, line_read);
		timeOfCreation_string = line_read.substr(4, line_read.size() - 9);
		getline(file, line_read);
		timesAccessed = stoi(line_read.substr(4, line_read.size() - 9));
		getline(file, line_read);
		footagePreview = line_read.substr(4, line_read.size() - 9);
		Recording recording{title, location, convert_timeOfCreation_HTML(timeOfCreation_string), timesAccessed, footagePreview};
		recordings.push_back(recording);
		getline(file, line_read);
	}

	return recordings;
}

void mylist_HTML::write_to_HTML(vector <Recording> recordings)
{
	this->clear_file(this->mylist_path_HTML);
	if (recordings.size() == 0)
		return;

	ofstream file(this->mylist_path_HTML, ios::app);

	file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Recordings</title>\n</head>\n<body>\n<table border = \"1\">\n<tr>\n<td>Title</td>\n<td>Location</td>\n\
<td>Time Of Creation</td>\n<td>Times Accessed</td>\n<td>Footage Preview</td>\n";

	for (auto recording : recordings)
	{
		string date_string = recording.get_timeOfCreation().date_string();
		file << "<tr>\n<td>" << recording.get_title() << "</td>\n<td>" << recording.get_location() << "</td>\n<td>" << date_string << \
			"</td>\n<td>" << recording.get_timesAccessed() << "</td>\n<td>" << recording.get_footagePreview() << "</td>\n</tr>\n";
	}

	file << "</table>\n</body>\n</html>\n";
}

void Repository_InMemory::add_recording(const Recording& recording)
{
	if (search_recording(recording.get_title()) == false)
		this->recordings.push_back(recording);
	else
		throw RepositoryException("Recording already exists!");
}

Recording Repository_InMemory::delete_recording(const std::string& title)
{
	int position = 0;
	Recording deleted_recording;
	if (search_recording(title) == true)
		for (auto recording : this->recordings)
			if (recording.get_title() == title)
			{
				deleted_recording = recording;
				this->recordings.erase(recordings.begin() + position);
				break;
			}
			else
				position++;
	else
		throw RepositoryException("Recording doesn't exist!");

	return deleted_recording;
}

Recording Repository_InMemory::update_recording(const Recording& updated_recording)
{
	int position = 0;
	Recording returned_recording;
	if (search_recording(updated_recording.get_title()) == true)
		for (auto recording : this->recordings)
			if (recording.get_title() == updated_recording.get_title())
			{
				returned_recording = recording;
				this->recordings.erase(recordings.begin() + position);
				this->recordings.insert(recordings.begin() + position, updated_recording);
				break;
			}
			else
				position++;
	else
		throw RepositoryException("Recording doesn't exist!");

	return returned_recording;
}

bool Repository_InMemory::search_recording(const std::string& title)
{
	for (auto recording : this->recordings)
		if (recording.get_title() == title)
			return true;
	return false;
}

Recording Repository_InMemory::next_recording()
{
	if (this->nextPosition == this->recordings.size())
		this->nextPosition = 0;
	return this->recordings[this->nextPosition++];
}

void Repository_InMemory::save_recording(const string& title)
{
	if (search_recording(title) == true)
	{
		for (auto recording : this->recordings)
			if (recording.get_title() == title)
				this->myList_recordings.push_back(recording);
	}
	else
		throw RepositoryException("Recording doesn't exist!");
}

vector<Recording> Repository_InMemory::get_myList()
{
	return this->myList_recordings;
}

vector <Recording> Repository_InMemory::get_all_recordings()
{
	return this->recordings;
}