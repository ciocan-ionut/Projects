#pragma once

#include <string>
using std::string;

class BaseException
{
protected:
	string errMsg;

public:
	explicit BaseException(string msg) : errMsg{ msg } {}

	virtual const char* what() const noexcept
	{
		return errMsg.c_str();
	}

	virtual ~BaseException() = default;
};

