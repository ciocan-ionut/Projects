#pragma once

#include <vector>
#include "Activitate.h"

#include <QAbstractTableModel>

class TableViewModel : public QAbstractTableModel
{
	Q_OBJECT
private:
	vector<Activitate> activitati;

public:
	TableViewModel(QObject* parent = nullptr)
		: QAbstractTableModel(parent) {}

	void setActivitati(const vector<Activitate>& activitati)
	{
		emit layoutAboutToBeChanged();
		this->activitati = activitati;
		emit layoutChanged();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return (int)activitati.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 4; // Titlu, Descriere, Tip, Durata
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			const Activitate& activitate = activitati[index.row()];
			switch (index.column())
			{
			case 0: return QString::fromStdString(activitate.getTitlu());
			case 1: return QString::fromStdString(activitate.getDescriere());
			case 2: return QString::fromStdString(activitate.getTip());
			case 3: return QString::number(activitate.getDurata());
			}
		}
		return QVariant();
	}
};

