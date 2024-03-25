#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	public:

		Client();
		// ~Client();

		// std::string& getNickname() const;
		// std::string& getRealName() const;

		int get_fd();
		void set_fd(int fd);
		void set_ip_address(std::string ipadd);

		// bool parsing_nickname();

	private:

		// Client(const Client& rhs);
		// Client& operator=(const Client& rhs);

		int _fd;				//-> client file descriptor
		std::string _ipAddress; //-> client ip address	

		// std::string _nickname;
		// std::string _realName;

};

#endif
