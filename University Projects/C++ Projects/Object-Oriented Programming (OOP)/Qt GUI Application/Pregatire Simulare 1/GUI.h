#pragma once

#include <vector>

#include "Rochie.h"
#include "Magazin.h"

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI()
    {
        initGUI();
		connectSignals();
		loadList(magazin.getListaRochii());
    }

private:
	void initGUI();
	void connectSignals();
    void loadList(vector<Rochie>& listaRochii);

    Magazin magazin{ "rochie.txt" };

	QListWidget* listaRochiiWidget;
    QPushButton* btnSortMarime;
	QPushButton* btnSortPret;
	QPushButton* btnReincarca;
};
