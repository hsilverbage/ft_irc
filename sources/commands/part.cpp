#include "Command.hpp"

void send_part(Channel* channel, Client* client, std::string reason)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + " PART " + channel->get_channel_name() + " " + reason + "\r\n";
	
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void Command::part(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "PART"));

	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::string reason						= "";

	if (args.size() > 2)
	{
		for (size_t i = 2; i < args.size(); i++)
		{
			if (args[i][0] != '#' && args[i][0] != '&')
				for (size_t j = i; j < args.size(); j++)
					reason += args[j];
		}
	}

	for (size_t i = 1; i < args.size(); i++)
	{
		std::map<std::string, Channel*>::iterator it = channel.find(args[i]);

		if (args[i][0] != '#')
			return;
		if (it == channel.end())
			NumericReplies::ERR_NOSUCHCHANNEL(client, args[i]);
		else
		{
			it->second->remove_client_from_channel(client);
			send_part(it->second, client, reason);
		}
	}
}
