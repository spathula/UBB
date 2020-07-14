#pragma once
#include "Repository.h"

class Action {
public:
	virtual void executeUndo() {};
	virtual void executeRedo() {};
};

class ActionAdd : public Action {
private:
	Repository& repository;
	Recording addedRecording;

public:
	ActionAdd(Repository& repository, Recording addedRecording) : repository{ repository }, addedRecording{ addedRecording } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action {
private:
	Repository& repository;
	Recording removedRecording;

public:
	ActionRemove(Repository& repository, Recording removedRecording) : repository{ repository }, removedRecording{ removedRecording } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action {
private:
	Repository& repository;
	Recording updatedRecording;

public:
	ActionUpdate(Repository& repository, Recording updatedRecording) : repository{ repository }, updatedRecording{ updatedRecording } {}
	void set_recording(Recording recording) { this->updatedRecording = recording; }
	void executeUndo() override;
	void executeRedo() override;
};

class ActionAdd_InMemory : public Action {
private:
	Repository_InMemory& repository;
	Recording addedRecording;

public:
	ActionAdd_InMemory(Repository_InMemory& repository, Recording addedRecording) : repository{ repository }, addedRecording{ addedRecording } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove_InMemory : public Action {
private:
	Repository_InMemory& repository;
	Recording removedRecording;

public:
	ActionRemove_InMemory(Repository_InMemory& repository, Recording removedRecording) : repository{ repository }, removedRecording{ removedRecording } {}
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate_InMemory : public Action {
private:
	Repository_InMemory& repository;
	Recording updatedRecording;

public:
	ActionUpdate_InMemory(Repository_InMemory& repository, Recording updatedRecording) : repository{ repository }, updatedRecording{ updatedRecording } {}
	void set_recording(Recording recording) { this->updatedRecording = recording; }
	void executeUndo() override;
	void executeRedo() override;
};