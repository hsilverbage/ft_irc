#include "Command.hpp"

void send_quit(Channel* channel, Client* client, std::string reason)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + " QUIT\r\n";

	if (!reason.empty())
		msg += reason;
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void Command::quit(std::vector<std::string> args, Client* client)
{
	std::string reason = "";
	if (args.size() > 1)
		for (size_t i = 1; i < args.size(); i++)
			reason += args[i];

	std::map<std::string, Channel*> channels = _Serv->get_channel();

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second->is_client_in_channel(client->get_fd()))
		{
			it->second->remove_client_from_channel(client);
			send_quit(it->second, client, reason);
		}
	}
	this->_Serv->quit_client(client);
}
