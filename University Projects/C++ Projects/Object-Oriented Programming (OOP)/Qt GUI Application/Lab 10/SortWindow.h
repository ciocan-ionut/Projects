#pragma once

#include "Service.h"
#include "ListViewModel.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qcheckbox.h>

class SortWindow : public QWidget
{
private:
	Service& serv;

	QListWidget* listaSortata;

	QListView* listView;
	ListViewModel* listViewModel;

	QPushButton* btnSortTitlu;
	QPushButton* btnSortDescriere;
	QPushButton* btnSortTipDurata;

	QCheckBox* checkBoxSort;

	void initGUI();
	void connectSignals();
	void loadList(const std::vector<Activitate>& activitati);
	void resizeEvent(QResizeEvent* event);

public:
	SortWindow(Service& serv) : serv{ serv } {
		initGUI();
		connectSignals();
		try
		{
			// loadList(serv.getActivitatiService());
		}
		catch (const BaseException& ex) {
			QMessageBox::warning(this, "Eroare", ex.what());
		}
	}
};

