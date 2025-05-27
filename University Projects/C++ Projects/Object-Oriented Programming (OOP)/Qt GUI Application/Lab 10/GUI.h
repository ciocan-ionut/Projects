#pragma once

#include "Service.h"
#include "SortWindow.h"
#include "FilterWindow.h"
#include "CosWindow.h"
#include "TableViewModel.h"
#include "ListViewModel.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qtablewidget.h>

class GUI : public QWidget
{
private:
    Service& serv;

    QListWidget* listaActivitati;
	QTableWidget* tabelActivitati;

    QListView* listView;
	ListViewModel* listViewModel;

    QTableView* tableView;
	TableViewModel* tableViewModel;

    QLineEdit* txtTitlu;
    QLineEdit* txtDescriere;
    QLineEdit* txtTip;
    QLineEdit* txtDurata;

    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnModify;
    QPushButton* btnReload;
    QPushButton* btnUndo;

    QPushButton* btnSort;
    QPushButton* btnFilter;
	QPushButton* btnRaport;

    QPushButton* btnExit;
	QPushButton* btnCos;

	QPushButton* btnAddInCos;
	QPushButton* btnEmptyCos;
	QPushButton* btnGenerate;
	QLineEdit* txtGenerate;

	SortWindow* sortWindow = nullptr;
	FilterWindow* filterWindow = nullptr;
	CosWindow* cosWindow = nullptr;

    void initGUI();
    void connectSignals();
    void loadList(const std::vector<Activitate>& activitati);
    bool ignoreSelectionChange = false;
	void loadRaport(const std::map<string, DTO>& raport);

public:
    GUI(Service& serv) : serv{ serv } {
        serv.loadFromFile();
        initGUI();
        connectSignals();
        // loadList(serv.getActivitatiService());
    }
};

