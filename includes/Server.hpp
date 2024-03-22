#ifndef	SERVER_HPP
#define	SERVER_HPP

#include <iostream>
#include <exception>


class	Server
{
	public :

		Server(std::string port, std::string password);
		~Server();

	private :
	
		Server(const Server& rhs);
		Server& operator=(const Server& rhs);

		std::string	_port;
		std::string	_password;

};

#endif
