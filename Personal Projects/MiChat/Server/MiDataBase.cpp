#include "MiDataBase.h"

#include <qjsonobject.h>

MiDataBase::MiDataBase()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("MiChatDB.db");
	db.open();

	QSqlQuery query;
	query.exec("CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT UNIQUE, Password TEXT)");
	query.exec("CREATE TABLE IF NOT EXISTS Friends (ID INTEGER PRIMARY KEY AUTOINCREMENT, UserID INTEGER, FriendID INTEGER, "
			   "FOREIGN KEY (UserID) REFERENCES Users(ID), FOREIGN KEY (FriendID) REFERENCES Users(ID))");
	query.exec("CREATE TABLE IF NOT EXISTS Messages (ID INTEGER PRIMARY KEY AUTOINCREMENT, SenderID INTEGER, ReceiverID INTEGER, Message TEXT, Date DATETIME DEFAULT CURRENT_TIMESTAMP, "
			   "FOREIGN KEY (SenderID) REFERENCES Users(ID), FOREIGN KEY (ReceiverID) REFERENCES Users(ID))");
}

void MiDataBase::validateUserCredentials(const QString& username, const QString& password) const
{
	QSqlQuery query;
	query.prepare("SELECT Username, Password FROM Users WHERE Username = :username");
	query.bindValue(":username", username);
	query.exec();

	if (query.next())
	{
		QString dbPassword = query.value(1).toString();
		if (dbPassword != password)
			throw exception("The password is incorrect!");
	}
	else
		throw exception("The username doesn't exist!");
}

bool MiDataBase::isUsernameTaken(const QString& username) const
{
	QSqlQuery query;
	query.prepare("SELECT Username FROM Users WHERE Username = :username");
	query.bindValue(":username", username);
	query.exec();

	return query.next();
}

QString MiDataBase::getPassword(const QString& username) const
{
	QSqlQuery query;
	query.prepare("SELECT Password FROM Users WHERE Username = :username");
	query.bindValue(":username", username);
	query.exec();

	query.next();
	QString password = query.value(0).toString();
	return password;
}

void MiDataBase::addUser(const QString& username, const QString& password)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Users (Username, Password) VALUES (?, ?)");
	query.addBindValue(username);
	query.addBindValue(password);
	query.exec();
}

void MiDataBase::changePassword(const QString& username, const QString& newPassword)
{
	QSqlQuery query;
	query.prepare("UPDATE Users SET Password = :newPassword WHERE Username = :username");
	query.bindValue(":newPassword", newPassword);
	query.bindValue(":username", username);
	query.exec();
}

QJsonArray MiDataBase::getFriends(const QString& username)
{
	QSqlQuery query;
	query.prepare("SELECT Users.Username FROM Friends JOIN Users ON Friends.FriendID = Users.ID "
				  "WHERE Friends.UserID = (SELECT ID FROM Users WHERE Username = :username)");
	query.bindValue(":username", username);
	query.exec();

	QJsonArray friendsArray;
	while (query.next())
	{
		QString friendsUsername = query.value(0).toString();
		friendsArray.append(friendsUsername);
	}
	return friendsArray;
}

bool MiDataBase::checkIfTheUsersAreFriends(const QString& username, const QString& friendsUsername) const
{
	QSqlQuery query;
	query.prepare("SELECT UserID, FriendID FROM Friends "
				  "WHERE (UserID = (SELECT ID FROM Users WHERE Username = :username)"
				  "AND FriendID = (SELECT ID FROM Users WHERE Username = :friendsUsername))");
	query.bindValue(":username", username);
	query.bindValue(":friendsUsername", friendsUsername);
	query.exec();

	return query.next();
}

void MiDataBase::addFriend(const QString& username, const QString& friendsUsername)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Friends (UserID, FriendID) VALUES "
				  "((SELECT ID FROM Users WHERE Username = :username), (SELECT ID FROM Users WHERE Username = :friendsUsername))");
	query.bindValue(":username", username);
	query.bindValue(":friendsUsername", friendsUsername);
	query.exec();

	query.prepare("INSERT INTO Friends (UserID, FriendID) VALUES "
				  "((SELECT ID FROM Users WHERE Username = :username), (SELECT ID FROM Users WHERE Username = :friendsUsername))");
	query.bindValue(":username", friendsUsername);
	query.bindValue(":friendsUsername", username);
	query.exec();
}

void MiDataBase::removeFriend(const QString& username, const QString& friendsUsername)
{
	QSqlQuery query;
	query.prepare("DELETE FROM Friends WHERE (UserID = (SELECT ID FROM Users WHERE Username = :username) AND FriendID = (SELECT ID FROM Users WHERE Username = :friendsUsername)) "
				  "OR (UserID = (SELECT ID FROM Users WHERE Username = :friendsUsername) AND FriendID = (SELECT ID FROM Users WHERE Username = :username))");
	query.bindValue(":username", username);
	query.bindValue(":friendsUsername", friendsUsername);
	query.exec();

	query.prepare("DELETE FROM Messages WHERE(SenderID = (SELECT ID FROM Users WHERE Username = :username) AND ReceiverID = (SELECT ID FROM Users WHERE Username = :friendsUsername)) "
				  "OR (SenderID = (SELECT ID FROM Users WHERE Username = :friendsUsername) AND ReceiverID = (SELECT ID FROM Users WHERE Username = :username))");
	query.bindValue(":username", username);
	query.bindValue(":friendsUsername", friendsUsername);
	query.exec();
}

void MiDataBase::addMessage(const QString& sender, const QString& receiver, const QString& message)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Messages (SenderID, ReceiverID, Message) VALUES "
				  "((SELECT ID FROM Users WHERE Username = :sender), (SELECT ID FROM Users WHERE Username = :receiver), :message)");
	query.bindValue(":sender", sender);
	query.bindValue(":receiver", receiver);
	query.bindValue(":message", message);
	query.exec();
}

QJsonArray MiDataBase::getMessages(const QString& username, const QString& friendsUsername)
{
	QSqlQuery query;
	query.prepare("SELECT u1.Username AS Sender, u2.Username AS Receiver, m.Message, m.Date "
				  "FROM Messages m "
				  "JOIN Users u1 on m.SenderID = u1.ID "
				  "JOIN Users u2 on m.ReceiverID = u2.ID "
				  "WHERE (m.SenderID = (SELECT ID FROM Users WHERE Username = :username) AND m.ReceiverID = (SELECT ID FROM Users WHERE Username = :friendsUsername)) "
				  "OR (m.SenderID = (SELECT ID FROM Users WHERE Username = :friendsUsername) AND m.ReceiverID = (SELECT ID FROM Users WHERE Username = :username)) "
				  "ORDER BY m.Date ASC");
	query.bindValue(":username", username);
	query.bindValue(":friendsUsername", friendsUsername);
	query.exec();

	QJsonArray messagesArray;
	while (query.next())
	{
		QJsonObject message;
		message["sender"] = query.value(0).toString();
		message["receiver"] = query.value(1).toString();
		message["message"] = query.value(2).toString();
		messagesArray.append(message);
	}
	return messagesArray;
}

MiDataBase::~MiDataBase()
{
	if (db.isOpen())
		db.close();
}