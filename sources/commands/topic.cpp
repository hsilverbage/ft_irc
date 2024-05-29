#include "Command.hpp"

void	send_topic(Channel* channel, Client* client, std::string topic)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + " QUIT\r\n";

	if (!topic.empty())
		msg += topic;
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void	Command::topic(std::vector<std::string> args, Client* client)
{
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
		{
			NumericReplies::RPL_TOPIC(client, args[1], it_channel->second->get_topic());
			NumericReplies::RPL_TOPICWHOTIME(client);
		}
		return;
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
			it_channel->second->set_topic("", client);
			send_topic(it_channel->second, client, "");
		}
		else
		{
			if (it_channel->second->get_topic().empty())
				send_topic(it_channel->second, client, args[2]);
			else
				send_topic(it_channel->second, client, args[2]);
			it_channel->second->set_topic(args[2], client);
		}
	}

}
