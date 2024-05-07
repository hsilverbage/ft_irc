#include "Command.hpp"

void Command::invite(std::vector<std::string> args, Client* client)
{
	std::cout << "INVITE CMD\t" << args[0] << client->get_nickname() << std::endl;
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "INVITE"));

	std::map<std::string, Channel*> channel = _Serv->get_channel();
	std::map<std::string, Channel*>::iterator it = channel.find(args[2]);
	if (it == channel.end())
		return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[2]));
	
	std::map<int, Client*> client_map = _Serv->get_clients_map();
	std::map<int, Client*>::iterator iter;
	for (iter = client_map.begin(); iter != client_map.end(); ++iter) 
	{
		if (iter->second->get_nickname() == args[1])
		{
			if (it->second->is_client_in_channel(iter->first))
				return (NumericReplies::ERR_USERONCHANNEL(client, args[2]));
			else if (it->second->get_invite_only() && !channel[args[2]]->isOperator(client->get_fd()))
				return (NumericReplies::ERR_CHANOPRIVSNEEDED(client, args[2]));
			else if (it->second->is_banned(args[1]))
			{
				it->second->unban_client(iter->second);
				NumericReplies::RPL_INVITING(client, args[2]);
			}
			else
				NumericReplies::RPL_INVITING(client, args[2]);
		}
		// MAYBE AN ERROR WHEN THE NICK DON'T MATCH WITH THE CLIENT_MAP
	}
}

/*
INVITE message

	 Command: INVITE
  Parameters: <nickname> <channel>

The INVITE command is used to invite a user to a channel. The parameter <nickname> is the nickname of the person to be
invited to the target channel <channel>.

The target channel SHOULD exist (at least one user is on it). Otherwise, the server SHOULD reject the command with the
ERR_NOSUCHCHANNEL numeric.

Only members of the channel are allowed to invite other users. Otherwise, the server MUST reject the command with the
ERR_NOTONCHANNEL numeric.

Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric. In particular, they SHOULD reject it when the
channel has invite-only mode set, and the user is not a channel operator.

If the user is already on the target channel, the server MUST reject the command with the ERR_USERONCHANNEL numeric.

When the invite is successful, the server MUST send a RPL_INVITING numeric to the command issuer, and an INVITE message,
with the issuer as <source>, to the target user. Other channel members SHOULD NOT be notified.

Numeric Replies:

	RPL_INVITING (341) OK
	ERR_NEEDMOREPARAMS (461) OK
	ERR_NOSUCHCHANNEL (403) OK
	ERR_NOTONCHANNEL (442) OK
	ERR_CHANOPRIVSNEEDED (482) OK
	ERR_USERONCHANNEL (443) OK

Command Examples:

  INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

Message Examples:

  :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
										to the channel #test
*/
