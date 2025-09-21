#include "MainWindow.h"
#include "LoginWindow.h"

#include <sstream>
#include <algorithm>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <qmessagebox.h>

MainWindow::MainWindow(ChatService& service) : service{ service }
{
	initGUI();
	connectSignals();
}

void MainWindow::setupWindows(LoginWindow* login)
{
	loginWindow = login;
}

void MainWindow::initGUI()
{
	QVBoxLayout* mainLy = new QVBoxLayout(this);

	QHBoxLayout* logoutAndProfileBtnsLy = new QHBoxLayout(this);
	logoutBtn = new QPushButton("Logout", this);
	profileBtn = new QPushButton(this);
	logoutAndProfileBtnsLy->addWidget(logoutBtn);
	logoutAndProfileBtnsLy->addStretch();
	logoutAndProfileBtnsLy->addWidget(profileBtn);
	mainLy->addLayout(logoutAndProfileBtnsLy);

	QLabel* friendsLabel = new QLabel("Friends", this);
	QLabel* usernameLabel = new QLabel("Username:", this);
	QLabel* messagesLabel = new QLabel("Messages", this);

	friendsList = new QListWidget(this);
	messagesList = new QListWidget(this);

	friendUsernameInput = new QLineEdit(this);
	messageInput = new QLineEdit(this);

	addFriendBtn = new QPushButton("Add friend", this);
	sendMessageBtn = new QPushButton("Send", this);

	// Set up the layout for users + logout button for convenience
	QVBoxLayout* userLayout = new QVBoxLayout(this);
	userLayout->addWidget(friendsLabel);
	userLayout->addWidget(friendsList);
	QHBoxLayout* userLoginLayout = new QHBoxLayout(this);
	userLoginLayout->addWidget(usernameLabel);
	userLoginLayout->addWidget(friendUsernameInput);
	userLoginLayout->addWidget(addFriendBtn);
	userLayout->addLayout(userLoginLayout);

	// Set up the layout for messages
	QVBoxLayout* messageLayout = new QVBoxLayout(this);
	QHBoxLayout* messageLabelLayout = new QHBoxLayout(this);
	messageLabelLayout->addStretch();
	messageLabelLayout->addWidget(messagesLabel);
	messageLayout->addLayout(messageLabelLayout);
	messageLayout->addWidget(messagesList);
	QHBoxLayout* sendMessageLayout = new QHBoxLayout(this);
	sendMessageLayout->addWidget(messageInput);
	sendMessageLayout->addWidget(sendMessageBtn);
	messageLayout->addLayout(sendMessageLayout);

	// Add the user and message layouts to the content layout
	QHBoxLayout* contentLy = new QHBoxLayout(this);
	contentLy->addLayout(userLayout);
	contentLy->addLayout(messageLayout);

	mainLy->addLayout(contentLy);

	setLayout(mainLy);
	setWindowIcon(QIcon(":/MiChat/MiChatLogo.ico"));
}

void MainWindow::connectSignals()
{
	// Loads the messages list when the signal is received from ChatService
	QObject::connect(&service, &ChatService::loadMessagesListUISignal, [&]() {
		loadMessagesListUI();
		});

	// Updates the messages list if it's necessary when the signal is received from ChatService
	QObject::connect(&service, &ChatService::newMessageUISignal, [&](const QString& friendsUsername) {
		if (currentTalkingFriend == friendsUsername)
			updateMessagesListUI();
		});

	// Loads the friends list when the signal is received from ChatService
	QObject::connect(&service, &ChatService::loadFriendsListUISignal, [&]() {
		loadFriendsListUI();
		});

	// Updates the friends list when the signal is received from ChatService
	QObject::connect(&service, &ChatService::newFriendUISignal, [&]() {
		updateFriendsListUI();
		});

	// Showing a warning message box with the specific error received from ChatService
	QObject::connect(&service, &ChatService::errorOnFriendAddUISignal, [&](const QString& errMessage) {
		QMessageBox::warning(this, "Error", errMessage);
		});

	// Adds a friend with the username entered in the input
	QObject::connect(addFriendBtn, &QPushButton::clicked, [&]() {
		QString friendsUsername = friendUsernameInput->text();
		service.addFriend(friendsUsername);
		friendUsernameInput->clear();
		});

	// Loads the messages list if the friend selection changed so the messages corespond to the right friend
	QObject::connect(friendsList, &QListWidget::itemSelectionChanged, [&]() {
		if (friendsList->selectedItems().isEmpty())
			return;

		QWidget* currentSelectedWidget = friendsList->itemWidget(friendsList->currentItem());
		// Get the friend's username when selecting from the friends list
		QLabel* currentSelectedFriend = currentSelectedWidget->findChild<QLabel*>();
		currentTalkingFriend = currentSelectedFriend->text();

		if (currentTalkingFriend != "")
			service.loadMessages(currentTalkingFriend);
		});

	// Sends a message with the content from the input
	QObject::connect(sendMessageBtn, &QPushButton::clicked, [&]() {
		QString message = messageInput->text();
		if (message == "" || currentTalkingFriend == "")
			return;
		service.saveMessageSent(currentUser, currentTalkingFriend, message);
		messageInput->clear();
		});

	// Hiding the current window and showing the login window when the logout button is pressed
	QObject::connect(logoutBtn, &QPushButton::clicked, [&]() {
		hide();
		profileWindow.hide();
		friendsList->clearSelection();
		messagesList->clear();
		loginWindow->show();
		});

	// Showing the profile window of the user
	QObject::connect(profileBtn, &QPushButton::clicked, [&]() {
		profileWindow.show();
		service.loadUserPassword();
		});
}

void MainWindow::showEvent(QShowEvent* event)
{
	// Load friends list when the main window shows on the screen
	currentUser = service.getLoggedInUser();
	service.loadFriendsList();
	profileBtn->setText(currentUser);
	QWidget::showEvent(event);
}

void MainWindow::loadFriendsListUI()
{
	friendsList->clear();
	if (currentUser != "")
	{
		const auto& friends = service.getFriends();
		for (const auto& aFriend : friends)
		{
			QListWidgetItem* item = new QListWidgetItem();
			QWidget* container = new QWidget(this);

			// Add the friend's username and a button for easy friend-removal
			QLabel* friendUsernameLbl = new QLabel(aFriend, this);
			QPushButton* removeFriendBtn = new QPushButton("Remove", this);

			QHBoxLayout* containerLayout = new QHBoxLayout(this);
			containerLayout->addWidget(friendUsernameLbl);
			containerLayout->addStretch();
			containerLayout->addWidget(removeFriendBtn);
			container->setLayout(containerLayout);

			item->setSizeHint(container->sizeHint());
			friendsList->addItem(item);
			friendsList->setItemWidget(item, container);

			// Remove the friend if the button is pressed and it's confirmed
			connect(removeFriendBtn, &QPushButton::clicked, [this, aFriend]() {
				QMessageBox::StandardButton reply = QMessageBox::question(this, "Are you sure?", "Do you really want to remove " + aFriend + " as a friend?", QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes)
					service.removeFriend(aFriend);
				});
		}
	}
}

void MainWindow::updateFriendsListUI()
{
	int friendsCnt = friendsList->count();
	if (currentUser != "")
	{
		const auto& friends = service.getFriends();
		for (int i = friendsCnt; i < friends.size(); i++)
		{
			QString aFriend = friends[i];

			QListWidgetItem* item = new QListWidgetItem();
			QWidget* container = new QWidget(this);

			// Add the friend's username and a button for easy friend-removal
			QLabel* friendUsernameLbl = new QLabel(aFriend, this);
			QPushButton* removeFriendBtn = new QPushButton("Remove", this);

			QHBoxLayout* containerLayout = new QHBoxLayout(this);
			containerLayout->addWidget(friendUsernameLbl);
			containerLayout->addStretch();
			containerLayout->addWidget(removeFriendBtn);
			container->setLayout(containerLayout);

			item->setSizeHint(container->sizeHint());
			friendsList->addItem(item);
			friendsList->setItemWidget(item, container);

			// Remove the friend if the button is pressed and it's confirmed
			connect(removeFriendBtn, &QPushButton::clicked, [this, aFriend]() {
				QMessageBox::StandardButton reply = QMessageBox::question(this, "Are you sure?", "Do you really want to remove " + aFriend + " as a friend?", QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes)
					service.removeFriend(aFriend);
				});
		}
	}
}

void MainWindow::loadMessagesListUI()
{
	messagesList->clear();
	if (currentUser != "" && currentTalkingFriend != "")
	{
		try 
		{ 
			const auto& messages = service.getMessages(currentTalkingFriend);
			for (const auto& message : messages)
			{
				QString messageListItem = message.getSender() + ": " + message.getMessage();
				// Put the message on the right side of the screen for the current user
				if (currentUser == message.getSender())
				{
					QListWidgetItem* item = new QListWidgetItem(messageListItem);
					item->setTextAlignment(Qt::AlignRight);
					messagesList->addItem(item);
					continue;
				}
				// Otherwise just simply add them
				messagesList->addItem(messageListItem);
			}
		}
		catch (const out_of_range&) { return; };
	}
}

void MainWindow::updateMessagesListUI()
{
	int msgsCnt = messagesList->count();
	if (currentUser != "" && currentTalkingFriend != "")
	{
		try
		{
			const auto& messages = service.getMessages(currentTalkingFriend);
			for (int i = msgsCnt; i < messages.size(); i++)
			{
				const auto& message = messages[i];
				QString messageListItem = message.getSender() + ": " + message.getMessage();
				// Put the message on the right side of the screen for the current user
				if (currentUser == message.getSender())
				{
					QListWidgetItem* item = new QListWidgetItem(messageListItem);
					item->setTextAlignment(Qt::AlignRight);
					messagesList->addItem(item);
					continue;
				}
				// Otherwise just simply add them
				messagesList->addItem(messageListItem);
			}
		}
		catch (const out_of_range&) { return; };
	}
}