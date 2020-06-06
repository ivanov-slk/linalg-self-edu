#pragma once
#include <exception>
#include <string>

class BadDimensionsException : public std::exception
{
private:
    std::string m_message;

public:
    BadDimensionsException(std::string msg) : m_message(msg){};
    const char *what() const throw()
    {
        return m_message.c_str();
    }
};