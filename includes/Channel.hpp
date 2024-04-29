
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
	public:

		Channel();
		Channel(std::string key, Client* client, std::string channelName);
		~Channel();

		std::map<int, Client*>& get_clients();
		std::map<int, Client*>& get_ClientOperators();

		size_t get_maxClient();

		std::string& get_key();
		std::string& get_topic();
		std::string& get_channel_name();
		
		void set_topic(std::string topic);
		void add_client_to_channel(Client* client);
		void remove_client_from_channel(Client* client);
		void add_client_to_operators(Client* client);
		void remove_client_from_operators(Client* client);
		void send_msg_to_everyone_in_channel(const std::string str);
		void set_maxClient(size_t max);

	private :

		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);

		std::map<int, Client*> _Clients;
		std::map<int, Client*> _ClientOperators;

		size_t _maxClient; // TODO WHRERE DO WE SET MAX IENCLE

		std::string _channelName;
		std::string _key;
		std::string _topic;
};

#endif
