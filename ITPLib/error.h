#pragma once

#include <string>
#include <exception>

class ErrorException : public std::exception {
public:
	ErrorException(const std::string& msg);
	virtual std::string getMessage() const;
	virtual const char* what() const noexcept override;
private:
	std::string mMsg;
};

void error(const std::string& msg);
