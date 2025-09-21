#include "LoginWindow.h"
#include "MainWindow.h"
#include "SignUpWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qmessagebox.h>

LoginWindow::LoginWindow(ChatService& service) : service{ service }
{
	initGUI();
	connectSignals();
}

void LoginWindow::setupWindows(MainWindow* main, SignUpWindow* signup)
{
	mainWindow = main;
	signUpWindow = signup;
}

void LoginWindow::initGUI()
{
	QVBoxLayout* mainLy = new QVBoxLayout(this);

	QLabel* loginTitleLbl = new QLabel("Login", this);
	QFont fontLbl = loginTitleLbl->font();
	fontLbl.setBold(true);
	fontLbl.setPointSize(24);
	loginTitleLbl->setFont(fontLbl);
	loginTitleLbl->setAlignment(Qt::AlignHCenter);
	mainLy->addWidget(loginTitleLbl);

	mainLy->addStretch();

	QFormLayout* contentLy = new QFormLayout(this);

	usernameInput = new QLineEdit(this);
	contentLy->addRow("Username:", usernameInput);

	passwdInput = new QLineEdit(this);
	passwdInput->setEchoMode(QLineEdit::Password);
	contentLy->addRow("Password:", passwdInput);

	mainLy->addLayout(contentLy);

	loginBtn = new QPushButton("Login", this);
	mainLy->addWidget(loginBtn);

	QFormLayout* redirectToSignUpLy = new QFormLayout(this);
	redirectToSignUpBtn = new QPushButton("Sign Up", this);
	redirectToSignUpLy->addRow("New here? Create your account:", redirectToSignUpBtn);
	
	mainLy->addStretch();
	mainLy->addLayout(redirectToSignUpLy);

	setLayout(mainLy);
	setFixedSize(300, 300);
	setWindowTitle("Welcome to MiChat");
}

void LoginWindow::connectSignals()
{
	// Showing a warning message box with the specific error received from ChatService
	QObject::connect(&service, &ChatService::errorOnLoginUISignal, [&](const QString& errMessage) {
		QMessageBox::warning(this, "Error", errMessage);
		});

	// Hiding the current window and showing the main window if the login was succesful
	QObject::connect(&service, &ChatService::succesfulLoginUISignal, [&](const QString& username) {
		service.setLoggedInUser(username);
		hide();
		mainWindow->show();

		usernameInput->clear();
		passwdInput->clear();
		});

	// Extracting and validating the login credentials when the login button is pressed
	QObject::connect(loginBtn, &QPushButton::clicked, [&]() {
		QString username = usernameInput->text();
		QString password = passwdInput->text();
		service.validateAndLoginUser(username, password); 
		});

	// Hiding the current window and showing the signup window when the signup redirect button is pressed
	QObject::connect(redirectToSignUpBtn, &QPushButton::clicked, [&]() {
		hide();
		signUpWindow->show();

		usernameInput->clear();
		passwdInput->clear();
		});
}