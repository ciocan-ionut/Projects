#include "FilterWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>


void FilterWindow::initGUI()
{
	listaFiltrata = new QListWidget;

	listViewModel = new ListViewModel();
	listViewModel->setActivitati(serv.getActivitatiService());
	listView = new QListView();
	listView->setModel(listViewModel);

	txtDescriere = new QLineEdit;
	txtTip = new QLineEdit;

	QHBoxLayout* btnFilterLayout = new QHBoxLayout;
	btnFilterDescriere = new QPushButton("Filtrare descriere");
	btnFilterTip = new QPushButton("Filtrare tip");
	btnFilterLayout->addWidget(btnFilterDescriere);
	btnFilterLayout->addWidget(btnFilterTip);

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("Descriere:", txtDescriere);
	formLayout->addRow("Tip:", txtTip);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	// mainLayout->addWidget(listaFiltrata);
	mainLayout->addWidget(listView);
	mainLayout->addLayout(formLayout);
	mainLayout->addLayout(btnFilterLayout);

	setLayout(mainLayout);
	setWindowTitle("Activitati - Filtrare");
}

void FilterWindow::connectSignals()
{
	QObject::connect(btnFilterDescriere, &QPushButton::clicked, [&]() {
		try {
			auto listaFiltrata = serv.filterService(&Activitate::getDescriere,txtDescriere->text().toStdString());
			// loadList(listaFiltrata);
			listViewModel->setActivitati(listaFiltrata);
		}
		catch (BaseException& ex) {
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});
	QObject::connect(btnFilterTip, &QPushButton::clicked, [&]() {
		try {
			auto listaFiltrata = serv.filterService(&Activitate::getTip, txtTip->text().toStdString());
			// loadList(listaFiltrata);
			listViewModel->setActivitati(listaFiltrata);
		}
		catch (BaseException& ex) {
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});
}

void FilterWindow::loadList(const std::vector<Activitate>& activitati)
{
	listaFiltrata->clear();
	for (const auto& act : activitati) {
		listaFiltrata->addItem(QString::fromStdString(
			act.getTitlu() + " | " + act.getDescriere() + " | " + act.getTip() + " | " + std::to_string(act.getDurata())));
	}
}