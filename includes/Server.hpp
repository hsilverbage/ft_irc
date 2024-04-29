#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h> //for inet_ntoa()
#include <Client.hpp>
#include <csignal>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h> //for sockaddr_in
#include <poll.h>		//for poll()
#include <sys/socket.h> //for socket()
#include <sys/types.h>	//for socket()
#include <unistd.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

#include "Command.hpp"
#include "Client.hpp"
#include "NumericReplies.hpp"
#include "Channel.hpp"

#define RN "\r\n"

class Client;
class Command;
class Channel;

class Server
{
	public:

		Server(std::string port, std::string pass);
		~Server();

		void server_init();
		std::map<std::string, Channel*>&	get_channel();
		void create_socket();					
		void accept_new_client();				
		void receive_new_data(int fd);	
		void close_fds();						
		void clear_clients(int fd);
		static void SignalHandler(int signum);
		void setSocket();
		void ServInit();
		std::map<int, Client*>	get_clients_map();
		std::string&	get_pwd();

		class	InvalidPort : public std::exception
		{
			const char* what() const throw();
		};

	private:

		struct sockaddr_in struct_socket;
		int _port;						
		int _socketFd;
		std::string _pwd;
		static bool _signal;

		std::map<int, Client*>			_clients;
		std::map<std::string, Channel*>	_channel;
		std::vector<struct pollfd> 		_fds;

		Server(const Server& rhs);
		Server& operator=(const Server& rhs);
};

#endif
