#include "Command.hpp"

void Command::unban(std::vector<std::string> args, Client* client)
{
    std::cout << "UNBAN CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
    if (args.size() < 3)
        return (NumericReplies::ERR_NEEDMOREPARAMS(client, "BAN"));

    std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.find(args[1]);

	if (it == channel.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
    if (!it->second->isOperator(client->get_fd()))
        return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, it->second->get_channel_name()));

    std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator iter;
	for (iter = client_map.begin(); iter != client_map.end(); iter++) 
	{
        if (it->second->is_banned(iter->second->get_nickname()) && iter->first != client->get_fd())
        {
            std::cout << "debug in the if to deban " << std::endl;
            it->second->unban_client(iter->second);
            return ;
        }
    }
}