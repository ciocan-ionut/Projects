#pragma once

#include "ChatService.h"

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qregularexpression.h>

class LoginWindow;

class MainWindow;

class SignUpWindow : public QWidget
{
	ChatService& service;

	MainWindow* mainWindow = nullptr;

	LoginWindow* loginWindow = nullptr;

	QLineEdit* usernameInput;
	QLabel* feedbackUsrInput;
	QLineEdit* passwdInput;
	QLabel* feedbackPswdInput;
	QLineEdit* confPasswdInput;
	QLabel* feedbackConfPswdInput;
	QPushButton* signUpBtn;

	QPushButton* backToLoginBtn;

	QRegularExpression regexUser{ "^[a-zA-Z0-9-]+$" };
	QRegularExpression regexPswd{ "^[a-zA-Z0-9!@#$&]+$" };
	bool isUsernameValid = false;
	bool isPasswordValid = false;
	bool isConfPswdValid = false;

	/// Function that initializes GUI components
	void initGUI();

	/// Function that connects signals to the GUI components
	void connectSignals();
	
public:
	/// Class constructor
	SignUpWindow(ChatService& service);

	/// Function that setups the connection with the main application window and the user log-in window
	/// @param main - main application window
	/// @param login - user log-in window
	void setupWindows(MainWindow* main, LoginWindow* login);
};

