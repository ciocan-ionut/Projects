#pragma once

#include "Message.h"

#include <vector>
#include <unordered_map>
#include <algorithm>

#include <qstring.h>
#include <qjsonarray.h>

using namespace std;

class ChatRepository
{
private:
	vector<QString> friendsList;
	unordered_map<QString, vector<Message>> conversations;

public:
	/// Function that adds a new friend to the friends list
	/// @param friendsUsername - the friend's username
	void addFriend(const QString& friendsUsername);

	/// Function that removes an existing friend from the friends list
	/// @param friendsUsername - the friend's username
	void removeFriend(const QString& friendsUsername);

	/// Function that clears the friends list
	void clearFriendsList();

	/// Function that returns the friends list
	/// @return friendsList - the friends list
	const vector<QString>& getFriendsList() const;

	/// Function that adds a new message to the conversation with a friend
	/// @param receiver - the friend's username 
	/// @param message - the details of the message sent
	void addMessage(const QString& receiver, const Message& message);

	/// Function that completely deletes the conversation with a friend
	/// @param friendsUsername - the friend's username
	void deleteConversation(const QString& friendsUsername);

	/// Function that keeps the entry and clears the conversation with a friend
	/// @param friendsUsername - the friend's username
	void clearConversation(const QString& friendsUsername);

	/// Function that returns the conversation with a friend
	/// @param friendsUsername - the friend's username
	/// @return conversation - list of all the messages sent
	/// @throw out_of_range exception if there is no entry for the friend's username
	const vector<Message>& getConversation(const QString& friendsUsername) const;
};

