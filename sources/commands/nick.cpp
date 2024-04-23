#include "Command.hpp"

void Command::nick(std::vector<std::string> args, Client* client)
{
	std::cout << "NICK CMD\t" << args[0] << client->get_nickname() << std::endl;

	if (args.size() < 2)
	{
		NumericReplies::ERR_NONICKNAMEGIVEN(client);
		return;
	}
	std::map<int, Client*> clients = _Serv->get_clients_map();

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->get_nickname() == args[1])
		{
			NumericReplies::ERR_NICKNAMEINUSE(client);
			return;
		}
	}
	if (args[1][0] == ':' || args[1][0] == '$' || args[1][0] == '#' || args.size() != 2)
		NumericReplies::ERR_ERRONEUSNICKNAME(client);
	client->set_nickname(args[1]);
	NumericReplies::NOTIF_CHANGENICK(client);
}
