#pragma once

#include <vector>
#include "Activitate.h"

#include <QAbstractListModel>

class ListViewModel : public QAbstractListModel
{
	Q_OBJECT
private:
	vector<Activitate> activitati;

public:
	ListViewModel(QObject* parent = nullptr)
		: QAbstractListModel(parent) {}

	void setActivitati(const vector<Activitate>& activitati)
	{
		beginResetModel();
		this->activitati = activitati;
		endResetModel();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return (int)activitati.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			const Activitate& activitate = activitati[index.row()];
			return QString::fromStdString(activitate.getTitlu() + " | " + activitate.getDescriere() + " | " 
				+ activitate.getTip() + " | " + to_string(activitate.getDurata()));
		}
		return QVariant();
	}
};

