#include "SortWindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

void SortWindow::initGUI()
{
	listaSortata = new QListWidget;

	listViewModel = new ListViewModel();
	listViewModel->setActivitati(serv.getActivitatiService());
	listView = new QListView();
	listView->setModel(listViewModel);

	QHBoxLayout* btnSortLayout = new QHBoxLayout;
	btnSortTitlu = new QPushButton();
	btnSortDescriere = new QPushButton();
	btnSortTipDurata = new QPushButton();
	checkBoxSort = new QCheckBox("Crescator");

	btnSortTitlu->setMinimumWidth(90);
	btnSortLayout->addWidget(btnSortTitlu);
	btnSortDescriere->setMinimumWidth(90);
	btnSortLayout->addWidget(btnSortDescriere);
	btnSortTipDurata->setMinimumWidth(90);
	btnSortLayout->addWidget(btnSortTipDurata);
	btnSortLayout->addWidget(checkBoxSort);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	// mainLayout->addWidget(listaSortata);
	mainLayout->addWidget(listView);
	mainLayout->addLayout(btnSortLayout);

	setLayout(mainLayout);
	setWindowTitle("Activitati - Sortare");
}

void SortWindow::connectSignals()
{
	QObject::connect(btnSortTitlu, &QPushButton::clicked, [&]() {
		try 
		{
			auto listaSortata = serv.sortedService(&Activitate::compareTitlu, checkBoxSort->isChecked());
			// loadList(listaSortata);
			listViewModel->setActivitati(listaSortata);
		}
		catch (BaseException& ex) 
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});

	QObject::connect(btnSortDescriere, &QPushButton::clicked, [&]() {
		try 
		{
			auto listaSortata = serv.sortedService(&Activitate::compareDescriere, checkBoxSort->isChecked());
			// loadList(listaSortata);
			listViewModel->setActivitati(listaSortata);
		}
		catch (BaseException& ex) 
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});

	QObject::connect(btnSortTipDurata, &QPushButton::clicked, [&]() {
		try 
		{
			auto listaSortata = serv.sortedService(&Activitate::compareTipSiDurata, checkBoxSort->isChecked());
			// loadList(listaSortata);
			listViewModel->setActivitati(listaSortata);
		}
		catch (BaseException& ex) 
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});
}

void SortWindow::loadList(const std::vector<Activitate>& activitati)
{
	listaSortata->clear();
	for (const auto& act : activitati) 
	{
		listaSortata->addItem(QString::fromStdString(
			act.getTitlu() + " | " + act.getDescriere() + " | " + act.getTip() + " | " + std::to_string(act.getDurata())));
	}
}

void SortWindow::resizeEvent(QResizeEvent* event)
{
	int width = this->width();
	if (width <= 600)
	{
		btnSortTitlu->setText("Sortare\ntitlu");
		btnSortDescriere->setText("Sortare\ndescriere");
		btnSortTipDurata->setText("Sortare\ntip + durata");
	}
	else
	{
		btnSortTitlu->setText("Sortare titlu");
		btnSortDescriere->setText("Sortare descriere");
		btnSortTipDurata->setText("Sortare tip + durata");
	}
	QWidget::resizeEvent(event);
}