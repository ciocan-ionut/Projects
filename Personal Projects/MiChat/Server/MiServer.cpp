#include "MiServer.h"

MiServer::MiServer()
{
	clientSocket = new QTcpSocket(this);
	if (!listen(QHostAddress::Any, 12345))
		qDebug() << "Server start failed!\n";
	connect(this, &QTcpServer::newConnection, this, &MiServer::onNewConnection);
	createHandlers();
}

void MiServer::createHandlers()
{
	handlers["LOGIN"] = [this](const QJsonObject& obj) { handleUserLogin(obj); };
	handlers["SIGNUP"] = [this](const QJsonObject& obj) { handleUserSignup(obj); };
	handlers["GET_PASS"] = [this](const QJsonObject& obj) { handleGetPassword(obj); };
	handlers["CHG_PASS"] = [this](const QJsonObject& obj) { handleChangePassword(obj); };
	handlers["NEW_MSG"] = [this](const QJsonObject& obj) { handleNewMessage(obj); };
	handlers["GET_MSGS"] = [this](const QJsonObject& obj) { handleGetMessages(obj); };
	handlers["NEW_FRND"] = [this](const QJsonObject& obj) { handleNewFriend(obj); };
	handlers["RMV_FRND"] = [this](const QJsonObject& obj) { handleFriendRemoval(obj); };
	handlers["GET_FRNDS"] = [this](const QJsonObject& obj) { handleGetFriends(obj); };
}

void MiServer::sendJson(QTcpSocket* socket, const QJsonObject& obj)
{
	QByteArray data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
	data.append('\n');
	socket->write(data);
}

void MiServer::onNewConnection()
{
	clientSocket = nextPendingConnection();
	connect(clientSocket, &QTcpSocket::readyRead, [&]() {
		onReadyRead(clientSocket);
	});
}

void MiServer::handleUserLogin(const QJsonObject& obj)
{
	// "type": LOGIN,
	// "username":
	// "password":
	QString username = obj["username"].toString();
	QString password = obj["password"].toString();

	QJsonObject responseObj;
	responseObj["type"] = "LOGIN";
	try
	{
		db.validateUserCredentials(username, password);
		responseObj["status"] = "Succes";
		responseObj["username"] = username;
		clients[username] = clientSocket;
	}
	catch (const exception& errMessage)
	{
		responseObj["status"] = "Error";
		responseObj["message"] = errMessage.what();
	}
	sendJson(clientSocket, responseObj);
}

void MiServer::handleUserSignup(const QJsonObject& obj)
{
	// "type": SIGNUP,
	// "username":
	// "password":
	QString username = obj["username"].toString();
	QString password = obj["password"].toString();

	QJsonObject responseObj;
	responseObj["type"] = "SIGNUP";
	if (db.isUsernameTaken(username))
	{
		responseObj["status"] = "Error";
		responseObj["message"] = "This username already exists!";
	}
	else
	{
		db.addUser(username, password);
		responseObj["status"] = "Succes";
		responseObj["username"] = username;
	}
	sendJson(clientSocket, responseObj);
}

void MiServer::handleGetPassword(const QJsonObject& obj)
{
	// "type": GET_PASS
	// "username":
	QString username = obj["username"].toString();

	QJsonObject responseObj;
	responseObj["type"] = "GET_PASS";
	responseObj["password"] = db.getPassword(username);
	sendJson(clientSocket, responseObj);
}

void MiServer::handleChangePassword(const QJsonObject& obj)
{
	// "type": CHG_PASS,
	// "username":
	// "password":
	QString username = obj["username"].toString();
	QString newPassword = obj["password"].toString();
	db.changePassword(username, newPassword);
}

void MiServer::handleNewMessage(const QJsonObject& obj)
{
	// "type": NEW_MSG,
	// "sender": 
	// "receiver":
	// "message":
	QString sender = obj["sender"].toString();
	QString receiver = obj["receiver"].toString();
	QString message = obj["message"].toString();
	db.addMessage(sender, receiver, message);
	if (clients.count(receiver) > 0)
		sendJson(clients[receiver], obj);
}

void MiServer::handleGetMessages(const QJsonObject& obj)
{
	// "type": GET_MSGS
	// "username":
	// "friendsUsername":
	QString username = obj["username"].toString();
	QString friendsUsername = obj["friendsUsername"].toString();

	QJsonObject responseObj;
	responseObj["type"] = "GET_MSGS";
	responseObj["friendsUsername"] = friendsUsername; 
	responseObj["messages"] = db.getMessages(username, friendsUsername);;
	sendJson(clientSocket, responseObj);
}

void MiServer::handleNewFriend(const QJsonObject& obj)
{
	// "type": NEW_FRND,
	// "username":
	// "friendsUsername":
	QString username = obj["username"].toString();
	QString friendsUsername = obj["friendsUsername"].toString();

	QJsonObject userResponseObj;
	userResponseObj["type"] = "ADD_FRND";
	if (!db.isUsernameTaken(friendsUsername))
	{
		userResponseObj["status"] = "Error";
		userResponseObj["message"] = "The user doesn't exists!";
	}
	else if (db.checkIfTheUsersAreFriends(username, friendsUsername))
	{
		userResponseObj["status"] = "Error";
		userResponseObj["message"] = "The user is already in your friends list!";
	}
	else
	{
		userResponseObj["status"] = "Succes";
		userResponseObj["friendsUsername"] = friendsUsername;
		db.addFriend(username, friendsUsername);

		QJsonObject friendResponseObj;
		friendResponseObj["type"] = "NEW_FRND";
		friendResponseObj["friendsUsername"] = username;
		if (clients.count(friendsUsername) > 0)
			sendJson(clients[friendsUsername], friendResponseObj);
	}
	sendJson(clientSocket, userResponseObj);
}

void MiServer::handleFriendRemoval(const QJsonObject& obj)
{
	// "type": RMV_FRND
	// "username":
	// "friendsUsername":
	QString username = obj["username"].toString();
	QString friendsUsername = obj["friendsUsername"].toString();
	db.removeFriend(username, friendsUsername);

	QJsonObject responseObj;
	responseObj["type"] = "RMV_FRND";
	responseObj["friendsUsername"] = username;
	if (clients.count(friendsUsername) > 0)
		sendJson(clients[friendsUsername], responseObj);
}

void MiServer::handleGetFriends(const QJsonObject& obj)
{
	// "type": GET_FRNDS,
	// "username":
	QString username = obj["username"].toString();

	QJsonObject responseObj;
	responseObj["type"] = "GET_FRNDS";
	responseObj["friends"] = db.getFriends(username);
	sendJson(clientSocket, responseObj);
}

void MiServer::onReadyRead(QTcpSocket* clientSocket)
{
	QByteArray buffer = buffers[clientSocket];
	buffer.append(clientSocket->readAll());

	int newLine;
	while ((newLine = buffer.indexOf("\n")) != -1)
	{
		QByteArray data = buffer.left(newLine);
		buffer.remove(0, newLine + 1);

		QJsonDocument doc = QJsonDocument::fromJson(data);
		QJsonObject obj = doc.object();
		QString type = obj["type"].toString();

		handlers[type](obj);
	}
}