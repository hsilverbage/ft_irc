#include "Command.hpp"

void	Command::quit(std::vector<std::string> args, Client* client)
{
	std::string	reason = ""
	if (args.size() > 1)
	{
		for (size_t i = 1; i < args.size(); i++)
			reason += args[i];
	}

	std::map<std::string, Channel*> channels = _Serv->get_channel();
	
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second->is_client_in_channel(client->get_fd()))
		{
			it->second->remove_client_from_channel(client);
			it->second->send_msg_to_everyone_in_channel(client->get_nickname() + " Quit: Bye for now! " + reason + "\r\n");
		}
	}
}
