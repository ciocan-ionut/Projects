#pragma once

#include "ChatRepository.h"

#include <unordered_map>

#include <qtcpsocket.h>

using namespace std;
using Handler = function<void(const QJsonObject& obj)>;

// The ServerHandler class inherits from the QObject class to allow to emit signals to ChatService
class ServerHandler : public QObject
{
	Q_OBJECT
private:
	ChatRepository& repository;
	unordered_map<QString, Handler> handlers;

	QTcpSocket* userSocket;
	QByteArray socketBuffer;

	/// Function that creates handlers for the different server messages
	void createHandlers();

	/// Function that handles the different messages received from the server
	void onReadyRead();

	/// Function that handles the JSON object received from the server when a user tries to login
	/// @param obj - the JSON object received from the server
	void handleUserLogin(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when a user tries to signup
	/// @param obj - the JSON object received from the server
	void handleUserSignup(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when the app requests the user's password
	/// @param obj - the JSON object received from the server
	void handleGetPassword(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when a user receives a new message
	/// @param obj - the JSON object received from the server
	void handleNewMessage(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when the app requests the conversation between two users
	/// @param obj - the JSON object received from the server
	void handleGetMessages(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when a user adds a new friend
	/// @param obj - the JSON object received from the server
	void handleUserAddedNewFriend(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when a user got added by another user
	/// @param obj - the JSON object received from the server
	void handleUserGotAdded(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when a user got removed by another user
	/// @param obj - the JSON object received from the server
	void handleFriendRemoval(const QJsonObject& obj);

	/// Function that handles the JSON object received from the server when the app requests the user's friend list
	/// @param obj - the JSON object received from the server
	void handleGetFriends(const QJsonObject& obj);

	/// Function that sends a JSON object to the server
	/// @param obj - the JSON object to be sent
	void sendJson(const QJsonObject& obj);

signals:
	void reportSuccesfulLoginToService(const QString& username);
	void reportErrorOnLoginToService(const QString& errMessage);

	void reportSuccesfulSignupToService(const QString& username);
	void reportErrorOnSignupToService(const QString& errMessage);

	void reportNewMessageToService(const QString& friendsUsername);
	void reportLoadMessagesListToService();

	void reportErrorOnFriendAddToService(const QString& errMessage);
	void reportNewFriendToService();
	void reportLoadFriendsListToService();

	void reportUpdateProfileWindowToService(const QString& password);

public:
	/// Class constructor
	ServerHandler(ChatRepository& repository);

	/// FUnction that requests the server the password of the user
	/// @param username - the user's username
	void requestUserPassword(const QString& username);

	/// Function that sends to the server the login details of the user
	/// @param username - the username that the user entered trying to login
	/// @param password - the password that the user entered trying to login
	void sendUserLoginDetails(const QString& username, const QString& password);

	/// Function that sends to the server the signup details of the user
	/// @param username - the username that the user entered trying to signup
	/// @param password - the password that the user entered trying to signup
	void sendUserSignupDetails(const QString& username, const QString& password);

	/// Function that sends to the server the updated password of the user
	/// @param username - the user's username
	/// @param password - the user's new password
	void sendUserNewPassword(const QString& username, const QString& password);

	/// Function that sends to the server a new message
	/// @param sender - the username of the user that sent the message
	/// @param receiver - the username of the user that received the message
	/// @param message - the message sent
	void sendUserNewMessage(const QString& sender, const QString& receiver, const QString& message);

	/// Function that requests the server the conversation between the two users
	/// @param username - the user's username
	/// @param friendsUsername - the friend's username
	void requestMessagesBetweenUsers(const QString& username, const QString& friendsUsername);

	/// Function that sends to the server that the two users are now friends
	/// @param username - the user's username
	/// @param friendsUsername - the friend's username
	void sendUserNewFriend(const QString& username, const QString& friendsUsername);

	/// Function that sends to the server that the users are no longer friends
	/// @param username - the user's username
	/// @param friendsUsername - the friend's username
	void sendUserRemovedFriend(const QString& username, const QString& friendsUsername);

	/// Function that requests the server the user's friends list
	/// @param username - the user's username
	void requestUserFriendsList(const QString& username);
};

