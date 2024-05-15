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

void	limit_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{
		channel->set_maxClient()
	}
	else
	{
		
	}
}

void	topic_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{

	}
	else
	{
		
	}
}

void	key_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args[2][0] == '+')
	{

	}
	else
	{
		
	}
}

void	operator_mode(std::vector<std::string> args, Client* client, Channel* channel)
{
	if (args.size() < 4)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "MODE"));
	if (args[2][0] == '+')
	{

	}
	else
	{
		
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
		invite_mode(args, client, it->second);
	if (args[2][1] == 'l')
		limit_mode(args, client, it->second);
	if (args[2][1] == 't')
		topic_mode(args, client, it->second);
	if (args[2][1] == 'k')
		key_mode(args, client, it->second);
	if (args[2][1] == 'o')
		operator_mode(args, client, it->second);
	return (NumericReplies::ERR_UMODEUNKNOWNFLAG(client));
}

