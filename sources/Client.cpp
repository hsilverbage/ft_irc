#include "Client.hpp"

Client::Client()
{
	this->_nickname = "";
	this->_username = "";
	this->_realname = "";
}

void Client::set_ip_address(std::string ipAddress)
{
	this->_ipAddress = ipAddress;
}

Client::~Client() 
{
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
