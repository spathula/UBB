#pragma once
#include <QAbstractTableModel>
#include "Service.h"

class RecordingsTableModel : public QAbstractTableModel {
private:
	Service& service;

public:
	RecordingsTableModel(Service& service, QObject* parent = NULL) : QAbstractTableModel{ parent }, service{ service } {}
	~RecordingsTableModel() {}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
};


class RecordingsTableModel_InMemory : public QAbstractTableModel {
private:
	Service_InMemory& service;

public:
	RecordingsTableModel_InMemory(Service_InMemory& service, QObject* parent = NULL) : QAbstractTableModel{ parent }, service{ service } {}
	~RecordingsTableModel_InMemory() {}

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
};