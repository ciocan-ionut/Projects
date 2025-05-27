#pragma once

#include "Jocuri.h"

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI()
    {
        initGUI();
		connectSignals();
		loadList(jocuri.getJocuri());
    }

private:
	void initGUI();
	void connectSignals();
    void loadList(vector<Joc> jocuri);

	Jocuri jocuri{ "jocuri.txt" };

	QTableWidget* tableWidget;
    QLabel* ratingLabel;
    QPushButton* sortButton;
	QPushButton* filterButton;
    QPushButton* refreshButton;
};
