#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	public:

		Client();
		// ~Client();

		int get_fd();
		void set_fd(int fd);
		void set_ip_address(std::string ipadd);

	private:

		// Client(const Client& rhs);
		// Client& operator=(const Client& rhs);

		int _fd;
		std::string _ipAddress;
};

#endif
