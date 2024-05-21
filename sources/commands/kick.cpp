#include "Command.hpp"

void	Command::kick(std::vector<std::string> args, Client* client)
{
	std::cout << "KICK CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
    if (args.size() < 3)
        return (NumericReplies::ERR_NEEDMOREPARAMS(client, "KICK"));

    std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.find(args[1]);

	if (it == channel.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
    if (!it->second->is_client_in_channel(client->get_fd()))
        return (NumericReplies::ERR_NOTONCHANNEL(client, client->get_nickname()));
    if (!it->second->isOperator(client->get_fd()))
        return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, it->second->get_channel_name()));

    std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator iter;
	for (iter = client_map.begin(); iter != client_map.end(); iter++) 
	{
        if (it->second->is_nick_in_channel(args[2]))
        {
            if (args[2] == client->get_nickname())
                break;
            if (args.size() == 3)
                it->second->remove_client_from_channel(iter->second, "No reason");
            else if (args.size() == 4)
                it->second->remove_client_from_channel(iter->second, args[4]);
            return ;
        }
    }
    if (iter == client_map.end())
	    return (NumericReplies::ERR_USERNOTINCHANNEL(client, args[2], args[1]));
}