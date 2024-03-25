#include "Client.hpp"

Client::Client() {}


int Client::get_fd()
{
	return (this->_fd);
}

void Client::set_fd(int fd)
{
	this->_fd = fd;
}

void Client::set_ip_address(std::string ipAddress)
{
	this->_ipAddress = ipAddress;
}

// Client::~Client() {}

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
