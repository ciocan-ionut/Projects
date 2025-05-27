#pragma once
#include "C:\Qt\6.9.0\msvc2022_64\include\QtWidgets\qwidget.h"
#include <qpainter.h>
#include <cstdlib>
#include <ctime>
#include "Observer.h"
#include "Service.h"

class CosReadOnlyWindow : public QWidget, public Observer
{
private: 
	Service& serv;

public:
	CosReadOnlyWindow(Service& serv) : serv{ serv } 
	{
		serv.addObserver(this);
		setWindowTitle("Activitati - Cos Read Only");
		srand(time(nullptr));
		repaint();
	}

	void update() override
	{
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override 
	{
		size_t cosSize;
		try
		{
			cosSize = serv.getActivitatiCosService().size();
		}
		catch (BaseException)
		{
			cosSize = 0;
		}
		QPainter p{ this };
		for (int i = 0; i < cosSize; i++) 
		{
			int x = rand() % width();
			int y = rand() % height();
			p.drawEllipse(x, y, 20, 20);
		}
	}
};

