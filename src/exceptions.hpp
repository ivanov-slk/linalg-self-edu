#pragma once
#include <exception>
#include <string>

class CustomException : public std::exception
{
private:
    std::string m_message;

public:
    CustomException(std::string msg) : m_message(msg){};
    const char *what() const throw()
    {
        return m_message.c_str();
    }
};

class BadDimensionsException : public CustomException
{
    using CustomException::CustomException;
};

class BadMatrixPropertiesException : public CustomException
{
    using CustomException::CustomException;
};