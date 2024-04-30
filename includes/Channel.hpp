
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
		std::map<int, Client*>& get_banned();

		size_t get_maxClient();

		std::string&	get_key();
		std::string&	get_topic();
		std::string&	get_channel_name();
		std::string&	who_set_topic();

		size_t			get_nbClient();
		
		void ban_client(Client* client, std::string reason);
		void set_nbClient(size_t actualNb);
		void set_topic(std::string topic);
		void add_client_to_channel(Client* client);
		void remove_client_from_channel(Client* client, std::string reason);
		void add_client_to_operators(Client* client);
		void remove_client_from_operators(Client* client);
		void send_msg_to_everyone_in_channel(const std::string str);
		void set_maxClient(size_t max);
		void set_topic(std::string topic, Client* client);
		void set_topicProtected(bool status);

		bool get_topicProtected();
		bool isOperator(int fd);
		bool is_client_in_channel(int fd);


	private :

		std::map<int, Client*> _Clients;
		std::map<int, Client*> _ClientOperators;
		std::map<int, Client*> _Banned;

		size_t _nbClient;
		size_t _maxClient;

		std::string _channelName;
		std::string _key;
		std::string _topic;
		std::string	_whoSetTopic;
	

		bool	_topicProtected;
};

#endif
