#include "GUI.h"

#include <QHBoxLayout>

void GUI::initGUI()
{
	listWidget = new QListWidget;
	btnSortModel = new QPushButton("Sortare Model");
	btnSortAn = new QPushButton("Sortare An");
	btnRefresh = new QPushButton("Refresh");
	txtModel = new QLineEdit;
	txtAn = new QLineEdit;
	auto mainLayout = new QFormLayout;
	mainLayout->addRow("Devices", listWidget);
	mainLayout->addRow("Model", txtModel);
	mainLayout->addRow("Year", txtAn);
	auto btnLayout = new QHBoxLayout;
	btnLayout->addWidget(btnSortModel);
	btnLayout->addWidget(btnSortAn);
	btnLayout->addWidget(btnRefresh);
	mainLayout->addRow(btnLayout);
	setLayout(mainLayout);
	setWindowTitle("Device Manager");
}

void GUI::connectSignals()
{
	QObject::connect(btnSortModel, &QPushButton::clicked, [&]() {
		loadData(firma.sortModel());
		});
	QObject::connect(btnSortAn, &QPushButton::clicked, [&]() {
		loadData(firma.sortAn());
		});
	QObject::connect(btnRefresh, &QPushButton::clicked, [&]() {
		loadData(firma.getDevices());
		});
	QObject::connect(listWidget, &QListWidget::itemClicked, [&](QListWidgetItem* item) {
		QString text = item->text();
		QStringList parts = text.split(",");
		auto devices = firma.getDevices();
		auto it = find_if(devices.begin(), devices.end(), [&](const Device& device) {
			return device.getModel() == parts[0].toStdString() && device.getCuloare() == parts[1].toStdString();
			});
		txtModel->setText(QString::fromStdString(it->getModel()));
		txtAn->setText(QString::number(it->getAn()));
		});
}

void GUI::loadData(vector<Device> devices)
{
	listWidget->clear();
	for (const auto& device : devices)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(device.getModel() + "," + device.getCuloare() + "," + to_string(device.getPret())));
		if(device.getCuloare() == "negru")
			item->setBackground(Qt::black);
		else if (device.getCuloare() == "galben")
			item->setBackground(Qt::yellow);
		else if (device.getCuloare() == "rosu")
			item->setBackground(Qt::red);
		else if (device.getCuloare() == "albastru")
			item->setBackground(Qt::blue);
		listWidget->addItem(item);
	}
}