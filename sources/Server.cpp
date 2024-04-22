#include "Server.hpp"

bool Server::_signal = false;

void Server::SignalHandler(int signum)
{
	(void)signum;
	Server::_signal = true;
}

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

void Server::receive_new_data(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		clear_clients(fd);
		close(fd);
		return;
	}
	else
		buff[bytes] = '\0';
		
	Command	Cmd;

	Cmd.parse_cmd(buff, fd);
}

void Server::accept_new_client()
{
	Client client;

	struct pollfd poll;
	socklen_t len = sizeof(struct_socket);

	int acc = accept(_socketFd, (sockaddr*)&struct_socket, &len);
	if (acc == -1)
	{
		std::cout << "accept() failed" << std::endl;
		return;
	}
	if (fcntl(acc, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
		return;
	}
	poll.fd		 = acc;
	poll.events	 = POLLIN;
	poll.revents = 0;
	client.set_fd(acc);
	client.set_ip_address(inet_ntoa((struct_socket.sin_addr)));
	_clients.push_back(client);
	_fds.push_back(poll);
}

void Server::ServInit()
{
	setSocket();
	std::cout << " Waiting..." << std::endl;

	while (Server::_signal == false)
	{
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::_signal == false)
			throw(std::runtime_error("poll() failed"));
		for (size_t i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == this->_socketFd)
					accept_new_client();
				else
					receive_new_data(_fds[i].fd);
			}
		}
	}
	CloseFds();
}

void Server::setSocket()
{
	int l = 1;
	struct pollfd poll;

	struct_socket.sin_family	  = AF_INET;
	struct_socket.sin_port		  = htons(this->_port);
	struct_socket.sin_addr.s_addr = INADDR_ANY;
	this->_socketFd				  = socket(AF_INET, SOCK_STREAM, 0);

	if (this->_socketFd == -1)
		throw(std::runtime_error("socket not created"));
	if (setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &l, sizeof(l)) == -1)
		throw(std::runtime_error("failed to set option on socket"));
	if (fcntl(this->_socketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("failed to set option on socket"));
	if (bind(this->_socketFd, (struct sockaddr*)&struct_socket, sizeof(struct_socket)) == -1)
		throw(std::runtime_error("failed to bind socket"));
	if (listen(this->_socketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() failed"));
	poll.fd		 = this->_socketFd;
	poll.events	 = POLLIN;
	poll.revents = 0;
	_fds.push_back(poll);
}

Server::Server(std::string port, std::string pass) : _pass(pass)
{
	if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos)
		throw InvalidPort();

	std::stringstream ss(port);
	ss >> _port;
	ss.str();

	if (ss.fail())
		throw InvalidPort();
	if (_port < 1024 || _port > 65535)
		throw InvalidPort();
}

Server::~Server() {}

Server::Server(const Server& rhs)
{
	*this = rhs;
}

Server& Server::operator=(const Server& rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

const char* Server::InvalidPort::what() const throw()
{
	return ("Invalid port, a valid port is a number between 1024 and 65535");
}
