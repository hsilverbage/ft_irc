#include "Command.hpp"

void Command::user(std::vector<std::string> args, Client* client)
{
	if (client->get_pwdIsCorrect() == false)
		return;
	if (args.size() < 5)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "USER"));
	if (args[1].empty())
	{
		NumericReplies::ERR_NEEDMOREPARAMS(client, "USER");
		return;
	}
	if (client->get_username() != "" || args[2][0] != '0' || args[3][0] != '*')
	{
		NumericReplies::ERR_ALREADYREGISTERED(client);
		return;
	}
	client->set_username(args[1]);
	std::string realname = args[4];
	if (args.size() > 4)
	{
		for (size_t i = 5; i < args.size(); i++)
		{
			realname += ' ';
			realname += args[i];
		}
	}
	client->set_realname(realname);
	NumericReplies::NOTIF_USERNAME_SET(client);
	if (client->get_pwdIsCorrect() && client->get_nickname() != "" && client->get_username() != "" && client->get_isConnected() == false)
	{
		NumericReplies::RPL_WELCOME(client);
		client->set_isConnected(true);
	}
}

