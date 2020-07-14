#include "RecordingsTableModel.h"

int RecordingsTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.myList_service().size() + 1;
}

int RecordingsTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant RecordingsTableModel::data(const QModelIndex& index, int role) const
{
	std::vector<Recording> recordings = this->service.myList_service();

	if (index.row() == recordings.size())
		return QVariant{};

	Recording recording = recordings[index.row()];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0:
			return QString::fromStdString(recording.get_title());
		case 1:
			return QString::fromStdString(recording.get_location());
		case 2:
			return QString::fromStdString(recording.get_timeOfCreation().date_string());
		case 3:
			return QString::fromStdString(std::to_string(recording.get_timesAccessed()));
		case 4:
			return QString::fromStdString(recording.get_footagePreview());
		}
	}

	return QVariant{};
}

QVariant RecordingsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Location" };
			case 2:
				return QString{ "Time of creation" };
			case 3:
				return QString{ "Times accessed" };
			case 4:
				return QString{ "Footage preview" };
			default:
				break;
			}
		}
	}

	return QVariant{};
}

Qt::ItemFlags RecordingsTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}



int RecordingsTableModel_InMemory::rowCount(const QModelIndex& parent) const
{
	return this->service.myList_service().size() + 1;
}

int RecordingsTableModel_InMemory::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant RecordingsTableModel_InMemory::data(const QModelIndex& index, int role) const
{
	std::vector<Recording> recordings = this->service.myList_service();

	if (index.row() == recordings.size())
		return QVariant{};

	Recording recording = recordings[index.row()];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (index.column())
		{
		case 0:
			return QString::fromStdString(recording.get_title());
		case 1:
			return QString::fromStdString(recording.get_location());
		case 2:
			return QString::fromStdString(recording.get_timeOfCreation().date_string());
		case 3:
			return QString::fromStdString(std::to_string(recording.get_timesAccessed()));
		case 4:
			return QString::fromStdString(recording.get_footagePreview());
		}
	}

	return QVariant{};
}

QVariant RecordingsTableModel_InMemory::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Location" };
			case 2:
				return QString{ "Time of creation" };
			case 3:
				return QString{ "Times accessed" };
			case 4:
				return QString{ "Footage preview" };
			default:
				break;
			}
		}
	}

	return QVariant{};
}

Qt::ItemFlags RecordingsTableModel_InMemory::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
