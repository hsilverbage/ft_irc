
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
	public:

		Channel(std::string key, Client* client);
		~Channel();

		std::map<int, Client*> get_clients();

		std::string&			get_key();
		std::string&			get_topic();
		std::vector<Client*>& 	get_ClientOperators();
		void					set_topic(std::string topic);
		void					get_maxClient();
		size_t					set_maxClient(size_t max);
	

	private:

		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);

		std::map<int, Client*>	 	_Clients;
		std::vector<Client*> 		_ClientOperators;
		size_t 						_maxClient; //TODO WHRERE DO WE SET MAX IENCLE
		std::string 				_nameChannel;
		std::string 				_key;
		std::string 				_topic;

#endif
