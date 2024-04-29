#include "Command.hpp"

void Command::part(std::vector<std::string> args, Client* client)
{
	std::cout << "PART CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
	{
		NumericReplies::ERR_NEEDMOREPARAMS(client, "PART");
		return;
	}

	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::string reason = "";

	if (args.size() > 2)
	{
		for (size_t i = 2; i < args.size(); i++)
		{
			if (args[i][0] != '#' && args[i][0] != '&')
			{
				for (size_t j = 0; j < args.size(); j++)
					reason += args[j];
			}
		}
	}

	for (size_t i = 1; i < args.size(); i++)
	{
		std::map<std::string, Channel*>::iterator it = channel.find(args[i]);

		std::cout << "test1" << std::endl;
		if (it == channel.end())
		{
			NumericReplies::ERR_NOSUCHCHANNEL(client, args[i]);
			std::cout << "test2" << std::endl;
		}
		else
		{
			it->second->remove_client_from_channel(client, reason);	
			std::cout << "test3" << std::endl;
		}
	}
}

*/
