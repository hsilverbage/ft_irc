#include "Server.hpp"

Server::Server(std::string port, std::string password) : _port(port), _password(password)
{

}

Server::~Server()
{

}

Server::Server(const Server& rhs)
{
	*this = rhs;
}

Server&	Server::operator=(const Server& rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}
