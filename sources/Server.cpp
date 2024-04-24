#include "Server.hpp"

bool Server::_signal = false;

void Server::SignalHandler(int signum)
{
	(void)signum;
	Server::_signal = true;
}

void Server::clear_clients(int fd)
{
	std::map<int, Client*>::iterator	it;
	
	it = _clients.find(fd);
	if (it != _clients.end())
		_clients.erase(it);

	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			close(fd);
			_fds.erase(_fds.begin() + i);
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
		return;
	}
	else
		buff[bytes] = '\0';
	Command	Cmd(this);

	Cmd.parse_cmd(buff, fd);
}

void Server::accept_new_client()
{

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
	_fds.push_back(poll);

	Client* client = new Client(acc);
	_clients[acc] = client;
	_clients[acc]->set_ip_address(inet_ntoa((struct_socket.sin_addr)));
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

Server::Server(std::string port, std::string pwd) : _pwd(pwd)
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

std::map<int, Client*>	Server::get_clients_map()
{
	return (this->_clients);
}

std::string&	Server::get_pwd()
{
	return (this->_pwd);
}

Server::~Server() 
{
	// TODO maybe delete _CLients
	// TODO check if vector of fd socket is empty, if not close the rest
}

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
