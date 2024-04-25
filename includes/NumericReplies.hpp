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

		// NOTIFICATION

		static void NOTIF_CHANGENICK(Client* client, std::string newNick);
		static void NOTIF_USERNAME_SET(Client* client);

		// REPLY

		static void RPL_WELCOME(Client* client);

	private :

		NumericReplies() {};
		~NumericReplies() {};
};

#endif
