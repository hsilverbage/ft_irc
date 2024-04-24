#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{
	this->_nickname = "";
	this->_username = "";
	this->_realname = "";
	this->_isConnected = false;
	this->_pwdIsCorrect = false;
}

void Client::set_ip_address(std::string ipAddress)
{
	this->_ipAddress = ipAddress;
}

Client::~Client() 
{
}

bool	Client::get_isConnected()
{
	return (this->_isConnected);
}

bool	Client::get_pwdIsCorrect()
{
	return (this->_pwdIsCorrect);
}

std::string&	Client::get_nickname()
{
	return (this->_nickname);
}	

std::string&	Client::get_username()
{
	return (this->_username);
}

std::string&	Client::get_realname()
{
	return (this->_realname);
}

bool	Client::set_isConnected(bool status)
{
	return (this->_isConnected = status);
}

bool	Client::set_pwdIsCorrect(bool status)
{
	return (this->_pwdIsCorrect = status);
}

void	Client::set_realname(std::string name)
{
	this->_realname = name;
}

void	Client::set_nickname(std::string name)
{
	this->_nickname = name;
}	

void	Client::set_username(std::string name)
{
	this->_username = name;
}

int	Client::get_fd()
{
	return (this->_fd);
}


// Client::Client(const Client& rhs)
// {
// 	*this = rhs;
// }

// Client& Client::operator=(const Client& rhs)
// {
// 	if (this != &rhs)
// 	{
// 	}
// 	return (*this);
// }
