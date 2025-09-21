#pragma once

#include "ChatService.h"

#include "C:\Qt\6.9.0\msvc2022_64\include\QtWidgets\qwidget.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class SignUpWindow;

class MainWindow;

class LoginWindow : public QWidget
{
private:
	ChatService& service;

	MainWindow* mainWindow = nullptr;

	SignUpWindow* signUpWindow = nullptr;

	QLineEdit* usernameInput;
	QLabel* feedbackUsrInput;
	QLineEdit* passwdInput;
	QLabel* feedbackPswdInput;
	QPushButton* loginBtn;

	QPushButton* redirectToSignUpBtn;

	/// Function that initializes GUI components
	void initGUI();

	/// Function that connects signals to the GUI components
	void connectSignals();

public:
	/// Class constructor
	LoginWindow(ChatService& service);

	/// Function that setups the connection with the main application window and the user sign-up window
	/// @param main - main application window
	/// @param signup - user sign-up window
	void setupWindows(MainWindow* main, SignUpWindow* signup);
};

