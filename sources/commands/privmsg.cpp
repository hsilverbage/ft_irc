#include "Command.hpp"

void Command::privmsg(std::vector<std::string> args, Client* client)
{
	std::cout << "PRIVMSG CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 3)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "PRIVMSG"));

	size_t i = 0;

	std::string message;
	std::vector<std::string> target_vec;
	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator ite =	channel.begin();
	std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator it = client_map.begin();

	if (args[1][0] && (args[1][0] == '@' || args[1][0] == '#' || args[1][0] == '%'))
	{
		while (args[i + 1][0] && args[i + 1][0] != ':')
		{
			if (ite->second->is_channel(channel, args[i + 1]))
				target_vec.push_back(args[i + 1]);
			else
				return (NumericReplies::ERR_NOSUCHNICK(client, args[i + 1]));
			i++;
		}
		if (args[i + 1][0] && args[i + 1][0] == ':')
		{
			i++;
			message = client->get_nickname() + " :";
			while (i + 1 < args.size())
			{
				message += args[i + 1];
				if (i != args.size())
					message.push_back(' ');
				message.push_back('\0');
				i++;
			}
		}
		else
			return (NumericReplies::ERR_NORECIPIENT(client, "PRIVMSG"));
		i = 0;
		for (ite = channel.begin(); ite != channel.end(); ite++)
		{
			if (ite->first == target_vec[i] && ite->second->is_client_in_channel(client->get_fd()))
				ite->second->send_msg_to_everyone_in_channel(message);
			else if (ite->first == target_vec[i] && !ite->second->is_client_in_channel(client->get_fd()))
				return (NumericReplies::ERR_CANNOTSENDTOCHAN(client, target_vec[i]));
			i++;
		}
	}
	else
	{
		while (args[i + 1][0] && args[i + 1][0] != ':')
		{
			if (client->is_client(client_map, args[i + 1]))
				target_vec.push_back(args[i + 1]);
			else
				return (NumericReplies::ERR_NOSUCHNICK(client, args[i + 1]));
			i++;
		}
		if (args[i + 1][0] && args[i + 1][0] == ':')
		{
			i++;
			message = client->get_nickname() + " :";
			while (i + 1 < args.size())
			{
				if (i != args.size())
					message.push_back(' ');
				message.push_back('\0');
				i++;
			}
		}
		else
			return (NumericReplies::ERR_NORECIPIENT(client, "PRIVMSG"));
		i = 0;
		for (it = client_map.begin(); it != client_map.end(); it++)
		{
			if (it->second->get_nickname() == target_vec[i])
			{
				ite->second->send_msg_to_someone(it->second->get_fd(), message);
				i++;
			}
			else if (it == client_map.end())
				return (NumericReplies::ERR_NOSUCHNICK(client, target_vec[i]));
		}
	}
		
}

	// 	if (it != channel.end())
	// 		return (it->second->send_msg_to_everyone_in_channel(args[2]));
	// 	else
	// 		return (NumericReplies::ERR_NOSUCHNICK(client, args[1]));

	
	// 	for (iter = client_map.begin(); iter != client_map.end(); ++iter) 
	// 	{
	// 		if (iter->second->get_nickname() == args[1])
	// 			return (it->second->send_msg_to_someone(iter->first, args[2]));
	// 		if (iter == client_map.end())
	// 			return (NumericReplies::ERR_NOSUCHNICK(client, args[1]));
	// 	}

	// }
	
	


/*
Sending Messages
PRIVMSG message

	 Command: PRIVMSG
  Parameters: <target>{,<target>} <text to be sent>

The PRIVMSG command is used to send private messages between users, as well as to send messages to channels. <target> is
the nickname of a client or the name of a channel.

If <target> is a channel name and the client is banned and not covered by a ban exception, the message will not be
delivered and the command will silently fail. Channels with the moderated mode active may block messages from certain
users. Other channel modes may affect the delivery of the message or cause the message to be modified before delivery,
and these modes are defined by the server software and configuration being used.

If a message cannot be delivered to a channel, the server SHOULD respond with an ERR_CANNOTSENDTOCHAN (404) numeric to
let the user know that this message could not be delivered.

If <target> is a channel name, it may be prefixed with one or more channel membership prefix character (@, +, etc) and
the message will be delivered only to the members of that channel with the given or higher status in the channel.
Servers that support this feature will list the prefixes which this is supported for in the STATUSMSG RPL_ISUPPORT
parameter, and this SHOULD NOT be attempted by clients unless the prefix has been advertised in this token.

If <target> is a user and that user has been set as away, the server may reply with an RPL_AWAY (301) numeric and the
command will continue.

The PRIVMSG message is sent from the server to client to deliver a message to that client. The <source> of the message
represents the user or server that sent the message, and the <target> represents the target of that PRIVMSG (which may
be the client, a channel, etc).

When the PRIVMSG message is sent from a server to a client and <target> starts with a dollar character ('$', 0x24), the
message is a broadcast sent to all clients on one or multiple servers.

Numeric Replies:

	ERR_NOSUCHNICK (401)
	ERR_NOSUCHSERVER (402)
	ERR_CANNOTSENDTOCHAN (404)
	ERR_TOOMANYTARGETS (407)
	ERR_NORECIPIENT (411)
	ERR_NOTEXTTOSEND (412)
	ERR_NOTOPLEVEL (413)
	ERR_WILDTOPLEVEL (414)
	RPL_AWAY (301)

There are strange "X@Y" target rules and such which are noted in the examples of the original PRIVMSG RFC section. We
need to check to make sure modern servers actually process them properly, and if so then specify them.

Command Examples:

  PRIVMSG Angel :yes I'm receiving it !
								  ; Command to send a message to Angel.

  PRIVMSG %#bunny :Hi! I have a problem!
								  ; Command to send a message to halfops
								  and chanops on #bunny.

  PRIVMSG @%#bunny :Hi! I have a problem!
								  ; Command to send a message to halfops
								  and chanops on #bunny. This command is
								  functionally identical to the above
								  command.

Message Examples:

  :Angel PRIVMSG Wiz :Hello are you receiving this message ?
								  ; Message from Angel to Wiz.

  :dan!~h@localhost PRIVMSG #coolpeople :Hi everyone!
								  ; Message from dan to the channel
								  #coolpeople
*/
