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

		// NOTIFICATION

		static void	NOTIF_CHANGENICK(Client* client);

	private:

		NumericReplies() {};
		~NumericReplies() {};
};

#endif
