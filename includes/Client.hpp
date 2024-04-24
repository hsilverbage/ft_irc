#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	public:

		Client(int fd);
		~Client();

		
		std::string&	get_nickname();
		std::string&	get_username();
		std::string&	get_realname();
		
		bool	get_isConnected();
		bool	get_pwdIsCorrect();		

		int	get_fd();

		void 	set_ip_address(std::string ipadd);
		void	set_realname(std::string name);
		void	set_nickname(std::string name);
		void	set_username(std::string name);

		bool	set_isConnected(bool status);
		bool	set_pwdIsCorrect(bool status);

	private:

		// Client(const Client& rhs);
		// Client& operator=(const Client& rhs);

		std::string _ipAddress;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		bool		_isConnected;
		bool		_pwdIsCorrect;

		int	_fd;
};

#endif
