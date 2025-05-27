#include "CosWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <regex>

void CosWindow::initGUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout;

	listaCos = new QListWidget;

	listViewModel = new ListViewModel();
	listViewModel->setActivitati(serv.getActivitatiService());
	listView = new QListView();
	listView->setModel(listViewModel);

	try
	{
		lblCos = new QLabel("Cos: " + QString::number(serv.getActivitatiCosService().size()));
	}
	catch (BaseException)
	{
		lblCos = new QLabel("Cos: 0");
	}	

	txtGenerate = new QLineEdit;
	txtExport = new QLineEdit;

	btnEmptyCos = new QPushButton("Goleste cos");
	btnGenerate = new QPushButton("Genereaza activitati");
	btnExport = new QPushButton("Exporta cos (CSV)");
	btnAddInCos = new QPushButton("Adauga in cos");

	QHBoxLayout* btnFirstRowLayout = new QHBoxLayout;
	btnFirstRowLayout->addStretch();
	btnEmptyCos->setMinimumWidth(90);
	btnFirstRowLayout->addWidget(btnEmptyCos);
	lblCos->setMinimumWidth(50);
	btnFirstRowLayout->addWidget(lblCos);

	QHBoxLayout* btnSecondRowLayout = new QHBoxLayout;
	btnGenerate->setMinimumWidth(130);
	btnSecondRowLayout->addWidget(btnGenerate);
	btnSecondRowLayout->addWidget(txtGenerate);

	QHBoxLayout* btnThirdRowLayout = new QHBoxLayout;
	btnExport->setMinimumWidth(130);
	btnThirdRowLayout->addWidget(btnExport);
	btnThirdRowLayout->addWidget(txtExport);

	QHBoxLayout* btnFourthRowLayout = new QHBoxLayout;
	btnFourthRowLayout->addWidget(btnAddInCos);

	mainLayout->addLayout(btnFirstRowLayout);
	// mainLayout->addWidget(listaCos);
	mainLayout->addWidget(listView);
	mainLayout->addLayout(btnSecondRowLayout);
	mainLayout->addLayout(btnThirdRowLayout);
	mainLayout->addLayout(btnFourthRowLayout);

	setLayout(mainLayout);
	setWindowTitle("Activitati - Cos CRUD");
	setMinimumSize(400, 400);
}

void CosWindow::connectSignals()
{
	QObject::connect(btnAddInCos, &QPushButton::clicked, [&]() {
		try
		{
			auto index = listView->currentIndex();
			if (!index.isValid())
				throw BaseException("Selectati o activitate!");
			auto activitati = serv.getActivitatiService();
			auto act = activitati[index.row()];
			serv.addInCos(act.getTitlu());
			lblCos->setText("Cos: " + QString::number(serv.getActivitatiCosService().size()));
		}
		catch (BaseException& ex)
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});

	QObject::connect(btnEmptyCos, &QPushButton::clicked, [&]() {
		serv.emptyCos();
		lblCos->setText("Cos: 0");
		});

	QObject::connect(btnExport, &QPushButton::clicked, [&]() {
		try
		{
			string fisier = txtExport->text().toStdString();
			if (fisier.empty())
				throw BaseException("Introduceti numele fisierului!");
			regex fisier_valid(R"(.*\.csv$)");
			if (!regex_match(fisier, fisier_valid))
				throw BaseException("Va rog introduceti un nume de fisier cu extensia .csv!");
			serv.exportCosCSV(fisier);
			QMessageBox::information(this, "Export", "Cosul a fost exportat cu succes!");
			txtExport->clear();
		}
		catch (BaseException& ex)
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});

	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		try
		{
			int nr = txtGenerate->text().toInt();
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, "ATENTIE!",
				"Generati un numar aleatoriu de activitati? Veti pierde activitatile curente din lista!",
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				serv.generateActivitati(nr);
				// loadList(serv.getActivitatiService());
				listViewModel->setActivitati(serv.getActivitatiService());
			}
			txtGenerate->clear();
		}
		catch (BaseException& ex)
		{
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});
}

void CosWindow::loadList(const std::vector<Activitate>& activitati)
{
	listaCos->clear();
	for (const auto& act : activitati) {
		QWidget* lista = new QWidget;

		QHBoxLayout* listLayout = new QHBoxLayout;

		QLabel* lblAct = new QLabel(QString::fromStdString(
			act.getTitlu() + " | " + act.getDescriere() + " | " + act.getTip() + " | " + std::to_string(act.getDurata())));

		QPushButton* btnAdd = new QPushButton("Adauga");

		connect(btnAdd, &QPushButton::clicked, this, [=]() {
			serv.addInCos(act.getTitlu());
			lblCos->setText("Cos: " + QString::number(serv.getActivitatiCosService().size()));
			});

		listLayout->addWidget(lblAct);
		listLayout->addStretch();
		btnAdd->setFixedSize(80, 25);
		listLayout->addWidget(btnAdd);
		lista->setLayout(listLayout);

		QListWidgetItem* item = new QListWidgetItem(listaCos);
		item->setSizeHint(lista->sizeHint());
		listaCos->addItem(item);
		listaCos->setItemWidget(item, lista);
	}
}