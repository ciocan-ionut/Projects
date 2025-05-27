#pragma once
#include "Service.h"
#include "ListViewModel.h"

#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlineedit.h>

class FilterWindow : public QWidget
{
private:
	Service& serv;

	QListWidget* listaFiltrata;

	QListView* listView;
	ListViewModel* listViewModel;

	QLineEdit* txtDescriere;
	QLineEdit* txtTip;

	QPushButton* btnFilterDescriere;
	QPushButton* btnFilterTip;

	void initGUI();
	void connectSignals();
	void loadList(const std::vector<Activitate>& activitati);

public:
	FilterWindow(Service& serv) : serv{ serv } {
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

