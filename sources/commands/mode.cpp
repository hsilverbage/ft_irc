#include "Command.hpp"

void send_msg_mode(Channel* channel, std::string mode, Client* client)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + "!" + client->get_username() + "@localhost MODE " + channel->get_channel_name() + " " + mode + "\r\n";

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void send_msg_mode_with_param(Channel* channel, std::string mode, Client* client, std::string param)
{
	std::map<int, Client*> clients = channel->get_clients();
	std::string msg				   = ":" + client->get_nickname() + "!" + client->get_username() + "@localhost MODE " +
					  channel->get_channel_name() + " " + mode + " " + param + "\r\n";

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); it++)
		if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
}

void invite_mode(std::vector<std::string> args, Channel* channel, Client* client)
{
	if (args[2][0] == '+')
	{
		channel->set_invite_only(true);
		send_msg_mode(channel, "+i", client);
	}
	else
	{
		channel->set_invite_only(false);
		send_msg_mode(channel, "-i", client);
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
		send_msg_mode_with_param(channel, "+l", client, args[3]);
		channel->set_limit_mode(true);
	}
	else
	{
		channel->set_maxClient(SIZE_MAX - 1);
		send_msg_mode_with_param(channel, "-l", client, args[3]);
		channel->set_limit_mode(false);
	}
}

void topic_mode(std::vector<std::string> args, Channel* channel, Client* client)
{
	if (args[2][0] == '+')
	{
		channel->set_topicProtected(true);
		send_msg_mode(channel, "+t", client);
	}
	else
	{
		channel->set_topicProtected(false);
		send_msg_mode(channel, "-t", client);
	}
}

void key_mode(std::vector<std::string> args, Channel* channel, Client* client)
{
	if (args[2][0] == '+')
	{
		channel->set_pwd_protected(true);
		channel->set_pwd(args[3]);
		send_msg_mode_with_param(channel, "+k", client, args[3]);
	}
	else
	{
		channel->set_pwd_protected(false);
		send_msg_mode_with_param(channel, "-k", client, args[3]);
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
			send_msg_mode_with_param(channel, "+o", client, it->second->get_nickname());
		}
		else
		{
			channel->remove_client_from_operators(it->second);
			send_msg_mode_with_param(channel, "-o", client, it->second->get_nickname());
		}
	}
}

void Command::mode(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));

	std::map<std::string, Channel*> channels	 = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channels.find(args[1]);

	if (args.size() == 2 && it != channels.end())
		return (NumericReplies::RPL_CHANNELMODEIS(client, it->second, it->second->get_modes()));
	if (args.size() < 3)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
	if (it == channels.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
	if (!it->second->isOperator(client->get_fd()))
		return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[1]));
	if (args[2].compare(0, 2, "-i") == 0 || args[2].compare(0, 2, "+i") == 0)
		return (invite_mode(args, it->second, client));
	if (args[2].compare(0, 2, "-l") == 0 || args[2].compare(0, 2, "+l") == 0)
		return (limit_mode(args, client, it->second));
	if (args[2].compare(0, 2, "-t") == 0 || args[2].compare(0, 2, "+t") == 0)
		return (topic_mode(args, it->second, client));
	if (args[2].compare(0, 2, "-k") == 0 || args[2].compare(0, 2, "+k") == 0)
		return (key_mode(args, it->second, client));
	if (args[2].compare(0, 2, "-o") == 0 || args[2].compare(0, 2, "+o") == 0)
		return (operator_mode(args, client, it->second));
	return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
}
