
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
	public:

		Channel();
		~Channel();

		std::map<int, Client*>	get_clients();

	private:

		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);

		std::map<int, Client*>	_Clients;
		size_t					_maxClient;
		std::string 			_nameChannel;
};

#endif
