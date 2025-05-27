#include "GUI.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qformlayout.h>
#include <QList>

void GUI::initGUI()
{
	setWindowTitle("Depozit");
	setMinimumSize(600, 400);

	QFormLayout* mainLayout = new QFormLayout();

	tableWidget = new QTableWidget();
	tableWidget->setColumnCount(3);
	mainLayout->addWidget(tableWidget);

	txtBrand = new QLineEdit();
	mainLayout->addRow("Brand", txtBrand);

	txtCod = new QLineEdit();
	mainLayout->addRow("Cod", txtCod);

	QHBoxLayout* btnLayout = new QHBoxLayout();

	btnFilterBrand = new QPushButton("Brand");
	btnFilterCod = new QPushButton("Cod");
	btnRefresh = new QPushButton("Refresh");
	btnLayout->addWidget(btnFilterBrand);
	btnLayout->addWidget(btnFilterCod);
	btnLayout->addWidget(btnRefresh);
	mainLayout->addItem(btnLayout);

	setLayout(mainLayout);
}

void GUI::connectSignals()
{
	QObject::connect(btnFilterBrand, &QPushButton::clicked, [&]() {
		string brand = txtBrand->text().toStdString();
		auto produseFiltrate = depozit.filterByBrand(brand);
		loadData(produseFiltrate);
		});

	QObject::connect(btnFilterCod, &QPushButton::clicked, [&]() {
		int cod = txtCod->text().toInt();
		auto produseFiltrate = depozit.filterByCod(cod);
		loadData(produseFiltrate);
		});

	QObject::connect(btnRefresh, &QPushButton::clicked, [&]() {
		loadData(depozit.getProduse());
		});

	QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [&]() {
		int row = tableWidget->currentRow();
		QTableWidgetItem* itemTip = tableWidget->item(row, 0);
		QTableWidgetItem* itemBrand = tableWidget->item(row, 1);
		QTableWidgetItem* itemConsum = tableWidget->item(row, 2);
		string tip = itemTip->text().toStdString();
		string brand = itemBrand->text().toStdString();
		double consum = itemConsum->text().toDouble();
		auto produse = depozit.getProduse();
		for (const auto& p : produse)
		{
			if (p.getTip() == tip && p.getBrand() == brand && p.getConsum() == consum)
			{
				txtCod->setText(QString::number(p.getCod()));
				break;
			}
		}
		});
}

void GUI::loadData(vector<Produs> produse)
{
	tableWidget->clear();
	QStringList columns = { "Tip", "Brand", "Consum energetic (kWh)" };
	tableWidget->setHorizontalHeaderLabels(columns);
	tableWidget->setRowCount(produse.size());
	int index = 0;
	for (const auto& p : produse)
	{
		QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(p.getTip()));
		QTableWidgetItem* itemBrand = new QTableWidgetItem(QString::fromStdString(p.getBrand()));
		QTableWidgetItem* itemConsum = new QTableWidgetItem(QString::number(p.getConsum()));

		tableWidget->setItem(index, 0, itemTip);
		tableWidget->setItem(index, 1, itemBrand);
		tableWidget->setItem(index, 2, itemConsum);

		if (p.getTip() == "frigider")
		{
			itemTip->setBackground(QBrush("cyan"));
			itemBrand->setBackground(QBrush("cyan"));
			itemConsum->setBackground(QBrush("cyan"));
		}
		else if (p.getTip() == "aragaz")
		{
			itemTip->setBackground(QBrush("gray"));
			itemBrand->setBackground(QBrush("gray"));
			itemConsum->setBackground(QBrush("gray"));
		}
		else if (p.getTip() == "cuptor")
		{
			itemTip->setBackground(QBrush("magenta"));
			itemBrand->setBackground(QBrush("magenta"));
			itemConsum->setBackground(QBrush("magenta"));
		}
		else
		{
			itemTip->setBackground(QBrush("green"));
			itemBrand->setBackground(QBrush("green"));
			itemConsum->setBackground(QBrush("green"));
		}
		index++;
	}
}
