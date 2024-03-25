#include "Server.hpp"

Server::Server() : _socketFd(-1) {}

void Server::server_init() {}

void Server::create_socket() {}

void Server::accept_new_client() {}

void Server::receive_new_data(int fd) {}

static void SignalHandler(int signum) {}

void CloseFds() {}

void Server::clear_clients(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].get_fd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

// Server::~Server()
// {

// }

// Server::Server(const Server& rhs)
// {
// 	*this = rhs;
// }

// Server&	Server::operator=(const Server& rhs)
// {
// 	if (this != &rhs)
// 	{

// 	}
// 	return (*this);
// }

