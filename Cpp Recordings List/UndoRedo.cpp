#include "UndoRedo.h"

void ActionAdd::executeUndo()
{
	this->repository.delete_recording(this->addedRecording.get_title());
}

void ActionAdd::executeRedo()
{
	this->repository.add_recording(this->addedRecording);
}

void ActionRemove::executeUndo()
{
	this->repository.add_recording(this->removedRecording);
}

void ActionRemove::executeRedo()
{
	this->repository.delete_recording(this->removedRecording.get_title());
}

void ActionUpdate::executeUndo()
{
	Recording recording = this->repository.update_recording(this->updatedRecording);
	this->set_recording(recording);
}

void ActionUpdate::executeRedo()
{
	Recording recording = this->repository.update_recording(this->updatedRecording);
	this->set_recording(recording);
}


void ActionAdd_InMemory::executeUndo()
{
	this->repository.delete_recording(this->addedRecording.get_title());
}

void ActionAdd_InMemory::executeRedo()
{
	this->repository.add_recording(this->addedRecording);
}

void ActionRemove_InMemory::executeUndo()
{
	this->repository.add_recording(this->removedRecording);
}

void ActionRemove_InMemory::executeRedo()
{
	this->repository.delete_recording(this->removedRecording.get_title());
}

void ActionUpdate_InMemory::executeUndo()
{
	Recording recording = this->repository.update_recording(this->updatedRecording);
	this->set_recording(recording);
}

void ActionUpdate_InMemory::executeRedo()
{
	Recording recording = this->repository.update_recording(this->updatedRecording);
	this->set_recording(recording);
}
