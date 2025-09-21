#include "SignUpWindow.h"
#include "MainWindow.h"
#include "LoginWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qmessagebox.h>

SignUpWindow::SignUpWindow(ChatService& service) : service{ service }
{
	initGUI();
	connectSignals();
}

void SignUpWindow::setupWindows(MainWindow* main, LoginWindow* login)
{
	mainWindow = main;
	loginWindow = login;
}

void SignUpWindow::initGUI()
{
	QVBoxLayout* mainLy = new QVBoxLayout(this);

	QLabel* signInTitleLbl = new QLabel("Sign Up", this);
	QFont fontLbl = signInTitleLbl->font();
	fontLbl.setBold(true);
	fontLbl.setPointSize(24);
	signInTitleLbl->setFont(fontLbl);
	signInTitleLbl->setAlignment(Qt::AlignHCenter);

	mainLy->addWidget(signInTitleLbl);
	mainLy->addStretch();

	QFormLayout* contentLy = new QFormLayout(this);

	usernameInput = new QLineEdit(this);
	contentLy->addRow("Username:", usernameInput);
	feedbackUsrInput = new QLabel(this);
	fontLbl = feedbackUsrInput->font();
	fontLbl.setPointSize(10);
	feedbackUsrInput->setFont(fontLbl);
	contentLy->addWidget(feedbackUsrInput);

	passwdInput = new QLineEdit(this);
	passwdInput->setEchoMode(QLineEdit::Password);
	contentLy->addRow("Password:", passwdInput);
	feedbackPswdInput = new QLabel(this);
	fontLbl = feedbackPswdInput->font();
	fontLbl.setPointSize(10);
	feedbackPswdInput->setFont(fontLbl);
	contentLy->addWidget(feedbackPswdInput);

	confPasswdInput = new QLineEdit(this);
	confPasswdInput->setEchoMode(QLineEdit::Password);
	contentLy->addRow("Confirm Password:", confPasswdInput);
	feedbackConfPswdInput = new QLabel(this);
	fontLbl = feedbackConfPswdInput->font();
	fontLbl.setPointSize(10);
	feedbackConfPswdInput->setFont(fontLbl);
	contentLy->addWidget(feedbackConfPswdInput);

	mainLy->addLayout(contentLy);

	signUpBtn = new QPushButton("Sign Up", this);
	mainLy->addWidget(signUpBtn);

	QFormLayout* backToLoginLy = new QFormLayout(this);
	backToLoginBtn = new QPushButton("Login", this);
	backToLoginLy->addRow("Not new? Login here:", backToLoginBtn);

	mainLy->addStretch();
	mainLy->addLayout(backToLoginLy);

	setLayout(mainLy);
	setFixedSize(460, 300);
	setWindowTitle("Welcome to MiChat");
}

void SignUpWindow::connectSignals()
{
	// Showing a warning message box with the specific error received from ChatService
	QObject::connect(&service, &ChatService::errorOnSignupUISignal, [&](const QString& errMessage) {
		QMessageBox::warning(this, "Error", errMessage);
		});

	// Hiding the current window and showing the main window if the signup was succesful
	QObject::connect(&service, &ChatService::succesfulSignupUISignal, [&](const QString& username) {
		service.setLoggedInUser(username); 
		hide();
		mainWindow->show();

		usernameInput->clear();
		passwdInput->clear();
		confPasswdInput->clear();
		});

	// Providing feedback on the username based on the current input
	QObject::connect(usernameInput, &QLineEdit::textChanged, [&]() {
		QString username = usernameInput->text();
		if (username.size() < 4)
		{
			feedbackUsrInput->setText("Username too short!");
			isUsernameValid = false;
		}
		else if (!regexUser.match(username).hasMatch())
		{
			feedbackUsrInput->setText("Username can only contain letters, digits and -");
			isUsernameValid = false;
		}
		else
		{
			feedbackUsrInput->clear();
			isUsernameValid = true;
		}
		});

	// Providing feedback on the password based on the current input
	QObject::connect(passwdInput, &QLineEdit::textChanged, [&]() {
		QString password = passwdInput->text();
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

	// Providing feedback on the password confirmation based on the current input
	QObject::connect(confPasswdInput, &QLineEdit::textChanged, [&]() {
		QString password = passwdInput->text();
		QString confirmPassword = confPasswdInput->text();
		if (password != confirmPassword)
		{
			feedbackConfPswdInput->setText("Passwords do not match!");
			isConfPswdValid = false;
		}
		else
		{
			feedbackConfPswdInput->clear();
			isConfPswdValid = true;
		}
		});

	// Extracting and validating the signup credentials when the signup button is pressed
	QObject::connect(signUpBtn, &QPushButton::clicked, [&]() {
		if (isUsernameValid && isPasswordValid && isConfPswdValid)
		{
			QString username = usernameInput->text();
			QString password = passwdInput->text();
			service.validateAndSignupUser(username, password);
		}
		});

	// Hiding the current window and showing the login window when the login redirect button is pressed
	QObject::connect(backToLoginBtn, &QPushButton::clicked, [&]() {
		hide();
		loginWindow->show();

		usernameInput->clear();
		feedbackUsrInput->clear();
		passwdInput->clear();
		feedbackPswdInput->clear();
		confPasswdInput->clear();
		});
}