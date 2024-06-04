#include "Command.hpp"

void Command::invite(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "INVITE"));

	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.find(args[2]);
	if (it == channel.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[2]));
	
	std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator iter;
	for (iter = client_map.begin(); iter != client_map.end(); ++iter) 
	{
		if (iter->second->get_nickname() == args[1])
		{
			if (it->second->is_client_in_channel(iter->first))
				return (NumericReplies::ERR_USERONCHANNEL(client, args[2]));
			else if (it->second->get_invite_only() && !channel[args[2]]->isOperator(client->get_fd()))
				return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[2]));
			else if (it->second->is_banned(args[1]))
			{
				it->second->unban_client(iter->second);
				NumericReplies::RPL_INVITING(client, args[2], iter->second->get_nickname());
			}
			else
				NumericReplies::RPL_INVITING(client, args[2], iter->second->get_nickname());
		}
	}
}

