#pragma once

#include "ChatService.h"
#include "ProfileWindow.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

#include <vector>

using namespace std;

class LoginWindow;

class MainWindow : public QWidget
{
public:
    /// Class constructor
    MainWindow(ChatService& service);

	/// Function that setups the connection with the user log-in window
	/// @param login - user log-in window
	void setupWindows(LoginWindow* login);

	/// Overrides the inherited function to setup some UI components before showing the window
	/// @param event - Qt window show event
	void showEvent(QShowEvent* event) override;

private:
	ChatService& service;

	LoginWindow* loginWindow = nullptr;

	ProfileWindow profileWindow{ service };

	QString currentUser = "";
	QString currentTalkingFriend = "";

	QPushButton* logoutBtn;
	QPushButton* profileBtn;

	QListWidget* friendsList;
	QListWidget* messagesList;

	QLineEdit* friendUsernameInput;
	QLineEdit* messageInput;

	QPushButton* addFriendBtn;
	QPushButton* sendMessageBtn;

	/// Function that initialize GUI components
	void initGUI();

	/// Function that connects signals to the GUI components
	void connectSignals();

	/// Function that loads the friends list with the friends of the current logged-in user
	void loadFriendsListUI();

	/// Function that updates the friends list to show the new added friends
	void updateFriendsListUI();

	/// Function that loads the messages list based on the current logged-in user and the friend he is currently talking with
	void loadMessagesListUI();

	/// Function that updates the messages list to show the new received messages
	void updateMessagesListUI();
};

