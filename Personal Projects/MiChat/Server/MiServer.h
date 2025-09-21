#pragma once

#include "MiDataBase.h"

#include <unordered_map>
#include <string>

#include <QTcpServer>
#include <QTcpSocket>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

using namespace std;
using Handler = function<void(const QJsonObject& obj)>;

class MiServer : public QTcpServer
{
private:
	unordered_map<QString, QTcpSocket*> clients;
	unordered_map<QTcpSocket*, QByteArray> buffers;
	unordered_map<QString, Handler> handlers;
	MiDataBase db;

	QTcpSocket* clientSocket;

	/// Function that handles new connections to the server
	void onNewConnection();

	/// Function that handles the event when data is available to be read
	void onReadyRead(QTcpSocket* clientSocket);

	/// Function that sends a JSON object
	/// @param obj - the JSON object to be sent
	void sendJson(QTcpSocket* socket, const QJsonObject& obj);

	void createHandlers();

	void handleUserLogin(const QJsonObject& obj);

	void handleUserSignup(const QJsonObject& obj);

	void handleGetPassword(const QJsonObject& obj);

	void handleChangePassword(const QJsonObject& obj);

	void handleNewMessage(const QJsonObject& obj);

	void handleGetMessages(const QJsonObject& obj);

	void handleNewFriend(const QJsonObject& obj);

	void handleFriendRemoval(const QJsonObject& obj);

	void handleGetFriends(const QJsonObject& obj);

public:
	/// Class constructor
	MiServer();

	/// Default destructor
	~MiServer() = default;
};

