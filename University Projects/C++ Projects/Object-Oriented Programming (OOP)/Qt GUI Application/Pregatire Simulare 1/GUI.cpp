#include "GUI.h"

#include <qtablewidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

void GUI::initGUI()
{
	setWindowTitle("Magazin de Rochii");
	resize(600, 400);
	listaRochiiWidget = new QListWidget(this);
	btnSortMarime = new QPushButton("Sortare dupa marime");
	btnSortPret = new QPushButton("Sortare dupa pret");
	btnReincarca = new QPushButton("Reincarca lista");

	QVBoxLayout* mainLayout = new QVBoxLayout();
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(btnSortMarime);
	buttonLayout->addWidget(btnSortPret);
	buttonLayout->addWidget(btnReincarca);
	mainLayout->addWidget(listaRochiiWidget);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}

void GUI::connectSignals()
{
	connect(btnSortMarime, &QPushButton::clicked, this, [&]() {
		loadList(magazin.sortareDupaMarime());
		});
	connect(btnSortPret, &QPushButton::clicked, this, [&]() {
		loadList(magazin.sortareDupaPret());
		});
	connect(btnReincarca, &QPushButton::clicked, this, [&]() {
		magazin.adaugaRochii();
		loadList(magazin.getListaRochii());
		});
}

void GUI::loadList(vector<Rochie>& listaRochii)
{
	listaRochiiWidget->clear();
	for (auto& rochie : listaRochii)
	{
		QWidget* lista = new QWidget();
		QHBoxLayout* layout = new QHBoxLayout();
		QLabel* label = new QLabel(QString::fromStdString(rochie.toString()));
		QPushButton* btn = new QPushButton("Inchiriaza");

		layout->addWidget(label);
		layout->addStretch();
		layout->addWidget(btn);
		lista->setLayout(layout);

		QTableWidgetItem* tableItem = new QTableWidgetItem();

		QListWidgetItem* item = new QListWidgetItem(listaRochiiWidget);
		item->setSizeHint(lista->sizeHint());
		listaRochiiWidget->setItemWidget(item, lista);
		listaRochiiWidget->addItem(item);
		if (rochie.getDisponibilitate() == false)
		{
			item->setBackground(QBrush(QColor("red")));
			btn->setEnabled(false);
		}
		else
		{
			item->setBackground(QBrush(QColor("green")));
			btn->setEnabled(true);
		}

		connect(btn, &QPushButton::clicked, this, [item, btn, &rochie]() {
			rochie.setDisponibilitate();
			item->setBackground(QBrush(QColor("red")));
			btn->setEnabled(false);
			});
	}
}
