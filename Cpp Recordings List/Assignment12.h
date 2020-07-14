#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Assignment12.h"
#include "RecordingsTableModel.h"

class RecordingsGUI : public QMainWindow
{
	Q_OBJECT

private:
	void connectSignalsAndSlots();
	void set_file_path_interface();
	void set_myList_path_interface();
	void add_recording_interface();
	void delete_recording_interface();
	void update_recording_interface();
	void list_recordings_interface();

	void next_recording_interface();
	void save_recording_interface();
	void filtered_list_interface();
	void mylist_interface();
	void open_myList();
	void open_myList_newWindow();

	void undo_interface();
	void redo_interface();

public:
	RecordingsGUI(Service& service, QWidget* parent = Q_NULLPTR) : service{ service } { 
		user_interface.setupUi(this); 
		this->connectSignalsAndSlots(); 
		this->user_interface.setPaths_Label->setText("File-based repository selected, please set the file paths!");
		this->tableModel = new RecordingsTableModel{ this->service };
	}
	~RecordingsGUI() {}
private:
	Service& service;
	Ui::GUI user_interface;
	RecordingsTableModel* tableModel;
};

class RecordingsGUI_InMemory : public QMainWindow
{
	Q_OBJECT

private:
	void connectSignalsAndSlots();
	void add_recording_interface();
	void delete_recording_interface();
	void update_recording_interface();
	void list_recordings_interface();

	void next_recording_interface();
	void save_recording_interface();
	void filtered_list_interface();
	void mylist_interface();
	void open_myList_newWindow();

	void undo_interface();
	void redo_interface();

public:
	RecordingsGUI_InMemory(Service_InMemory& service, QWidget* parent = Q_NULLPTR) : service{ service } {
		user_interface.setupUi(this);
		this->connectSignalsAndSlots();
		this->user_interface.tabWidget->setTabEnabled(0, false);
		this->user_interface.OpenMyList_Button->setEnabled(false);
		this->tableModel = new RecordingsTableModel_InMemory{ this->service };
	}
	~RecordingsGUI_InMemory() {}

private:
	Service_InMemory& service;
	Ui::GUI user_interface;
	RecordingsTableModel_InMemory* tableModel;
};