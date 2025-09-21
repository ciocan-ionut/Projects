#pragma once

#include "Message.h"
#include "ChatRepository.h"
#include "ServerHandler.h"

#include <vector>
#include <unordered_map>

using namespace std;

// The ChatService class inherits from the QObject class to allow to emit signals to the UI
class ChatService : public QObject
{
	Q_OBJECT
private:
	ChatRepository& repository;
	ServerHandler serverHandler{ repository };

	QString loggedInUser;

	/// Function that connects the signals received from the server handler to UI
	void connectServerSignals();

signals:
	void succesfulLoginUISignal(const QString& username);
	void errorOnLoginUISignal(const QString& errMessage);

	void succesfulSignupUISignal(const QString& username);
	void errorOnSignupUISignal(const QString& errMessage);

	void newMessageUISignal(const QString& friendsUsername);
	void loadMessagesListUISignal();

	void errorOnFriendAddUISignal(const QString& errMessage);
	void newFriendUISignal();
	void loadFriendsListUISignal();

	void updateProfileWindowUISignal(const QString& password);

public:
	/// Class constructor
	ChatService(ChatRepository& repository);

	/// Function that returns the username of the currently logged-in user.
	/// @return The username of the currently logged-in user
	const QString& getLoggedInUser() const;

	/// Function that sets the currently logged-in user by username.
	/// @param username - the username of the user to set as logged in
	void setLoggedInUser(const QString& username);

	/// Function that loads the password of the currently logged-in user
	void loadUserPassword();

	/// Function that validates and logins the user if the credentials are valid
	/// @param username - the username that the user entered trying to login
	/// @param password - the password that the user entered trying to login
	void validateAndLoginUser(const QString& username, const QString& password);

	/// Function that validates and signups the user if the credentials are valid 
	/// @param username - the username that the user entered trying to signup
	/// @param password - the password that the user entered trying to signup
	void validateAndSignupUser(const QString& username, const QString& password);

	/// Function that changes the password of the currently logged-in user with a new one
	/// @param newPassword - the new user's password
	void changePassword(const QString& newPassword);

	/// Function that adds a message to the conversation between the two users
	/// @param sender - the username of the user that sent the message
	/// @param receiver - the username of the user that received the message
	/// @param message - the message that was sent
	void saveMessageSent(const QString& sender, const QString& receiver, const QString& message);

	/// Function that loads the conversation between the currently logged-in user and a friend
	/// @param friendsUsername - the friend's username
	void loadMessages(const QString& friendsUsername);

	/// Function that returns a list of the messages that were sent between the currently logged-in user and a friend
	/// @param friendsUsername - the friend's username
	/// @return The list of messages that were sent between the two users
	/// @throw out_of_range exception if there is no entry for the friend's username
	const vector<Message>& getMessages(const QString& friendsUsername) const;

	/// Function that adds a friend to the user's friends list
	/// @param friendsUsername - the friend's username 
	void addFriend(const QString& friendsUsername);

	/// Function that removes a friend from the user's friends list
	/// @param friendsUsername - the friend's username
	void removeFriend(const QString& friendsUsername);

	/// Function that loads the list of friends the user has
	void loadFriendsList();

	/// Function that returns the list of the friends of the currently logged-in user
	/// @return The list with the user's friends
	const vector<QString>& getFriends() const;

	/// Default destructor
	~ChatService() = default;
};

