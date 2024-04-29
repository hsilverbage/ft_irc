#include "NumericReplies.hpp"

void NumericReplies::ERR_NEEDMOREPARAMS(Client* client, std::string cmd)
{
	std::stringstream ss;

	ss << "461 : " << client->get_nickname() << " " << cmd << " :Not enough parameter\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NOSUCHCHANNEL(Client* client, std::string channel)
{
	std::stringstream ss;

	std::cout << client->get_nickname() << " " << channel << " : No such channel" << std::endl;
	// CHECK ERROR MSG : "<client> <channel> :No such channel"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::ERR_BADCHANMASK(Client* client, std::string channelName)
{
	std::stringstream ss;

	ss << channelName << " :Bad Channel Mask\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::RPL_TOPICWHOTIME(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL : "<client> <channel> <nick> <setat>"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::RPL_NAMREPLY(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL :  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::RPL_ENDOFNAMES(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL :   "<client> <channel> :End of /NAMES list"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::RPL_TOPIC(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL :  "<client> <channel> :<topic>"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::ERR_INVITEONLYCHAN(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL : "<client> <channel> :Cannot join channel (+i)"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::ERR_BANNEDFROMCHAN(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL : "<client> <channel> :Cannot join channel (+b)"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void	NumericReplies::ERR_CHANNELISFULL(Client* client)
{
	std::stringstream ss;

	// WRITE THE ERROR MSG W/ CHANNEL :  "<client> <channel> :Cannot join channel (+l)"
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_BADCHANNELKEY(Client* client, std::string channel)
{
	std::stringstream ss;

	ss << client->get_nickname() << " " << channel << " : Cannot join channel (+k)" << std::endl;
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_TOOMANYCHANNELS(Client* client, std::string channel)
{
	std::stringstream ss;

	std::cout << client->get_nickname() << " " << channel << " : You have joined too many channels" << std::endl;
	// CHECK  :  "<client> <channel> :You have joined too many channels"
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

	ss << "431 : " << client->get_nickname() << " :No nickname given\r\n";
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

	ss << "433 : " << client->get_nickname() << " :Nickname is already in use\r\n";
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

	ss << "432 : " << client->get_nickname() << " :Erroneus nickname\r\n";
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
	{
		std::stringstream ss;

		ss << client->get_nickname() << " changed his nickname to " << newNick << "\"\r\n";
		std::string str = ss.str();
		if (ss.fail())
		{
			std::cerr << "stringstream failed" << std::endl;
			return;
		}
		if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	}
}

void NumericReplies::ERR_ALREADYREGISTERED(Client* client)
{
	std::stringstream ss;

	ss << "462 : " << client->get_nickname() << " :You may not reregister\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::NOTIF_USERNAME_SET(Client* client)
{
	std::stringstream ss;

	ss << "User gets registered with username \"" << client->get_username() << "\" and real name \"" << client->get_realname() << "\"\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_PASSWDMISMATCH(Client* client)
{
	std::stringstream ss;

	ss << "464 : " << client->get_username() << " :Password incorrect\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size() + 1, 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_WELCOME(Client* client)
{
	std::stringstream ss;

	ss << "001 : " << client->get_nickname() << " :Welcome to the best_irc Network, " << client->get_nickname() << "[!" << client->get_username() << "@localhost]\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}
