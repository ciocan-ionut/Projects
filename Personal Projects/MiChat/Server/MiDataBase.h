#pragma once

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <qjsonarray.h>

#include <vector>

using namespace std;

class MiDataBase
{
private:
	QSqlDatabase db;

public:
	/// Function that connects the application to the database
	MiDataBase();

	/// Function that validates the user's username and password
	/// @param username - the user's username
	/// @param password - the user's password
	void validateUserCredentials(const QString& username, const QString& password) const;

	/// Function that returns if the username already exists in the database
	/// @param username - the user's username
	/// @return true (if the username already exists) / false (otherwise)
	bool isUsernameTaken(const QString& username) const;

	/// Function that returns the user's password based on the username
	/// @param username - the user's username
	/// @return password - the user's password
	QString getPassword(const QString& username) const;

	/// Function that adds an user to the database
	/// @param username - the user's username
	/// @param password - the user's password
	void addUser(const QString& username, const QString& password);

	/// Function that updates the user's password with the new password
	/// @username - the user's username
	/// @newPassword - the user's new password
	void changePassword(const QString& username, const QString& newPassword);

	/// Function that returns a list of the user's friends
	/// @param username - the user's username
	/// @return friendsArray - the user's friend list
	QJsonArray getFriends(const QString& username);

	/// Function that checks if the two users are friends
	/// @param username - the user's username
	/// @param friendsUsername - the username of the potential friend
	/// @return true (if the users are friends) / false (otherwise)
	bool checkIfTheUsersAreFriends(const QString& username, const QString& friendsUsername) const;

	/// Function that adds a new friend to the database
	/// @username - the user that added the friend
	/// @friendsUsername - the friend's username
	void addFriend(const QString& username, const QString& friendsUsername);

	/// Function that removes a friend from the database and all the messages between them
	/// @username - the username of the user that removed the friend
	/// @friendsUsername - the username of the friend that was removed
	void removeFriend(const QString& username, const QString& friendsUsername);

	/// Function that adds a message to the database
	/// @param sender - the username of the user that sent the message
	/// @param receiver - the username of the user that received the message
	/// @param message - the message that was sent
	void addMessage(const QString& sender, const QString& receiver, const QString& message);

	/// Function that returns a list of all the messages between the two users
	/// @param username - the user's username
	/// @param friendsUsername - the friend's username
	/// @return messagesArray - the list of messages
	QJsonArray getMessages(const QString& username, const QString& friendsUsername);

	/// Class destructor
	~MiDataBase();
};

