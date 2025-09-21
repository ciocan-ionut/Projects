#pragma once

#include "ChatService.h"

#include "C:\Qt\6.9.0\msvc2022_64\include\QtWidgets\qwidget.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qregularexpression.h>

class ProfileWindow : public QWidget
{
private:
	ChatService& service;

	QLineEdit* usernameInput;
	QLineEdit* passwordInput;
	QPushButton* showPasswordBtn;
	QLineEdit* changePassInput;
	QPushButton* changePassBtn;

	QLabel* feedbackPswdInput;
	bool isPasswordValid = false;
	QRegularExpression regexPswd{ "^[a-zA-Z0-9!@#$&]+$" };

	/// Function that initializes GUI components
	void initGUI();

	/// Function that connects signals to the GUI components
	void connectSignals();

	void showEvent(QShowEvent* event) override;

public:
	/// Class constructor
	ProfileWindow(ChatService& service);
};

