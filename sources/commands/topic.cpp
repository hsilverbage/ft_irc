#include "Command.hpp"

void	send_topic(Channel* channel, Client* client, std::string topic)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + " QUIT\r\n";

	if (!reason.empty())
		msg += reason;
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
			// it_channel->second->set_topic("");
			it_channel->second->send_msg_to_everyone_in_channel("Clearing the topic on " + args[1]);
		}
		else
		{
			if (it_channel->second->get_topic().empty())
				it_channel->second->send_msg_to_everyone_in_channel(client->get_nickname() + " set the topic to : " + args[2] +  " on " + it_channel->second->get_channel_name());
			else
				it_channel->second->send_msg_to_everyone_in_channel(client->get_nickname() + " changed the topic : " + it_channel->second->get_topic() + " to" + args[2] + " on " + it_channel->second->get_channel_name());
			// it_channel->second->set_topic(args[2]);
		}
	}

}
