#include "GUI.h"
#include "Jocuri.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

void GUI::initGUI()
{
	setWindowTitle("Jocuri");
	setMinimumSize(800, 600);

	tableWidget = new QTableWidget();
	tableWidget->setColumnCount(2);

	ratingLabel = new QLabel("Rating: ");
	sortButton = new QPushButton("Sortare Pret");
	filterButton = new QPushButton("Jocuri recomandate pentru copii", this);
	refreshButton = new QPushButton("Refresh", this);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(sortButton);
	buttonLayout->addWidget(filterButton);
	buttonLayout->addWidget(refreshButton);
	mainLayout->addWidget(tableWidget);
	mainLayout->addWidget(ratingLabel);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}

void GUI::connectSignals()
{
	connect(sortButton, &QPushButton::clicked, this, [&]() {
		loadList(jocuri.sortJocuri());
		});
	connect(filterButton, &QPushButton::clicked, this, [&]() {
		loadList(jocuri.filterJocuri());
		});
	connect(refreshButton, &QPushButton::clicked, this, [&]() {
		loadList(jocuri.getJocuri());
		});
	connect(tableWidget, &QTableWidget::itemSelectionChanged, this, [&]() {
		int row = tableWidget->currentRow();
		if (row >= 0)
		{
			string titlu = tableWidget->item(row, 0)->text().toStdString();
			const auto& getJocuri = jocuri.getJocuri();
			auto it = find_if(getJocuri.begin(), getJocuri.end(), [=](const Joc& joc) {
				return joc.getTitlu() == titlu;
				});
			if (it != getJocuri.end())
				ratingLabel->setText("Rating: " + QString::number(it->getRating()));
		}
		});
}

void GUI::loadList(vector<Joc> jocuri)
{
	tableWidget->clear();
	const QStringList columns = { "Titlu", "Pret" };
	tableWidget->setHorizontalHeaderLabels(columns);
	tableWidget->setRowCount((int)jocuri.size());
	for (int i = 0; i < jocuri.size(); ++i)
	{
		QTableWidgetItem* itemTitlu = new QTableWidgetItem(QString::fromStdString(jocuri[i].getTitlu()));
		QTableWidgetItem* itemPret = new QTableWidgetItem(QString::number(jocuri[i].getPret()));
		if (jocuri[i].getPlatforma() == "PC")
		{
			itemTitlu->setBackground(Qt::black);
			itemPret->setBackground(Qt::black);
		}
		else if (jocuri[i].getPlatforma() == "Xbox")
		{
			itemTitlu->setBackground(Qt::green);
			itemPret->setBackground(Qt::green);
		}
		else if (jocuri[i].getPlatforma() == "Playstation")
		{
			itemTitlu->setBackground(Qt::blue);
			itemPret->setBackground(Qt::blue);
		}
		else
		{
			itemTitlu->setBackground(Qt::red);
			itemPret->setBackground(Qt::red);
		}
		tableWidget->setItem(i, 0, itemTitlu);
		tableWidget->setItem(i, 1, itemPret);
	}
}