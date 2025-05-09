
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Client;

class Channel
{
	public:

		Channel();
		Channel(std::string key, Client* client, std::string channelName);
		~Channel();

		std::map<int, Client*>& get_clients();
		std::map<int, Client*>& get_ClientOperators();
		std::map<int, Client*>& get_banned();
		std::vector<Client*>&	get_invited();

		size_t get_maxClient();

		std::string&	get_key();
		std::string&	get_topic();
		std::string&	get_channel_name();
		std::string&	who_set_topic();
		std::string		get_modes();
		bool			get_topicProtected();
		bool			get_invite_only();
		bool 			get_pwd_protected();
		bool 			get_limit_mode();
		size_t			get_nbClient();

		void set_invited_client(Client* client);
		void set_invite_only(bool status);
		void set_nbClient(size_t actualNb);
		void set_topic(std::string topic);
		void set_topic(std::string topic, Client* client);
		void set_topicProtected(bool status);
		void set_maxClient(size_t max);
		void set_pwd_protected(bool status);
		void set_limit_mode(bool status);
		void set_pwd(std::string pwd);

		bool isOperator(int fd);
		bool is_banned(std::string nickname);
		bool is_client_in_channel(int fd);
		bool is_nick_in_channel(std::string nickname);
		bool is_channel(std::map<std::string, Channel*> channels, std::string channelTarg);

		void ban_client(Client* client, std::string reason);
		void unban_client(Client* client);
		
		void send_msg_to_everyone_in_channel(std::string str, std::string client, std::string channelName);
		void send_msg_to_someone(Client* client, std::string str, Client* target);
		
		void add_client_to_channel(Client* client);
		void remove_client_from_channel_no_check(Client* client);
		void remove_client_from_channel(Client* client);

		void add_client_to_operators(Client* client);
		void remove_client_from_operators(Client* client);

	private :

		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);

		std::map<int, Client*>	_Clients;
		std::map<int, Client*>	_ClientOperators;
		std::map<int, Client*>	_Banned;
		std::vector<Client*>	_Invited;

		size_t _nbClient;
		size_t _maxClient;

		std::string _channelName;
		std::string _key;
		std::string _topic;
		std::string	_whoSetTopic;
		std::string _modes;


		bool	_inviteOnly;
		bool	_topicProtected;
		bool	_pwdProtected;
		bool	_limitMode;
};

#endif
