#pragma once

#include "Service.h"
#include "ListViewModel.h"

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>

class CosWindow : public QWidget, public Observer
{
private: 
	Service& serv;

	QListWidget* listaCos;

	QListView* listView;
	ListViewModel* listViewModel;

	QLabel* lblCos;

	QLineEdit* txtGenerate;
	QLineEdit* txtExport;

	QPushButton* btnEmptyCos;
	QPushButton* btnGenerate;
	QPushButton* btnExport;
	QPushButton* btnAddInCos;

	void initGUI();
	void connectSignals();
	void loadList(const std::vector<Activitate>& activitati);

public:
	CosWindow(Service& serv) : serv{ serv } 
	{
		serv.addObserver(this);
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

	void update() override 
	{
		listViewModel->setActivitati(serv.getActivitatiService());
		// loadList(serv.getActivitatiService());
		try
		{
			lblCos->setText("Cos: " + QString::number(serv.getActivitatiCosService().size()));
		}
		catch (BaseException) 
		{
			lblCos->setText("Cos: 0");
		}
	}
};

