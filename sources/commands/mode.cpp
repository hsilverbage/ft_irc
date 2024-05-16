#include "Command.hpp"

void	invite_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_invite_only(true);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode invite only is actived by " + client->get_nickname());
	}
	else
	{
		channel->set_invite_only(false);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode invite only is desactivated by " + client->get_nickname());
	}
}

// void	limit_mode(std::vector<std::string> args, Client* client, Channel* channel)
// {
// 	// if (args[2][0] == '+')
// 	// {
// 	// 	if (args.size() < 4)
// 	// 		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
// 	// 	if (args[3].find_first_not_of("0123456789") != std::string::npos)
// 	// 		return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
// 	// 	// std::stringstream ss;
// 	// 	// size_t	max;

// 	// 	// ss << args[3];
// 	// 	// ss >> max;
// 	// 	// if (ss.fail())
// 	// 	// {
// 	// 	// 	std::cerr << "stringstream failed" << std::endl;
// 	// 	// 	return;
// 	// 	// }
// 	// 	// if (max > SIZE_MAX)
// 	// 	// 	return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
// 	// 	// channel->set_maxClient(std::atoi(args[3].c_str()));
// 	// }
// 	// else
// 	// 	channel->set_maxClient(SIZE_MAX);
// }

void	topic_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_topicProtected(true);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode topic protection is activated by " + client->get_nickname());
	}
	else
	{
		channel->set_topicProtected(false);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode topic protection is desactivated by " + client->get_nickname());
	}
}

void	key_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_pwd_protected(true);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode key protection is activated by " + client->get_nickname());
	}
	else
	{
		channel->set_pwd_protected(false);
		channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " channel mode key protection is desactivated by " + client->get_nickname());
	}
}

void	operator_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args.size() < 4)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
	if (!channel->is_nick_in_channel(args[3]))
		return (NumericReplies::ERR_NOSUCHNICK(client, args[3]));
	std::map<int, Client*> clients = channel->get_clients();
	std::map<int, Client*>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->get_nickname() == args[3])
			break;
	}
	if (it != clients.end())
	{
		if (args[2][0] == '+')
		{
			channel->add_client_to_operators(it->second);
			channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " " + args[3] + " is now operator thanks to " + client->get_nickname());
		}
		else
		{
			channel->remove_client_from_operators(it->second);
			channel->send_msg_to_everyone_in_channel(channel->get_channel_name() + " " + args[3] + " is now no longer operator because of " + client->get_nickname());
		}
	}
}

void Command::mode(std::vector<std::string> args, Client* client)
{
	std::cout << "MODE CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 3)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));

	std::map<std::string, Channel*> channels	 = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channels.find(args[1]);

	if (it != channels.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
	if (!it->second->isOperator(client->get_fd()))
		return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[1]));
	if (args[2][0] != '-' || args[2][0] != '+')
		return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
	if (args[2][1] == 'i')
		return (invite_mode(args, client, it->second));
	// if (args[2][1] == 'l')
	// 	return (limit_mode(args, client, it->second));
	if (args[2][1] == 't')
		return (topic_mode(args, client, it->second));
	if (args[2][1] == 'k')
		return (key_mode(args, client, it->second));
	if (args[2][1] == 'o')
		return (operator_mode(args, client, it->second));
	return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
}

