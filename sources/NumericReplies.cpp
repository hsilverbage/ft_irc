#include "NumericReplies.hpp"

void NumericReplies::ERR_NEEDMOREPARAMS(Client* client, std::string cmd)
{
	std::stringstream ss;

	ss << "461 : " << client->get_nickname() << " " << cmd << " :Not enough parameter\n\r";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NONICKNAMEGIVEN(Client* client)
{
	std::stringstream ss;

	ss << "431 : " << client->get_nickname() << " :No nickname given\n\r";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NICKNAMEINUSE(Client* client)
{
	std::stringstream ss;

	ss << "433 : " << client->get_nickname() << " :Nickname is already in use\n\r";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_ERRONEUSNICKNAME(Client* client)
{
	std::stringstream ss;

	ss << "432 : " << client->get_nickname() << " :Erroneus nickname\n\r";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::NOTIF_CHANGENICK(Client* client, std::string newNick)
{
	if (client->get_nickname() != "")
		std::cout << client->get_nickname() << " changed his nickname to " << newNick << std::endl;
	/*
		The NICK message may be sent from the server to clients to acknowledge their NICK command was successful, and to
	   inform other clients about the change of nickname. In these cases, the <source> of the message will be the old
	   nickname [ [ "!" user ] "@" host ] of the user who is changing their nickname.

		Message Examples:

		:WiZ NICK Kilroy          ; WiZ changed his nickname to Kilroy.

		:dan-!d@localhost NICK Mamoped
								; dan- changed his nickname to Mamoped.

		TODO SEE IF I SEND THIS TO EVERYONE IN THE CHANEL OR NOT
	*/
}
