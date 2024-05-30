#include "Command.hpp"

void send_msg_mode(Channel* channel, std::string mode)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = "MODE " + channel->get_channel_name() + " " + mode + "\r\n";

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void send_msg_mode_operator(Channel* channel, std::string mode, std::string target)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = "MODE " + channel->get_channel_name() + " " + mode + " " + target + "\r\n";

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}


void invite_mode(std::vector<std::string> args, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_invite_only(true);
		send_msg_mode(channel, "+i");
	}
	else
	{
		channel->set_invite_only(false);
		send_msg_mode(channel, "-i");
	}
}

void limit_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{
		if (args.size() < 4)
			return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
		if (args[3].find_first_not_of("0123456789") != std::string::npos)
			return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
		unsigned long max;
		std::stringstream ss(args[3]);
		ss >> max;
		ss.str();
		if (ss.fail())
			return;
		if (max > SIZE_MAX)
			return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
		channel->set_maxClient(max);
		send_msg_mode(channel, "+l");
	}
	else
	{
		channel->set_maxClient(SIZE_MAX - 1);
		send_msg_mode(channel, "-l");
	}
}

void topic_mode(std::vector<std::string> args, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_topicProtected(true);
		send_msg_mode(channel, "+t");
	}
	else
	{
		channel->set_topicProtected(false);
		send_msg_mode(channel, "-t");
	}
}

void key_mode(std::vector<std::string> args, Channel* channel) 
{
	if (args[2][0] == '+')
	{
		channel->set_pwd_protected(true);
		send_msg_mode(channel, "+k");
	}
	else
	{
		channel->set_pwd_protected(false);
		send_msg_mode(channel, "-k");
	}
}

void operator_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args.size() < 4)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
	if (!channel->is_nick_in_channel(args[3]))
		return (NumericReplies::ERR_NOSUCHNICK(client, args[3]));
	std::map<int, Client*> clients = channel->get_clients();
	std::map<int, Client*>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++)
		if (it->second->get_nickname() == args[3])
			break;
	if (it != clients.end())
	{
		if (args[2][0] == '+')
		{
			channel->add_client_to_operators(it->second);
			send_msg_mode_operator(channel, "+o", it->second->get_nickname());
		}
		else
		{
			channel->remove_client_from_operators(it->second);
			send_msg_mode_operator(channel, "-o", it->second->get_nickname());
		}
	}
}

void Command::mode(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 3)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));

	std::map<std::string, Channel*> channels	 = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channels.find(args[1]);

	if (it == channels.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
	if (!it->second->isOperator(client->get_fd()))
		return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[1]));
	if (args[2][0] != '-' || args[2][0] != '+')
		return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
	if (args[2][1] == 'i')
		return (invite_mode(args, it->second));
	if (args[2][1] == 'l')
		return (limit_mode(args, client, it->second));
	if (args[2][1] == 't')
		return (topic_mode(args, it->second));
	if (args[2][1] == 'k')
		return (key_mode(args, it->second));
	if (args[2][1] == 'o')
		return (operator_mode(args, client, it->second));
	return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
}
