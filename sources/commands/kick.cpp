#include "Command.hpp"

void	Command::kick(std::vector<std::string> args, Client* client)
{
	std::cout << "KICK CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
    if (args.size() < 3)
        return (NumericReplies::ERR_NEEDMOREPARAMS(client, "KICK"));

    std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.find(args[1]);

	if (it == channel.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
    if (!it->second->is_client_in_channel(client->get_fd()))
        return (NumericReplies::ERR_NOTONCHANNEL(client, client->get_nickname()));
    if (!it->second->isOperator(client->get_fd()))
        return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, it->second->get_channel_name()));

    std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator iter;
	for (iter = client_map.begin(); iter != client_map.end(); iter++) 
	{
        std::cout << "debug 1 " << std::endl;
        if (it->second->is_nick_in_channel(args[2]) && iter->first != client->get_fd())
        {
            std::cout << "debug 2 " << std::endl;
            it->second->remove_client_from_channel(iter->second, args[4]);
            return ;
        }
    }
    if (iter == client_map.end())
    {
        std::cout << "debug 3 " << std::endl;
	    return (NumericReplies::ERR_USERNOTINCHANNEL(client, args[2], args[1]));
    }
}

/*
KICK message

      Command: KICK
   Parameters: <channel> <user> *( "," <user> ) [<comment>]

The KICK command can be used to request the forced removal of a user from a channel. It causes the <user> to be removed from the <channel> by force.

This message may be sent from a server to a client to notify the client that someone has been removed from a channel. In this case, the message <source> will be the client who sent the kick, and <channel> will be the channel which the target client has been removed from.

If no comment is given, the server SHOULD use a default message instead.

Servers MUST NOT send multiple users in this message to clients, and MUST distribute these multiple-user KICK messages as a series of messages with a single user name on each. This is necessary to maintain backward compatibility with existing client software. If a KICK message is distributed in this way, <comment> (if it exists) should be on each of these messages.

Servers MAY limit the number of target users per KICK command via the TARGMAX parameter of RPL_ISUPPORT, and silently drop targets if the number of targets exceeds the limit.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461) Ok
    ERR_NOSUCHCHANNEL (403) OK
    ERR_CHANOPRIVSNEEDED (482) OK
    ERR_USERNOTINCHANNEL (441) OK
    ERR_NOTONCHANNEL (442) OK

Deprecated Numeric Reply:

    ERR_BADCHANMASK (476)

Examples:

   KICK #Finnish Matthew           ; Command to kick Matthew from
                                   #Finnish

   KICK &Melbourne Matthew         ; Command to kick Matthew from
                                   &Melbourne

   KICK #Finnish John :Speaking English
                                   ; Command to kick John from #Finnish
                                   using "Speaking English" as the
                                   reason (comment).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; KICK message on channel #Finnish
                                   from WiZ to remove John from channel
*/

