#ifndef	CLIENT_HPP
#define	CLIENT_HPP

#include <iostream>

class Client
{
	public :
	
		Client();
		~Client();
	
		std::string&	getNickname() const;
		std::string&	getRealName() const;
		std::string&	getAddress() const;


	private :

		Client(const Client& rhs);
		Client& operator=(const Client &rhs);
		
		bool	parsing_nickname();

		std::string	_nickname;
		std::string	_realName;
		std::string	_address; //address of the host that the client is connecting from
};



#endif
