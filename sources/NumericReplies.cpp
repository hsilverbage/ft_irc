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

void NumericReplies::ERR_USERNOTINCHANNEL(Client* client, std::string nickname, std::string channel)
{
	std::stringstream ss;

	//   "<client> <nick> <channel> :They aren't on that channel"

	ss << "441 : " << client->get_nickname() << " " << nickname << " " << channel << " "
	   << " : They aren't on that channel\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NORECIPIENT(Client* client, std::string command)
{
	std::stringstream ss;

	// "<client> :No recipient given (<command>)"
	ss << "411 : " << client->get_nickname() << " : :No recipient given " << command << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NOSUCHNICK(Client* client, std::string noSuchelement)
{
	std::stringstream ss;

	// CHECK  "<client> <nickname> :No such nick/channel"
	ss << "401 : " << client->get_nickname() << " : No such " << noSuchelement << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_CANNOTSENDTOCHAN(Client* client, std::string channel)
{
	std::stringstream ss;

	// CHECK "<client> <channel> :Cannot send to channel"
	ss << "404 : " << client->get_nickname() << " " << channel << " : Cannot send to channel\r\n";
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

	ss << "403 : " << client->get_nickname() << " " << channel << " : No such channel\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_TOPICWHOTIME(Client* client)
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

void NumericReplies::RPL_NAMREPLY(Client* client, std::map<int, Client*> clients, std::string channel)
{
	std::stringstream ss;

	// CHECK :  "<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
	ss << ": 353 " << client->get_nickname() << " = " << channel << " : ";
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		ss << it->second->get_nickname() << " ";
	ss << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_INVITING(Client* client, std::string channel)
{
	std::stringstream ss;

	// CHECK :   "<client> <nick> <channel>"
	ss << "341 : " << client->get_nickname() << " " << channel << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_ENDOFNAMES(Client* client, std::string channel)
{
	std::stringstream ss;

	// CHECK :   "<client> <channel> :End of /NAMES list"
	ss << ": 366 " << client->get_nickname() << " " << channel << " :End of /NAMES list\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_TOPIC(Client* client)
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

void NumericReplies::ERR_INVITEONLYCHAN(Client* client, std::string channel)
{
	std::stringstream ss;

	//  CHECK : "<client> <channel> :Cannot join channel (+i)"
	ss << "473 : " << client->get_nickname() << " " << channel << " : Cannot join channel (+i)\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_BANNEDFROMCHAN(Client* client, std::string channel)
{
	std::stringstream ss;

	// CHECK : "<client> <channel> :Cannot join channel (+b)"
	ss << "474 : " << client->get_nickname() << " " << channel << " : Cannot join channel (+b)\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_CHANNELISFULL(Client* client, std::string channel)
{
	std::stringstream ss;

	// CHECK  :  "<client> <channel> :Cannot join channel (+l)"
	ss << "471 : " << client->get_nickname() << " " << channel << " : Cannot join channel (+l)\r\n";
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

		ss << ":" << client->get_nickname() << " NICK " << newNick << "\"\r\n";
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

	ss << "User gets registered with username \"" << client->get_username() << "\" and real name \""
	   << client->get_realname() << "\"\r\n";
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

	ss << "001 : " << client->get_nickname() << " :Welcome to the best_irc Network, " << client->get_nickname() << "[!"
	   << client->get_username() << "@localhost]\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_CHANOPRIVSNEEDED(Client* client, std::string channel)
{
	std::stringstream ss;

	ss << "482 : " << client->get_nickname() << " " << channel << ": You're not channel operator\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_USERONCHANNEL(Client* client, std::string channel)
{
	std::stringstream ss;

	ss << "443 : " << client->get_nickname() << " " << channel << ": is already on channel\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_NOTONCHANNEL(Client* client, std::string name)
{
	std::stringstream ss;

	ss << "442 : " << client->get_nickname() << " " << name << " :You're not on that channel\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_NOTOPIC(Client* client, std::string channelName)
{
	std::stringstream ss;

	ss << "331 : " << client->get_nickname() << " " << channelName << " :No topic is set\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_TOPIC(Client* client, std::string channelName, std::string topicName)
{
	std::stringstream ss;

	ss << "332 : " << client->get_nickname() << " " << channelName << " :" << topicName << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_TOPICWHOTIME(Client* client, Channel* channel)
{
	std::stringstream ss;

	ss << "333 : " << client->get_nickname() << " " << channel->get_channel_name() << " the topic was set by"
	   << channel->who_set_topic() << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_USERSDONTMATCH(Client* client)
{
	std::stringstream ss;

	ss << "502 : " << client->get_nickname() << " :Cant change mode for other users\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::ERR_UMODEUNKNOWNFLAG(Client* client)
{
	std::stringstream ss;

	ss << "501 : " << client->get_nickname() << " :Unknown MODE flag\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}
	if (send(client->get_fd(), str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void NumericReplies::RPL_JOIN(Client* client, std::string channelName, Channel* channel)
{
	std::stringstream ss;

	ss << ":" << client->get_nickname() << " JOIN " << channelName << "\r\n";
	std::string str = ss.str();
	if (ss.fail())
	{
		std::cerr << "stringstream failed" << std::endl;
		return;
	}

	std::map<int, Client*> clients = channel->get_clients();

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, str.c_str(), str.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}
