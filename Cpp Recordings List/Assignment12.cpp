#include "Assignment12.h"
#include <regex>
#include <QMessageBox>
#include <QtWidgets/QTableView>

Date convert_timeOfCreation(const std::string& timeOfCreation_string)
{
	int day, month, year;
	std::string split_timeOfCreation[3];
	std::regex words_regex("[^\\s-.,:;!?]+");
	auto words_begin = std::sregex_iterator(timeOfCreation_string.begin(), timeOfCreation_string.end(), words_regex);
	auto words_end = std::sregex_iterator();
	int counter = 0;
	for (std::sregex_iterator timeOfCreation_word = words_begin; timeOfCreation_word != words_end; ++timeOfCreation_word)
		split_timeOfCreation[counter++] = (*timeOfCreation_word).str();
	day = stoi(split_timeOfCreation[0]);
	month = stoi(split_timeOfCreation[1]);
	year = stoi(split_timeOfCreation[2]);
	Date timeOfCreation{ day, month, year };
	return timeOfCreation;
}


void RecordingsGUI::connectSignalsAndSlots()
{
	QObject::connect(this->user_interface.setFilePath_Button, &QPushButton::clicked, this, &RecordingsGUI::set_file_path_interface);
	QObject::connect(this->user_interface.setMyListPath_Button, &QPushButton::clicked, this, &RecordingsGUI::set_myList_path_interface);

	QObject::connect(this->user_interface.Add_Button, &QPushButton::clicked, this, &RecordingsGUI::add_recording_interface);
	QObject::connect(this->user_interface.Delete_Button, &QPushButton::clicked, this, &RecordingsGUI::delete_recording_interface);
	QObject::connect(this->user_interface.Update_Button, &QPushButton::clicked, this, &RecordingsGUI::update_recording_interface);
	QObject::connect(this->user_interface.List_Button, &QPushButton::clicked, this, &RecordingsGUI::list_recordings_interface);

	QObject::connect(this->user_interface.NextRecording_Button, &QPushButton::clicked, this, &RecordingsGUI::next_recording_interface);
	QObject::connect(this->user_interface.FilteredList_Button, &QPushButton::clicked, this, &RecordingsGUI::filtered_list_interface);
	QObject::connect(this->user_interface.SaveRecording_Button, &QPushButton::clicked, this, &RecordingsGUI::save_recording_interface);
	QObject::connect(this->user_interface.MyList_Button, &QPushButton::clicked, this, &RecordingsGUI::mylist_interface);
	QObject::connect(this->user_interface.OpenMyList_Button, &QPushButton::clicked, this, &RecordingsGUI::open_myList);
	QObject::connect(this->user_interface.MyListWindow_Button, &QPushButton::clicked, this, &RecordingsGUI::open_myList_newWindow);

	QObject::connect(this->user_interface.Undo_Button, &QPushButton::clicked, this, &RecordingsGUI::undo_interface);
	QObject::connect(this->user_interface.Redo_Button, &QPushButton::clicked, this, &RecordingsGUI::redo_interface);
}

void RecordingsGUI::set_file_path_interface()
{
	QString file_path = this->user_interface.setFilePath->text();
	
	this->service.save_file_path_service(file_path.toStdString());
}

void RecordingsGUI::set_myList_path_interface()
{
	QString myList_path = this->user_interface.setMyListPath->text();

	this->service.save_mylist_path_service(myList_path.toStdString());
}

void RecordingsGUI::add_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();
	QString location = this->user_interface.Location_LEdit->text();
	QString timeOfCreation_string = this->user_interface.TimeOfCreation_LEdit->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit->text();
	QString footagePreview = this->user_interface.FootagePreview_LEdit->text();

	Date timeOfCreation = convert_timeOfCreation(timeOfCreation_string.toStdString());
	try {
		this->service.add_recording_service(title.toStdString(), location.toStdString(), timeOfCreation, timesAccessed.toInt(), footagePreview.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI::delete_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();

	try {
		this->service.delete_recording_service(title.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI::update_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();
	QString location = this->user_interface.Location_LEdit->text();
	QString timeOfCreation_string = this->user_interface.TimeOfCreation_LEdit->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit->text();
	QString footagePreview = this->user_interface.FootagePreview_LEdit->text();

	Date timeOfCreation = convert_timeOfCreation(timeOfCreation_string.toStdString());
	try {
		this->service.update_recording_service(title.toStdString(), location.toStdString(), timeOfCreation, timesAccessed.toInt(), footagePreview.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI::list_recordings_interface()
{
	this->user_interface.list_Widget->clear();
	
	std::vector<Recording> recordings = this->service.get_all_from_file_service();

	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.list_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI::next_recording_interface()
{
	this->user_interface.CurrentRecording_Widget->clear();
	QString recordingString = QString::fromStdString(this->service.next_recording_service().recording_string());
	QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
	this->user_interface.CurrentRecording_Widget->addItem(recordingInList);
}

void RecordingsGUI::save_recording_interface()
{
	QString title = this->user_interface.Title_LEdit_ModeB->text();
	try {
		this->service.save_recording_service(title.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI::filtered_list_interface()
{
	this->user_interface.FilteredList_Widget->clear();
	QString location = this->user_interface.Location_LEdit_ModeB->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit_ModeB->text();

	std::vector<Recording> recordings = this->service.list_location_service(location.toStdString(), timesAccessed.toInt());
	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.FilteredList_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI::mylist_interface()
{
	this->user_interface.MyList_Widget->clear();
	
	std::vector<Recording> recordings = this->service.myList_service();
	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.MyList_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI::open_myList()
{
	this->service.open_myList_service();
}

void RecordingsGUI::open_myList_newWindow()
{
	QDialog* myList_Dialog = new QDialog{ this };
	myList_Dialog->setModal(true);
	QHBoxLayout* myList_Layout = new QHBoxLayout{ myList_Dialog };
	QTableView* tableView = new QTableView{ myList_Dialog };
	tableView->setModel(this->tableModel);
	myList_Layout->addWidget(tableView);

	myList_Dialog->exec();
}

void RecordingsGUI::undo_interface()
{
	this->service.undoAction();
}

void RecordingsGUI::redo_interface()
{
	this->service.redoAction();
}

///////////////////////////
//==In-memory interface==//
///////////////////////////


void RecordingsGUI_InMemory::connectSignalsAndSlots()
{
	QObject::connect(this->user_interface.Add_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::add_recording_interface);
	QObject::connect(this->user_interface.Delete_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::delete_recording_interface);
	QObject::connect(this->user_interface.Update_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::update_recording_interface);
	QObject::connect(this->user_interface.List_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::list_recordings_interface);

	QObject::connect(this->user_interface.NextRecording_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::next_recording_interface);
	QObject::connect(this->user_interface.FilteredList_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::filtered_list_interface);
	QObject::connect(this->user_interface.SaveRecording_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::save_recording_interface);
	QObject::connect(this->user_interface.MyList_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::mylist_interface);
	QObject::connect(this->user_interface.MyListWindow_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::open_myList_newWindow);

	QObject::connect(this->user_interface.Undo_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::undo_interface);
	QObject::connect(this->user_interface.Redo_Button, &QPushButton::clicked, this, &RecordingsGUI_InMemory::redo_interface);
}

void RecordingsGUI_InMemory::add_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();
	QString location = this->user_interface.Location_LEdit->text();
	QString timeOfCreation_string = this->user_interface.TimeOfCreation_LEdit->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit->text();
	QString footagePreview = this->user_interface.FootagePreview_LEdit->text();

	Date timeOfCreation = convert_timeOfCreation(timeOfCreation_string.toStdString());
	try {
		this->service.add_recording_service(title.toStdString(), location.toStdString(), timeOfCreation, timesAccessed.toInt(), footagePreview.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI_InMemory::delete_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();

	try {
		this->service.delete_recording_service(title.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI_InMemory::update_recording_interface()
{
	QString title = this->user_interface.Title_LEdit->text();
	QString location = this->user_interface.Location_LEdit->text();
	QString timeOfCreation_string = this->user_interface.TimeOfCreation_LEdit->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit->text();
	QString footagePreview = this->user_interface.FootagePreview_LEdit->text();

	Date timeOfCreation = convert_timeOfCreation(timeOfCreation_string.toStdString());
	try {
		this->service.update_recording_service(title.toStdString(), location.toStdString(), timeOfCreation, timesAccessed.toInt(), footagePreview.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI_InMemory::list_recordings_interface()
{
	this->user_interface.list_Widget->clear();

	std::vector<Recording> recordings = this->service.get_all_recordings_service();

	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.list_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI_InMemory::next_recording_interface()
{
	this->user_interface.CurrentRecording_Widget->clear();
	QString recordingString = QString::fromStdString(this->service.next_recording_service().recording_string());
	QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
	this->user_interface.CurrentRecording_Widget->addItem(recordingInList);
}

void RecordingsGUI_InMemory::save_recording_interface()
{
	QString title = this->user_interface.Title_LEdit_ModeB->text();
	try {
		this->service.save_recording_service(title.toStdString());
	}
	catch (ValidationException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
	catch (RepositoryException& error) {
		QString error_message = QString::fromStdString(error.throw_error());
		QMessageBox error_box;
		error_box.setText(error_message);
		error_box.exec();
	}
}

void RecordingsGUI_InMemory::filtered_list_interface()
{
	this->user_interface.FilteredList_Widget->clear();
	QString location = this->user_interface.Location_LEdit_ModeB->text();
	QString timesAccessed = this->user_interface.TimesAccessed_LEdit_ModeB->text();

	std::vector<Recording> recordings = this->service.list_location_service(location.toStdString(), timesAccessed.toInt());
	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.FilteredList_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI_InMemory::mylist_interface()
{
	this->user_interface.MyList_Widget->clear();

	std::vector<Recording> recordings = this->service.myList_service();
	for (auto recording : recordings)
	{
		QString recordingString = QString::fromStdString(recording.recording_string());
		QListWidgetItem* recordingInList = new QListWidgetItem{ recordingString };
		this->user_interface.MyList_Widget->addItem(recordingInList);
	}
}

void RecordingsGUI_InMemory::undo_interface()
{
	this->service.undoAction();
}

void RecordingsGUI_InMemory::redo_interface()
{
	this->service.redoAction();
}

void RecordingsGUI_InMemory::open_myList_newWindow()
{
	QDialog* myList_Dialog = new QDialog{ this };
	myList_Dialog->setModal(true);
	QHBoxLayout* myList_Layout = new QHBoxLayout{ myList_Dialog };
	QTableView* tableView = new QTableView{ myList_Dialog };
	tableView->setModel(this->tableModel);
	myList_Layout->addWidget(tableView);
	myList_Dialog->exec();
}