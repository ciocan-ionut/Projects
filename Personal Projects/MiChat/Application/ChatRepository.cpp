#include "ChatRepository.h"

void ChatRepository::addFriend(const QString& friendsUsername)
{
	friendsList.push_back(friendsUsername);
}

void ChatRepository::removeFriend(const QString& friendsUsername)
{
	const auto& itF = find(friendsList.begin(), friendsList.end(), friendsUsername);
	if (itF != friendsList.end())
		friendsList.erase(itF);
}

void ChatRepository::clearFriendsList()
{
	friendsList.clear();
}

const vector<QString>& ChatRepository::getFriendsList() const
{
	return friendsList;
}

void ChatRepository::addMessage(const QString& receiver, const Message& message)
{
	conversations[receiver].push_back(message);
}

void ChatRepository::deleteConversation(const QString& friendsUsername)
{
	const auto& itC = conversations.find(friendsUsername);
	if (itC != conversations.end())
		conversations.erase(itC);
}

void ChatRepository::clearConversation(const QString& friendsUsername)
{
	conversations[friendsUsername].clear();
}

const vector<Message>& ChatRepository::getConversation(const QString& friendsUsername) const
{
	return conversations.at(friendsUsername);
}