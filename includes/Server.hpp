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

class Client;

class Server
{
	public:

		Server(std::string port, std::string pass);
// 		~Server();

		void server_init();						
		void create_socket();					
		void accept_new_client();				
		void receive_new_data(int fd);	
		void close_fds();						
		void clear_clients(int fd);
		static void signal_handler(int signum);
		int servRun();

	private:

		struct sockaddr_in struct_socket;
		int _port;						
		int _socketFd;
		std::string _pass;
		static bool _signal;
		std::vector<Client> _clients;
		std::vector<struct pollfd> _fds;
// 		Server(const Server& rhs);
// 		Server& operator=(const Server& rhs);
};

#endif
