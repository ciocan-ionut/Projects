#include "ProfileWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qmessagebox.h>

ProfileWindow::ProfileWindow(ChatService& service) : service{ service }
{
	initGUI();
	connectSignals();
}

void ProfileWindow::initGUI()
{
	QHBoxLayout* mainLy = new QHBoxLayout(this);

	QLabel* pfpLbl = new QLabel(this);
	QIcon pfpIcon(":/MiChat/MiChatProfil.png");
	pfpLbl->setPixmap(pfpIcon.pixmap(128, 128));
	mainLy->addWidget(pfpLbl);

	QFormLayout* contentLy = new QFormLayout(this);
	usernameInput = new QLineEdit(this);
	usernameInput->setReadOnly(true);
	contentLy->addRow("Username:", usernameInput);

	passwordInput = new QLineEdit(this);
	passwordInput->setReadOnly(true);
	passwordInput->setEchoMode(QLineEdit::Password);
	showPasswordBtn = new QPushButton("Show", this);
	QWidget* passwordWidget = new QWidget(this);
	QHBoxLayout* passWidgetLy = new QHBoxLayout(this);
	passWidgetLy->setContentsMargins(0, 0, 0, 0);
	passWidgetLy->addWidget(passwordInput);
	passWidgetLy->addWidget(showPasswordBtn);
	passwordWidget->setLayout(passWidgetLy);
	contentLy->addRow("Password:", passwordWidget);

	changePassInput = new QLineEdit(this);
	changePassInput->setEchoMode(QLineEdit::Password);
	changePassBtn = new QPushButton("Change", this);
	QWidget* changePassWidget = new QWidget(this);
	QHBoxLayout* changePassWidgetLy = new QHBoxLayout(this);
	changePassWidgetLy->setContentsMargins(0, 0, 0, 0);
	changePassWidgetLy->addWidget(changePassInput);
	changePassWidgetLy->addWidget(changePassBtn);
	changePassWidget->setLayout(changePassWidgetLy);
	contentLy->addRow("New Password:", changePassWidget);

	feedbackPswdInput = new QLabel(this);
	contentLy->addWidget(feedbackPswdInput);

	mainLy->addLayout(contentLy);
	setLayout(mainLy);
	setWindowTitle("Profile");
	setFixedSize(540, 150);
}

void ProfileWindow::connectSignals()
{
	// Updates the input with the password received from ChatService
	QObject::connect(&service, &ChatService::updateProfileWindowUISignal, [&](const QString& password) {
		passwordInput->setText(password);
		});

	// Shows the password when the button is pressed
	QObject::connect(showPasswordBtn, &QPushButton::pressed, [&]() {
		passwordInput->setEchoMode(QLineEdit::Normal);
		});

	// Hides the password when the button is released
	QObject::connect(showPasswordBtn, &QPushButton::released, [&]() {
		passwordInput->setEchoMode(QLineEdit::Password);
		});

	// Providing feedback on the password based on the current input
	QObject::connect(changePassInput, &QLineEdit::textChanged, [&]() {
		QString password = changePassInput->text();
		if (password.size() < 8)
		{
			feedbackPswdInput->setText("Password too short!");
			isPasswordValid = false;
		}
		else if (!regexPswd.match(password).hasMatch())
		{
			feedbackPswdInput->setText("Password can only contain letters, digits, and ! @ # $ &");
			isPasswordValid = false;
		}
		else
		{
			feedbackPswdInput->clear();
			isPasswordValid = true;
		}
		});

	// Changes the password if it's valid and shows a confirmation message box
	QObject::connect(changePassBtn, &QPushButton::clicked, [&]() {
		if (isPasswordValid)
		{
			QString newPassword = changePassInput->text();
			service.changePassword(newPassword);

			changePassInput->clear();
			feedbackPswdInput->clear();
			QMessageBox::information(this, "Succes!", "The password has been succesfully changed!");
		}
		});
}

void ProfileWindow::showEvent(QShowEvent* event)
{
	QString username = service.getLoggedInUser();
	usernameInput->setText(username);
	QWidget::showEvent(event);
}