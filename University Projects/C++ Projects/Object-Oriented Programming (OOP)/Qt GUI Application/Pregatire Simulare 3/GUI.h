#pragma once

#include <QtWidgets/QMainWindow>
#include <qwidget.h>
#include <Firma.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qformlayout.h>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI()
    {
        initGUI();
        connectSignals();
        loadData(firma.getDevices());
    }

private:
    void initGUI();
	void connectSignals();
    void loadData(vector<Device> devices);

	Firma firma{ "devices.txt" };

	QListWidget* listWidget;
	QPushButton* btnSortModel;
	QPushButton* btnSortAn;
	QPushButton* btnRefresh;
	QLineEdit* txtModel;
    QLineEdit* txtAn;
};
