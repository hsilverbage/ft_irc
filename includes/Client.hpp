#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	public:

		Client();
		~Client();

		void 	set_ip_address(std::string ipadd);
		std::string&	get_nickname();
		std::string&	get_username();
		std::string&	get_realname();

	private:

		// Client(const Client& rhs);
		// Client& operator=(const Client& rhs);

		std::string _ipAddress;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
};

#endif
