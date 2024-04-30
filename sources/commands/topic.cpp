#include "Command.hpp"

void	Command::topic(std::vector<std::string> args, Client* client)
{
	std::cout << "TOPIC CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
	{
		NumericReplies::ERR_NEEDMOREPARAMS(client, "TOPIC");
		return ;
	}
	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it_channel = channel.find(args[1]);

	if (it_channel == channel.end())
	{
		NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]);
		return;
	}
	std::map<int, Client*>	clients = it_channel->second->get_clients();
	std::map<int, Client*>::iterator it_clients =clients.find(client->get_fd());
	if (it_clients == clients.end())
	{
		NumericReplies::ERR_NOTONCHANNEL(client, args[1]);
		return;
	}
	if (args.size() < 3)
	{
		if (it_channel->second->get_topic().empty())
			NumericReplies::RPL_NOTOPIC(client, args[1]);
		else
			NumericReplies::RPL_TOPIC(client, args[1], it_channel->second->get_topic());
	}
	else
	{
		if (it_channel->second->get_topicProtected() && it_channel->second->isOperator(client->get_fd()) == false)
		{
			NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[1]);
			return ;
		}
		if (args[2][0] == ':' && args[2].size() == 1)
		{
			it_channel->second->set_topic("");
			it_channel->second->send_msg_to_everyone_in_channel("Clearing the topic on " + args[1]);
		}

	}

}


If RPL_TOPIC is returned to the client sending this command, RPL_TOPICWHOTIME SHOULD also be sent to that client.

If the topic of a channel is changed or cleared, every client in that channel (including the author of the topic change) will receive a TOPIC command with the new topic as argument (or an empty argument if the topic was cleared) alerting them to how the topic has changed. If the <topic> param is provided but the same as the previous topic (ie. it is unchanged), servers MAY notify the author and/or other users anyway.

Clients joining the channel in the future will receive a RPL_TOPIC numeric (or lack thereof) accordingly.

Numeric Replies:

    RPL_NOTOPIC (331)
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333)

Command Examples:

  TOPIC #test :New topic          ; Setting the topic on "#test" to
                                  "New topic".

  TOPIC #test :                   ; Clearing the topic on "#test"

  TOPIC #test                     ; Checking the topic for "#test"
