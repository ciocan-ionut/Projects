#include "Message.h"

Message::Message(const QString& sender, const QString& receiver, const QString& message)
	: sender{ sender }, receiver{ receiver }, message { message } {}

const QString& Message::getSender() const
{
	return sender;
}

const QString& Message::getReceiver() const
{
	return receiver;
}

const QString& Message::getMessage() const
{
	return message;
}