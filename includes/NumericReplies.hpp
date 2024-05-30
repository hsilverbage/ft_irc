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
		static void ERR_BANNEDFROMCHAN(Client* client, std::string channel);
		static void ERR_CHANNELISFULL(Client* client, std::string channel);
		static void ERR_INVITEONLYCHAN(Client* client, std::string channel);
		static void RPL_INVITING(Client* client, std::string channel);
		static void ERR_NOTONCHANNEL(Client* client, std::string name);
		static void ERR_USERONCHANNEL(Client* client, std::string channel);
		static void ERR_CHANOPRIVSNEEDED(Client* client, std::string channelName);
		static void ERR_USERNOTINCHANNEL(Client* client, std::string nickname, std::string channel);
		static void ERR_NOSUCHNICK(Client* client, std::string noSuchelement);
		static void ERR_NORECIPIENT(Client* client, std::string command);
		static void ERR_CANNOTSENDTOCHAN(Client* client, std::string channel);
		static void ERR_USERSDONTMATCH(Client* client);
		static void ERR_UMODEUNKNOWNFLAG(Client* client);

		// NOTIFICATION

		static void NOTIF_CHANGENICK(Client* client, std::string newNick);
		static void NOTIF_USERNAME_SET(Client* client);

		// REPLY

		static void RPL_WELCOME(Client* client);
		static void RPL_TOPIC(Client* client);
		static void RPL_JOIN(Client* client, std::string channelName, Channel* channel);
		static void RPL_TOPICWHOTIME(Client* client);
		static void RPL_NAMREPLY(Client* client, std::map<int, Client*> clients, std::string channel);
		static void RPL_ENDOFNAMES(Client* client, std::string channel);
		static void RPL_TOPIC(Client* client, std::string channelName, std::string topicName);
		static void RPL_NOTOPIC(Client* client, std::string channelName);
		static void RPL_TOPICWHOTIME(Client* client, Channel* channel);
		static void	RPL_CHANNELMODEIS(Client* client, Channel* channel, std::string modes);

	private:

		NumericReplies() {};
		~NumericReplies() {};
};

#endif
