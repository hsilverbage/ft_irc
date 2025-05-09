#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <map>
#include "Server.hpp"

class Client
{
	public:

		Client(int fd);
		~Client();

		
		std::string&	get_nickname();
		std::string&	get_username();
		std::string&	get_realname();
		
		size_t			get_nb_channel();
		
		bool	get_isConnected();
		bool	get_pwdIsCorrect();		

		int	get_fd();

		void 	set_ip_address(std::string ipadd);
		void	set_realname(std::string name);
		void	set_nickname(std::string name);
		void	set_username(std::string name);
		void	set_nb_channel(size_t nbChannel);

		bool	set_isConnected(bool status);
		bool	set_pwdIsCorrect(bool status);
		bool	is_client(std::map<int, Client*> client_map, std::string nickname);

	private:

		std::string _ipAddress;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		size_t		_nbChannel;
		bool		_isConnected;
		bool		_pwdIsCorrect;

		int	_fd;
};

#endif
