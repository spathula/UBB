#include "Domain.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Date::Date() : day(0), month(0), year(0) {}

Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

string Date::date_string()
{
	stringstream date_string;

	if (this->day < 10)
		date_string << "0";
	date_string << this->day;
	date_string << "-";

	if (this->month < 10)
		date_string << "0";
	date_string << this->month;
	date_string << "-";
	
	date_string << this->year;

	return date_string.str();
}

Recording::Recording() : title(""), location(""), timeOfCreation(Date()), timesAccessed(0), footagePreview("") {}

Recording::Recording(const string& title, const string& location, const Date timeOfCreation, int timesAccessed, const string& footagePreview)
{
	this->title = title;
	this->location = location;
	this->timeOfCreation = timeOfCreation;
	this->timesAccessed = timesAccessed;
	this->footagePreview = footagePreview;
}

string Recording::recording_string()
{
	stringstream recording_string;
	string date_string = this->timeOfCreation.date_string();
	recording_string << this->title << " | " << this->location << " | " << date_string << " | " << this->timesAccessed << " | " << this->footagePreview << "\n";
	return recording_string.str();
}

vector<string> get_parameters(string line_read, char delimiter)
{
	vector <string> result;
	stringstream input_sstream(line_read);
	string parameter;
	while (getline(input_sstream, parameter, delimiter))
		result.push_back(parameter);

	return result;
}

istream& operator>>(istream& input, Recording& recording)
{
	string line_read;
	getline(input, line_read);
	vector<string> parameters = get_parameters(line_read,',');
	if (parameters.size() != 5)
		return input;
	vector<string> date_parameters = get_parameters(parameters[2], '-');
	string title = parameters[0];
	string location = parameters[1];
	Date timeOfCreation{ stoi(date_parameters[0]), stoi(date_parameters[1]), stoi(date_parameters[2]) };
	int timesAccesed = stoi(parameters[3]);
	string footagePreview = parameters[4];
	recording.title = title;
	recording.location = location;
	recording.timeOfCreation = timeOfCreation;
	recording.timesAccessed = timesAccesed;
	recording.footagePreview = footagePreview;

	return input;
}

ostream& operator<<(ostream& output, const Recording& recording)
{
	string date_string = recording.get_timeOfCreation().date_string();
	output << recording.get_title() << "," << recording.get_location() << "," << date_string << "," << recording.get_timesAccessed() << "," << recording.get_footagePreview() << "\n";
	return output;
}