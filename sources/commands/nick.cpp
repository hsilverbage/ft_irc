#include "Command.hpp"

void Command::nick(std::vector<std::string> args, Client* client)
{
	if (client->get_pwdIsCorrect() == false)
		return;
	if (args.size() < 2)
	{
		NumericReplies::ERR_NONICKNAMEGIVEN(client);
		return;
	}
	std::map<int, Client*> clients = _Serv->get_clients_map();
	std::map<int, Client*>::iterator ite = clients.begin();
	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.begin();
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->get_nickname() == args[1])
		{
			NumericReplies::ERR_NICKNAMEINUSE(client);
			return;
		}
	}
	if (args[1].empty() || args[1].find_first_of(":$#") == 0 || args.size() != 2)
	{
		NumericReplies::ERR_ERRONEUSNICKNAME(client);
		return;
	}
	for (it = channel.begin(); it != channel.end(); it++)
	{
		for (ite = clients.begin(); ite != clients.end(); ite++)
		{
			if (it->second->is_client_in_channel(ite->second->get_fd()))
				NumericReplies::NOTIF_CHANGENICK(client, args[1], ite->second->get_fd());
		}
		ite = clients.begin();
	}
	client->set_nickname(args[1]);
	if (client->get_pwdIsCorrect() && client->get_nickname() != "" && client->get_username() != "" && client->get_isConnected() == false)
	{
		NumericReplies::RPL_WELCOME(client);
		client->set_isConnected(true);
	}
}
