#include "Tests.h"
#include "Message.h"
#include "ChatRepository.h"
#include "ChatService.h"

#include <assert.h>

void Tests::runMessageTests()
{
	QString sender = "a", receiver = "b", message = "Hello World!";
	Message msg{ sender, receiver, message };
	assert(msg.getSender() == sender);
	assert(msg.getReceiver() == receiver);
	assert(msg.getMessage() == message);
}

void Tests::repositoryFriendTests()
{
	ChatRepository repository;
	QString testFriend = "a";
	repository.addFriend(testFriend);
	auto friends = repository.getFriendsList();
	assert(friends.size() == 1);
	repository.removeFriend(testFriend);
	friends = repository.getFriendsList();
	assert(friends.size() == 0);
	repository.addFriend(testFriend);
	repository.clearFriendsList();
	friends = repository.getFriendsList();
	assert(friends.size() == 0);
}

void Tests::repositoryConversationTests()
{
	ChatRepository repository;
	QString testFriend = "a";
	repository.addFriend(testFriend);
	QString sender = "a", receiver = "b", message = "Hello World!";
	Message msg{ sender, receiver, message };
	repository.addMessage(testFriend, msg);
	auto messages = repository.getConversation(testFriend);
	assert(messages.size() == 1);
	repository.clearConversation(testFriend);
	messages = repository.getConversation(testFriend);
	assert(messages.size() == 0);
	repository.deleteConversation(testFriend);
}

void Tests::runRepositoryTests()
{
	repositoryFriendTests();
	repositoryConversationTests();
}

void Tests::runServiceTests()
{
	ChatRepository repository;
	ChatService service{ repository };

	QString username = "a";
	service.setLoggedInUser(username);
	QString checkUsername = service.getLoggedInUser();
	assert(username == checkUsername);
}

void Tests::runTests()
{
	runMessageTests();
	runRepositoryTests();
	runServiceTests();
}