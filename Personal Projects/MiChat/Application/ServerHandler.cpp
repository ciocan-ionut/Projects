#include "ServerHandler.h"

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

ServerHandler::ServerHandler(ChatRepository& repository) : repository{ repository }
{
	userSocket = new QTcpSocket(this);
	userSocket->connectToHost("100.108.219.85", 12345);
	connect(userSocket, &QTcpSocket::readyRead, this, &ServerHandler::onReadyRead);
	createHandlers();
}

void ServerHandler::createHandlers()
{
	handlers["LOGIN"] = [this](const QJsonObject& obj) { handleUserLogin(obj); };
	handlers["SIGNUP"] = [this](const QJsonObject& obj) { handleUserSignup(obj); };
	handlers["GET_PASS"] = [this](const QJsonObject& obj) { handleGetPassword(obj); };
	handlers["NEW_MSG"] = [this](const QJsonObject& obj) { handleNewMessage(obj); };
	handlers["GET_MSGS"] = [this](const QJsonObject& obj) { handleGetMessages(obj); };
	handlers["ADD_FRND"] = [this](const QJsonObject& obj) { handleUserAddedNewFriend(obj); };
	handlers["NEW_FRND"] = [this](const QJsonObject& obj) { handleUserGotAdded(obj); };
	handlers["RMV_FRND"] = [this](const QJsonObject& obj) { handleFriendRemoval(obj); };
	handlers["GET_FRNDS"] = [this](const QJsonObject& obj) { handleGetFriends(obj); };
}

void ServerHandler::handleUserLogin(const QJsonObject& obj)
{
	// "type": LOGIN
	// "status": Error / Succes
	// "message": / "username":
	QString operationStatus = obj["status"].toString();
	if (operationStatus == "Succes")
	{
		QString username = obj["username"].toString();
		emit reportSuccesfulLoginToService(username);
	}
	else
	{
		QString errMessage = obj["message"].toString();
		emit reportErrorOnLoginToService(errMessage);
	}
}

void ServerHandler::handleUserSignup(const QJsonObject& obj)
{
	// "type": SIGNUP
	// "status": Error / Succes
	// "message": / "username":
	QString operationStatus = obj["status"].toString();
	if (operationStatus == "Succes")
	{
		QString username = obj["username"].toString();
		emit reportSuccesfulSignupToService(username);
	}
	else
	{
		QString errMessage = obj["message"].toString();
		emit reportErrorOnSignupToService(errMessage);
	}
}

void ServerHandler::handleGetPassword(const QJsonObject& obj)
{
	// "type": GET_PASS
	// "password":
	QString password = obj["password"].toString();
	emit reportUpdateProfileWindowToService(password);
}

void ServerHandler::handleNewMessage(const QJsonObject& obj)
{
	// "type": NEW_MSG
	// "sender":
	// "receiver":
	// "message":
	QString sender = obj["sender"].toString();
	QString receiver = obj["receiver"].toString();
	QString message = obj["message"].toString();
	Message m{ sender, receiver, message };
	repository.addMessage(receiver, m);
	emit reportNewMessageToService(sender);
}

void ServerHandler::handleGetMessages(const QJsonObject& obj)
{
	// "type": GET_MSGS
	// "friendsUsername":
	// "messages":
	QString friendsUsername = obj["friendsUsername"].toString();
	QJsonArray messages = obj["messages"].toArray();
	repository.clearConversation(friendsUsername);
	for (const auto& val : messages)
	{
		QJsonObject msg = val.toObject();
		QString sender = msg["sender"].toString();
		QString receiver = msg["receiver"].toString();
		QString message = msg["message"].toString();

		Message m{ sender, receiver, message };
		repository.addMessage(friendsUsername, m);
	}
	emit reportLoadMessagesListToService();
}

void ServerHandler::handleUserAddedNewFriend(const QJsonObject& obj)
{
	// "type": ADD_FRND
	// "status": Error / Succes
	// "message": / "friendsUsername":
	QString operationStatus = obj["status"].toString();
	if (operationStatus == "Succes")
	{
		QString friendsUsername = obj["friendsUsername"].toString();
		repository.addFriend(friendsUsername);
		emit reportNewFriendToService();
	}
	else
	{
		QString errMessage = obj["message"].toString();
		emit reportErrorOnFriendAddToService(errMessage);
	}
}

void ServerHandler::handleUserGotAdded(const QJsonObject& obj)
{
	// "type": NEW_FRND
	// "friendsUsername":
	QString friendsUsername = obj[friendsUsername].toString();
	repository.addFriend(friendsUsername);
	emit reportNewFriendToService();
}

void ServerHandler::handleFriendRemoval(const QJsonObject& obj)
{
	// "type": RMV_FRND
	// "friendsUsername":
	QString friendsUsername = obj["friendsUsername"].toString();
	repository.removeFriend(friendsUsername);
	repository.deleteConversation(friendsUsername);
	emit reportLoadFriendsListToService();
	emit reportLoadMessagesListToService();
}

void ServerHandler::handleGetFriends(const QJsonObject& obj)
{
	// "type": GET_FRNDS
	// "friends":
	QJsonArray friends = obj["friends"].toArray();
	repository.clearFriendsList();
	for (const auto& f : friends)
		repository.addFriend(f.toString());
	emit reportLoadFriendsListToService();
}

void ServerHandler::onReadyRead()
{
	// Read all the information in the socket and add it to a buffer
	socketBuffer.append(userSocket->readAll());
	int newLine;
	while ((newLine = socketBuffer.indexOf("\n")) != -1)
	{
		// Split the buffer and handle every message received from the server
		QByteArray data = socketBuffer.left(newLine);
		socketBuffer.remove(0, newLine + 1);

		QJsonDocument doc = QJsonDocument::fromJson(data);
		QJsonObject obj = doc.object();
		QString type = obj["type"].toString();

		handlers[type](obj);
	}
}

void ServerHandler::sendJson(const QJsonObject& obj)
{
	QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
	data.append('\n');
	userSocket->write(data);
}

void ServerHandler::requestUserPassword(const QString& username)
{
	QJsonObject obj;
	obj["type"] = "GET_PASS";
	obj["username"] = username;
	sendJson(obj);
}

void ServerHandler::sendUserLoginDetails(const QString& username, const QString& password)
{
	QJsonObject obj;
	obj["type"] = "LOGIN";
	obj["username"] = username;
	obj["password"] = password;
	sendJson(obj);
}

void ServerHandler::sendUserSignupDetails(const QString& username, const QString& password)
{
	QJsonObject obj;
	obj["type"] = "SIGNUP";
	obj["username"] = username;
	obj["password"] = password;
	sendJson(obj);
}

void ServerHandler::sendUserNewPassword(const QString& username, const QString& password)
{
	QJsonObject obj;
	obj["type"] = "CHG_PASS";
	obj["username"] = username;
	obj["password"] = password;
	sendJson(obj);
}

void ServerHandler::sendUserNewMessage(const QString& sender, const QString& receiver, const QString& message)
{
	QJsonObject obj;
	obj["type"] = "NEW_MSG";
	obj["sender"] = sender;
	obj["receiver"] = receiver;
	obj["message"] = message;
	sendJson(obj);
}

void ServerHandler::requestMessagesBetweenUsers(const QString& username, const QString& friendsUsername)
{
	QJsonObject obj;
	obj["type"] = "GET_MSGS";
	obj["username"] = username;
	obj["friendsUsername"] = friendsUsername;
	sendJson(obj);
}

void ServerHandler::sendUserNewFriend(const QString& username, const QString& friendsUsername)
{
	QJsonObject obj;
	obj["type"] = "NEW_FRND";
	obj["username"] = username;
	obj["friendsUsername"] = friendsUsername;
	sendJson(obj);
}

void ServerHandler::sendUserRemovedFriend(const QString& username, const QString& friendsUsername)
{
	QJsonObject obj;
	obj["type"] = "RMV_FRND";
	obj["username"] = username;
	obj["friendsUsername"] = friendsUsername;
	sendJson(obj);
}

void ServerHandler::requestUserFriendsList(const QString& username)
{
	QJsonObject obj;
	obj["type"] = "GET_FRNDS";
	obj["username"] = username;
	sendJson(obj);
}