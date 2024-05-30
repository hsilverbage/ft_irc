#include "Command.hpp"

void Command::privmsg(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 3)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "PRIVMSG"));

	size_t i = 0;

	std::string message;
	std::vector<std::string> target_vec;
	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator ite =	channel.begin();
	std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator it = client_map.begin();

	if (args[1][0] && (args[1][0] == '@' || args[1][0] == '#' || args[1][0] == '%'))
	{
		while (args[i + 1][0] && args[i + 1][0] != ':')
		{
			if (ite->second->is_channel(channel, args[i + 1]))
				target_vec.push_back(args[i + 1]);
			else
				return (NumericReplies::ERR_NOSUCHNICK(client, args[i + 1]));
			i++;
		}
		if (args[i + 1][0] && args[i + 1][0] == ':')
		{
			while (i + 1 < args.size())
			{
				message += args[i + 1];
				if (i + 1 != args.size())
					message.push_back(' ');
				i++;
			}
		}
		else
			return (NumericReplies::ERR_NORECIPIENT(client, "PRIVMSG"));
		i = 0;
		for (ite = channel.begin(); ite != channel.end(); ite++)
		{
			if (ite->first == target_vec[i] && ite->second->is_client_in_channel(client->get_fd()))
				ite->second->send_msg_to_everyone_in_channel(message, client->get_nickname(), ite->first);
			else if (ite->first == target_vec[i] && !ite->second->is_client_in_channel(client->get_fd()))
				return (NumericReplies::ERR_CANNOTSENDTOCHAN(client, target_vec[i]));
			i++;
		}
	}
	else
	{
		std::cout << "l53" << std::endl;
		while (args[i + 1][0] && args[i + 1][0] != ':')
		{
			if (client->is_client(client_map, args[i + 1]))
				target_vec.push_back(args[i + 1]);
			else
				return (NumericReplies::ERR_NOSUCHNICK(client, args[i + 1]));
			i++;
		}
		if (args[i + 1][0] && args[i + 1][0] == ':')
		{
			while (i + 1 < args.size())
			{
				message += args[i + 1];
				if (i + 1 != args.size())
					message.push_back(' ');
				i++;
			}
		}
		else
			return (NumericReplies::ERR_NORECIPIENT(client, "PRIVMSG"));
		i = 0;
		for (it = client_map.begin(); it != client_map.end(); it++)
		{
			std::cout << "l77" << std::endl;
			if (it->second->get_nickname() == target_vec[i])
				ite->second->send_msg_to_someone(client, message, it->second);
			else if (it == client_map.end())
				return (NumericReplies::ERR_NOSUCHNICK(client, target_vec[i]));
		}
	}
		
}
