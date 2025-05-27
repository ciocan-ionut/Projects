#pragma once

#include "Depozit.h"

#include <QtWidgets/QWidget>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI()
    {
        initGUI();
        connectSignals();
        loadData(depozit.getProduse());
    }

private:
    /// Functie care initializeaza componentele GUI-ului
    void initGUI();

    /// Functie care initializeaza legaturile intre utilizator si componentele GUI-ului
    void connectSignals();

    /// Functie care incarca tabelul de date cu datele produselor
    /// @param produse este vectorul de produse
    void loadData(vector<Produs> produse);

    Depozit depozit{ "produse.txt" };

    QTableWidget* tableWidget;
    QLineEdit* txtCod;
    QLineEdit* txtBrand;
    QPushButton* btnFilterBrand;
    QPushButton* btnFilterCod;
    QPushButton* btnRefresh;
};
