#include "Command.hpp"

void Command::ban(std::vector<std::string> args, Client* client)
{
    std::cout << "BAN CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
    if (args.size() < 3)
        return (NumericReplies::ERR_NEEDMOREPARAMS(client, "BAN"));

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
	for (iter = client_map.begin(); iter != client_map.end(); ++iter) 
	{
        if (it->second->is_client_in_channel(iter->first))
        {
            it->second->ban_client(client, args[4]);
            return ;
        }
    }
    if (iter == client_map.end())
	    return (NumericReplies::ERR_USERNOTINCHANNEL(client, args[2], args[1]));

}