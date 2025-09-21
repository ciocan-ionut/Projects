#include "ChatService.h"

#include <fstream>
#include <sstream>

#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>

ChatService::ChatService(ChatRepository& repository) : repository{ repository }
{
	connectServerSignals();
}

const QString& ChatService::getLoggedInUser() const
{
	return loggedInUser;
}

void ChatService::setLoggedInUser(const QString& username)
{
	loggedInUser = username;
}

void ChatService::loadUserPassword()
{
	serverHandler.requestUserPassword(loggedInUser);
}

void ChatService::validateAndLoginUser(const QString& username, const QString& password)
{
	if (username == "" || password == "")
	{
		emit errorOnLoginUISignal("Empty fields are not allowed!");
		return;
	}
	serverHandler.sendUserLoginDetails(username, password);
}

void ChatService::validateAndSignupUser(const QString& username, const QString& password)
{
	serverHandler.sendUserSignupDetails(username, password);
}

void ChatService::changePassword(const QString& newPassword)
{
	emit updateProfileWindowUISignal(newPassword);
	serverHandler.sendUserNewPassword(loggedInUser, newPassword);
}

void ChatService::saveMessageSent(const QString& sender, const QString& receiver, const QString& message)
{
	Message m{ sender, receiver, message };
	repository.addMessage(receiver, m);
	emit newMessageUISignal(receiver);
	serverHandler.sendUserNewMessage(sender, receiver, message);
}

void ChatService::loadMessages(const QString& friendsUsername)
{
	serverHandler.requestMessagesBetweenUsers(loggedInUser, friendsUsername);
}

const vector<Message>& ChatService::getMessages(const QString& friendsUsername) const
{
	return repository.getConversation(friendsUsername);
}

void ChatService::addFriend(const QString& friendsUsername)
{
	if (friendsUsername == "")
	{
		emit errorOnFriendAddUISignal("Empty fields are not allowed!");
		return;
	}
	if (loggedInUser == friendsUsername)
	{
		emit errorOnFriendAddUISignal("You can't add yourself!");
		return;
	}
	serverHandler.sendUserNewFriend(loggedInUser, friendsUsername);
}

void ChatService::removeFriend(const QString& friendsUsername)
{
	repository.removeFriend(friendsUsername);
	emit loadFriendsListUISignal();

	repository.deleteConversation(friendsUsername);
	emit loadMessagesListUISignal();

	serverHandler.sendUserRemovedFriend(loggedInUser, friendsUsername);
}

void ChatService::loadFriendsList()
{
	serverHandler.requestUserFriendsList(loggedInUser);
}

const vector<QString>& ChatService::getFriends() const
{
	return repository.getFriendsList();
}

void ChatService::connectServerSignals()
{
	// Listening to signals from the server handler and emiting new signals to the UI

	connect(&serverHandler, &ServerHandler::reportSuccesfulLoginToService, [&](const QString& username) {
		emit succesfulLoginUISignal(username);
		});

	connect(&serverHandler, &ServerHandler::reportErrorOnLoginToService, [&](const QString& errMessage) {
		emit errorOnLoginUISignal(errMessage);
		});

	connect(&serverHandler, &ServerHandler::reportSuccesfulSignupToService, [&](const QString& username) {
		emit succesfulSignupUISignal(username);
		});

	connect(&serverHandler, &ServerHandler::reportErrorOnSignupToService, [&](const QString& errMessage) {
		emit errorOnSignupUISignal(errMessage);
		});

	connect(&serverHandler, &ServerHandler::reportNewMessageToService, [&](const QString& friendsUsername) {
		emit newMessageUISignal(friendsUsername);
		});

	connect(&serverHandler, &ServerHandler::reportLoadMessagesListToService, [&]() {
		emit loadMessagesListUISignal();
		});

	connect(&serverHandler, &ServerHandler::reportNewFriendToService, [&]() {
		emit newFriendUISignal();
		});

	connect(&serverHandler, &ServerHandler::reportErrorOnFriendAddToService, [&](const QString& errMessage) {
		emit errorOnFriendAddUISignal(errMessage);
		});

	connect(&serverHandler, &ServerHandler::reportLoadFriendsListToService, [&]() {
		emit loadFriendsListUISignal();
		});

	connect(&serverHandler, &ServerHandler::reportUpdateProfileWindowToService, [&](const QString& password) {
		emit updateProfileWindowUISignal(password);
		});
}