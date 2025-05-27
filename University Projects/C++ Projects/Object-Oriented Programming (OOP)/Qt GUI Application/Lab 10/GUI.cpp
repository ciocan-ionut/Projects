#include "GUI.h"
#include "CosReadOnlyWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <qlabel.h>

/// Functie care initializeaza obiectele pentru crearea paginii principale
void GUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout;

	QHBoxLayout* contentLayout = new QHBoxLayout;
    // listaActivitati = new QListWidget;

	listViewModel = new ListViewModel();
	listViewModel->setActivitati(serv.getActivitatiService());
	listView = new QListView();
	listView->setModel(listViewModel);

    tableViewModel = new TableViewModel();
	tableViewModel->setActivitati(serv.getActivitatiService());
	tableView = new QTableView();
	tableView->setModel(tableViewModel);

	// tabelActivitati = new QTableWidget(4, 4);
    // const QStringList columns = { "Titlu", "Descriere", "Tip", "Durata" };
    // tabelActivitati->setHorizontalHeaderLabels(columns);
	// contentLayout->addWidget(listaActivitati);
	// contentLayout->addWidget(tabelActivitati);

	contentLayout->addWidget(listView);
	contentLayout->addWidget(tableView);

    txtTitlu = new QLineEdit;
    txtDescriere = new QLineEdit;
    txtTip = new QLineEdit;
    txtDurata = new QLineEdit;

	btnExit = new QPushButton("Iesire");
	btnCos = new QPushButton("Cos");

    btnAdd = new QPushButton("Adauga");
    btnDelete = new QPushButton("Sterge");
    btnModify = new QPushButton("Modifica");
    btnReload = new QPushButton("Reincarca");
    btnUndo = new QPushButton("Undo");

	btnSort = new QPushButton("Sortare");
	btnFilter = new QPushButton("Filtrare");
	btnRaport = new QPushButton("Raport");

	QHBoxLayout* btnCosFirstLayout = new QHBoxLayout;
	btnGenerate = new QPushButton("Genereaza activitati");
    btnGenerate->setMinimumWidth(200);
	txtGenerate = new QLineEdit;
	btnCosFirstLayout->addWidget(btnGenerate);
	btnCosFirstLayout->addWidget(txtGenerate);

	QHBoxLayout* btnCosSecondLayout = new QHBoxLayout;
	btnAddInCos = new QPushButton("Adauga in cos");
	btnEmptyCos = new QPushButton("Goleste cos");
	btnCosSecondLayout->addWidget(btnAddInCos);
	btnCosSecondLayout->addWidget(btnEmptyCos);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Titlu:", txtTitlu);
    formLayout->addRow("Descriere:", txtDescriere);
    formLayout->addRow("Tip:", txtTip);
    formLayout->addRow("Durata:", txtDurata);

	QHBoxLayout* btnFirstRowLayout = new QHBoxLayout;
	btnFirstRowLayout->addWidget(btnExit);
	btnFirstRowLayout->addStretch();
	btnFirstRowLayout->addWidget(btnCos);

    QHBoxLayout* btnSecondRowLayout = new QHBoxLayout;
    btnSecondRowLayout->addWidget(btnAdd);
    btnSecondRowLayout->addWidget(btnDelete);
    btnSecondRowLayout->addWidget(btnModify);
    btnSecondRowLayout->addWidget(btnReload);
    btnSecondRowLayout->addWidget(btnUndo);

	QHBoxLayout* btnThirdRowLayout = new QHBoxLayout;
    btnThirdRowLayout->addWidget(btnSort);
	btnThirdRowLayout->addWidget(btnFilter);
	btnThirdRowLayout->addWidget(btnRaport);

	mainLayout->addLayout(btnFirstRowLayout);
    mainLayout->addLayout(contentLayout);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnSecondRowLayout);
	mainLayout->addLayout(btnThirdRowLayout);
	mainLayout->addLayout(btnCosFirstLayout);
	mainLayout->addLayout(btnCosSecondLayout);

    setLayout(mainLayout);
    setWindowTitle("Activitati - GUI");
	setMinimumSize(800, 600);
}

/// Functie care contine functiile care creeaza legatura dintre utilizator si functionalitati
void GUI::connectSignals() {
    QObject::connect(btnReload, &QPushButton::clicked, [&]() {
        try
        {
			ignoreSelectionChange = false;
			tableViewModel->setActivitati(serv.getActivitatiService());
			listViewModel->setActivitati(serv.getActivitatiService());
            // loadList(serv.getActivitatiService());
        }
        catch (const BaseException& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });

    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        try {
            string titlu = txtTitlu->text().toStdString();
            string descriere = txtDescriere->text().toStdString();
            string tip = txtTip->text().toStdString();
            int durata = txtDurata->text().toInt();
            serv.addService(titlu, descriere, tip, durata);
            // loadList(serv.getActivitatiService());

            tableViewModel->setActivitati(serv.getActivitatiService());
			listViewModel->setActivitati(serv.getActivitatiService());

            txtTitlu->clear();
            txtDescriere->clear();
            txtTip->clear();
            txtDurata->clear();
        }
        catch (const BaseException& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });

    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        try {
            auto selected = listView->currentIndex();
            if (!selected.isValid())
                throw BaseException("Selectati o activitate!");
            auto selectedIndex = selected.row();

            serv.deleteService(selectedIndex);
            ignoreSelectionChange = true;
            // loadList(serv.getActivitatiService());
            tableViewModel->setActivitati(serv.getActivitatiService());
			listViewModel->setActivitati(serv.getActivitatiService());

            ignoreSelectionChange = false;
            txtTitlu->clear();
            txtDescriere->clear();
            txtTip->clear();
            txtDurata->clear();
        }
        catch (const BaseException& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }

        });

    // QObject::connect(listaActivitati, &QListWidget::itemSelectionChanged, [&]() {
    QObject::connect(listView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (ignoreSelectionChange)
			return;

        auto selected = listView->currentIndex();
        if (!selected.isValid())
            return;
        auto selectedIndex = selected.row();
        // int selectedIndex = listaActivitati->currentRow();

        const auto& activitati = serv.getActivitatiService();
        const auto& act = activitati[selectedIndex];

        txtTitlu->setText(QString::fromStdString(act.getTitlu()));
        txtDescriere->setText(QString::fromStdString(act.getDescriere()));
        txtTip->setText(QString::fromStdString(act.getTip()));
        txtDurata->setText(QString::number(act.getDurata()));
        });

    QObject::connect(btnModify, &QPushButton::clicked, [&]() {
        try {
            auto selected = listView->currentIndex();
            if (!selected.isValid())
                throw BaseException("Selectati o activitate!");
			auto selectedIndex = selected.row();

            string titlu = txtTitlu->text().toStdString();
            string descriere = txtDescriere->text().toStdString();
            string tip = txtTip->text().toStdString();
            int durata;
			if (txtDurata->text().isEmpty())
				durata = -1;
			else
                durata = txtDurata->text().toInt();

            serv.modifyService(
                selectedIndex,
                txtTitlu->text().toStdString(),
                txtDescriere->text().toStdString(),
                txtTip->text().toStdString(),
                txtDurata->text().toInt()
            );
            // loadList(serv.getActivitatiService());
            tableViewModel->setActivitati(serv.getActivitatiService());
			listViewModel->setActivitati(serv.getActivitatiService());

            txtTitlu->clear();
            txtDescriere->clear();
            txtTip->clear();
            txtDurata->clear();
        }
        catch (const BaseException& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });

	QObject::connect(btnSort, &QPushButton::clicked, [&]() {
        if(sortWindow && sortWindow->isVisible())
            QMessageBox::warning(this, "Eroare", "Fereastra este deja deschisa!");
        else
        {
            sortWindow = new SortWindow(serv);
            sortWindow->show();
        }
		});

    QObject::connect(sortWindow, &SortWindow::destroyed, [&]() {
        sortWindow = nullptr;
        });

    QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
		if (filterWindow && filterWindow->isVisible())
			QMessageBox::warning(this, "Eroare", "Fereastra este deja deschisa!");
        else
        {
            filterWindow = new FilterWindow(serv);
            filterWindow->show();
        }
        });

	QObject::connect(filterWindow, &FilterWindow::destroyed, [&]() {
		filterWindow = nullptr;
		});

    QObject::connect(btnCos, &QPushButton::clicked, [&]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Cos");
        msgBox.setText("Cum vrei să deschizi coșul?");

        QPushButton* crudButton = msgBox.addButton("CRUD", QMessageBox::AcceptRole);
        QPushButton* readOnlyButton = msgBox.addButton("ReadOnly", QMessageBox::AcceptRole);
        msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == crudButton) {
            cosWindow = new CosWindow(serv);
            cosWindow->show();
        }
        else if (msgBox.clickedButton() == readOnlyButton) {
            auto* cosWindow = new CosReadOnlyWindow(serv);
            cosWindow->show();
        }
        });

	QObject::connect(cosWindow, &CosWindow::destroyed, [&]() {
		cosWindow = nullptr;
		});

    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		serv.saveToFile();

		if (sortWindow)
			sortWindow->close();
		if (filterWindow)
			filterWindow->close();
		if (cosWindow)
			cosWindow->close();
		this->close();
		});

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try
        {
            serv.undo();
			// loadList(serv.getActivitatiService());
            tableViewModel->setActivitati(serv.getActivitatiService());
            listViewModel->setActivitati(serv.getActivitatiService());
        }
		catch (const BaseException& ex) {
			QMessageBox::warning(this, "Eroare", ex.what());
		}
        });

	QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
		try
		{
			ignoreSelectionChange = true;

			auto raport = serv.createMap();
			// loadRaport(raport);
		}
		catch (const BaseException& ex) 
        {
			QMessageBox::warning(this, "Eroare", ex.what());
		}
		});

    QObject::connect(btnEmptyCos, &QPushButton::clicked, [&]() {
        serv.emptyCos();
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
                tableViewModel->setActivitati(serv.getActivitatiService());
            }
            txtGenerate->clear();
        }
        catch (BaseException& ex)
        {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });

    QObject::connect(btnAddInCos, &QPushButton::clicked, [&]() {
        try
        {
            auto index = listView->currentIndex();
            if (!index.isValid())
                throw BaseException("Selectati o activitate!");
            auto activitati = serv.getActivitatiService();
            auto act = activitati[index.row()];
            serv.addInCos(act.getTitlu());
        }
        catch (BaseException& ex)
        {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });
}

/// Functie care populeaza listaActivitati cu activitatile din "activitati"
/// @param activitati este lista de activitati
void GUI::loadList(const std::vector<Activitate>& activitati) {
    listaActivitati->clear();
    int index = 0;
    for (const auto& act : activitati) {
        QWidget* lista = new QWidget;
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel* label = new QLabel(QString::fromStdString(
            act.getTitlu() + " | " + act.getDescriere() + " | " + act.getTip() + " | " + std::to_string(act.getDurata())));
        QPushButton* info = new QPushButton("Info");

        connect(info, &QPushButton::clicked, this, [=]() {
            QMessageBox::information(nullptr, "Informatii", QString::fromStdString("Tipul activitatii este: " + act.getTip()));
                });

        layout->addWidget(label);
		layout->addStretch();
		info->setFixedSize(80, 25);
        layout->addWidget(info);
        lista->setLayout(layout);

        QListWidgetItem* item = new QListWidgetItem(listaActivitati);
        item->setSizeHint(lista->sizeHint());
        listaActivitati->addItem(item);
        listaActivitati->setItemWidget(item, lista);

        // tabelActivitati->setRowCount((int)serv.getActivitatiService().size());
		// QTableWidgetItem* actTitlu = new QTableWidgetItem(QString::fromStdString(act.getTitlu()));
		// QTableWidgetItem* actDescriere = new QTableWidgetItem(QString::fromStdString(act.getDescriere()));
		// QTableWidgetItem* actTip = new QTableWidgetItem(QString::fromStdString(act.getTip()));
		// QTableWidgetItem* actDurata = new QTableWidgetItem(QString::number(act.getDurata()));
		// tabelActivitati->setItem(index, 0, actTitlu);
		// tabelActivitati->setItem(index, 1, actDescriere);
		// tabelActivitati->setItem(index, 2, actTip);
		// tabelActivitati->setItem(index, 3, actDurata);
		// index++;
    }
}

/// Functie care populeaza listaActivitati cu activitatile din raport
/// @param raport este un map care contine activitatile
void GUI::loadRaport(const std::map<string, DTO>& raport)
{
	listaActivitati->clear();
	for (const auto& act : raport)
	{
		listaActivitati->addItem(QString::fromStdString(
			"Tip: " + act.second.getTip() + " | Cantitate: " + std::to_string(act.second.getCantitate())));
	}
}