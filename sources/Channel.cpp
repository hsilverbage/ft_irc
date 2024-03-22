#include "Channel.hpp"

Channel::Channel(std::string port, std::string password) : _port(port), _password(password)
{

}

Channel::~Channel()
{

}

Channel::Channel(const Channel& rhs)
{
	*this = rhs;
}

Channel&	Channel::operator=(const Channel& rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}

