#pragma once

#include <QString>

class Message
{
private:
	QString sender;
	QString receiver;
	QString message;

public:
	/// Class constructor
	Message(const QString& sender, const QString& receiver, const QString& message);

	/// Function that returns the sender of the message
	/// @return sender
	const QString& getSender() const;

	/// Function that returns the receiver of the message
	/// @return receiver
	const QString& getReceiver() const;

	/// Function that returns the content of the message 
	/// @return message
	const QString& getMessage() const;
};

