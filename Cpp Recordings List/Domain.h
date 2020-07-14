#pragma once
#include <iostream>

class Date {

private:
	int day;
	int month;
	int year;

public:
	Date();

	Date(int day, int month, int year);

	int get_day() const { return day; }
	int get_month() const { return month; }
	int get_year() const { return year; }
	void set_day(int day) { this->day = day; }
	void set_month(int month) { this->month = month; }
	void set_year(int year) { this->year = year; }
	std::string date_string();

};

class Recording {
private:
	std::string title, location, footagePreview;
	Date timeOfCreation;
	int timesAccessed;

public:
	Recording();

	Recording(const std::string& title, const std::string& location, const Date timeOfCreation, int timesAccessed, const std::string& footagePreview);

	std::string recording_string();

	std::string get_title() const { return title; }
	std::string get_location() const { return location; }
	Date get_timeOfCreation() const { return timeOfCreation; }
	int get_timesAccessed() const { return timesAccessed; }
	std::string get_footagePreview() const { return footagePreview; }

	void set_location(const std::string& new_location) { this->location = new_location; }
	void set_timeOfCreation(int day, int month, int year) {
		this->timeOfCreation.set_day(day);
		this->timeOfCreation.set_month(month);
		this->timeOfCreation.set_year(year);
	}
	void set_timesAccessed(int new_timesAccessed) { this->timesAccessed = new_timesAccessed; }
	void set_footagePreview(const std::string& new_footagePreview) { this->footagePreview = new_footagePreview; }

	friend std::istream& operator>>(std::istream& input, Recording& recording);
	friend std::ostream& operator<<(std::ostream& output, const Recording& recording);
};

void test_domain();