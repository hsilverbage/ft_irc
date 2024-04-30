#ifndef NUMERICPREPLIES_HPP
#define NUMERICPREPLIES_HPP

#include "Server.hpp"

class NumericReplies
{
	public:

		// ERROR

		static void ERR_NEEDMOREPARAMS(Client* client, std::string cmd);
		static void ERR_NONICKNAMEGIVEN(Client* client);
		static void ERR_NICKNAMEINUSE(Client* client);
		static void ERR_ERRONEUSNICKNAME(Client* client);
		static void ERR_ALREADYREGISTERED(Client* client);
		static void ERR_PASSWDMISMATCH(Client* client);
		static void ERR_NOSUCHCHANNEL(Client* client, std::string channel);
		static void ERR_TOOMANYCHANNELS(Client* client, std::string channel);
		static void ERR_BADCHANNELKEY(Client* client, std::string channel);
		static void ERR_BANNEDFROMCHAN(Client* client);
		static void ERR_CHANNELISFULL(Client* client);
		static void ERR_INVITEONLYCHAN(Client* client);
		static void ERR_NOTONCHANNEL(Client* client, std::string name);
		static void ERR_CHANOPRIVSNEEDED(Client* client, std::string channelName);

		// NOTIFICATION

		static void NOTIF_CHANGENICK(Client* client, std::string newNick);
		static void NOTIF_USERNAME_SET(Client* client);

		// REPLY

		static void RPL_WELCOME(Client* client);
		static void RPL_TOPIC(Client* client);
		static void RPL_TOPICWHOTIME(Client* client);
		static void RPL_NAMREPLY(Client* client);
		static void RPL_ENDOFNAMES(Client* client);
		static void RPL_TOPIC(Client* client, std::string channelName, std::string topicName);
		static void RPL_NOTOPIC(Client* client, std::string channelName);

	private:

		NumericReplies() {};
		~NumericReplies() {};
};

#endif
