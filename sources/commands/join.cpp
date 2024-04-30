#include "Command.hpp"

void Command::join(std::vector<std::string> args, Client* client)
{
	if (client->get_isConnected() == false)
		return;
	if (args.size() < 2)
		return (NumericReplies::ERR_NEEDMOREPARAMS(client, "USER"));
	if (args[1][0] == '0')
	{
		std::map<std::string, Channel*> channel = _Serv->get_channel();
		for (std::map<std::string, Channel*>::iterator it = channel.begin(); it != channel.end(); it++)
		{
			it->second->remove_client_from_channel(client, "");
			//TODO SEND A MSG TO TELL EVERYONE THAT THE CLIENT LEFT THE CHHANEL AS IN PART PROBABLY GONNA PUT IN DIRECTLY IN THE FUNCTION ABOVE AS IN ASS IN add_client_to_channel()
		}
	}

	std::map<std::string, Channel*> channel_map = _Serv->get_channel();
	std::vector<std::string> argsChannel;
	std::vector<std::string> argsKey;


	for (size_t i = 1; i < args.size(); i++)
		if (args[i][0] == '&' || args[i][0] == '#')
			argsChannel.push_back(args[i]);
		else
			argsKey.push_back(args[i]);
	if (argsChannel.size() < argsKey.size())
		NumericReplies::ERR_BADCHANMASK(client, argsKey[0]);

	for (size_t i = 0; i < argsChannel.size(); i++)
	{
		std::map<std::string, Channel*>::iterator it = channel_map.find(argsChannel[i]);
		std::string	channelName = argsChannel[i];
		std::string	channelKey = "";

		if (i < argsKey.size())
			channelKey = argsKey[i];
		if (it != channel_map.end())  // SOULD WE CONTINU OR STOP AS SOON AS ONE CHANNEL FUCKS UP ?
		{
			std::map<int, Client*> banned = it->second->get_banned();
			std::map<int, Client*>::iterator ite;
    		for (ite = banned.begin(); ite != banned.end(); ++ite) 
			{
        		if (ite->second->get_nickname() == client->get_nickname())
			}	
			if (client->get_nb_channel() >= MAXCHANNEL)
				NumericReplies::ERR_TOOMANYCHANNELS(client, channelName);
			else if (it->second->get_nbClient() >= MAXCLIENT)
			{
				NumericReplies::ERR_CHANNELISFULL(client, channelName);
			}
			else if (it->second->get_key() != channelKey)
			{
				NumericReplies::ERR_BADCHANNELKEY(client, channelName);
			}
			else
			{
				
				it->second->add_client_to_channel(client);
				NumericReplies::RPL_NAMREPLY(client, it->second->get_clients(), channelName);
				NumericReplies::RPL_ENDOFNAMES(client, channelName);
				if (!it->second->get_topic().empty())
					NumericReplies::RPL_TOPIC(client);
				/*TODO : if joining the channel is successful :
						- all relevant information about that channel including the JOIN,PART, KICK, and MODE messages affecting the channel
						- They receive all PRIVMSG and NOTICE messages sent to the channel
						- receive QUIT messages from other clients joined to the same channel
						- A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
				*/
			}
		}
		else
		{
			Channel* channel = new Channel(channelKey, client, channelName);

			channel->add_client_to_channel(client);
			_Serv->add_channel_to_map(channel, argsChannel[i]);
			
			// return (NumericReplies::ERR_NOSUCHCHANNEL(client, args[1]));
		}
	}
}

/*
JOIN message

	 Command: JOIN
  Parameters: <channel>{,<channel>} [<key>{,<key>}]
  Alt Params: 0

The JOIN command indicates that the client wants to join the given channel(s), each channel using the given key for it.
The server receiving the command checks whether or not the client can join the given channel, and processes the request.
Servers MUST process the parameters of this command as lists on incoming commands from clients, with the first <key>
being used for the first <channel>, the second <key> being used for the second <channel>, etc.

While a client is joined to a channel, they receive all relevant information about that channel including the JOIN,
PART, KICK, and MODE messages affecting the channel. They receive all PRIVMSG and NOTICE messages sent to the channel,
and they also receive QUIT messages from other clients joined to the same channel (to let them know those users have
left the channel and the network). This allows them to keep track of other channel members and channel modes.

If a client’s JOIN command to the server is successful, the server MUST send, in this order:

	A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of
the message. The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME (333)), and no message if the
channel does not have a topic. A list of users currently joined to the channel (with one or more RPL_NAMREPLY (353)
numerics followed by a single RPL_ENDOFNAMES (366) numeric). These RPL_NAMREPLY messages sent by the server MUST include
the requesting client that has just joined the channel.

The key, client limit , ban - exception, invite-only - exception, and other (depending on server software) channel modes
affect whether or not a given client may join a channel. More information on each of these modes and how they affect the
JOIN command is available in their respective sections.

Servers MAY restrict the number of channels a client may be joined to at one time. This limit SHOULD be defined in the
CHANLIMIT RPL_ISUPPORT parameter. If the client cannot join this channel because they would be over their limit, they
will receive an ERR_TOOMANYCHANNELS (405) reply and the command will fail.

Note that this command also accepts the special argument of ("0", 0x30) instead of any of the usual parameters, which
requests that the sending client leave all channels they are currently connected to. The server will process this
command as though the client had sent a PART command for each channel they are a member of.

This message may be sent from a server to a client to notify the client that someone has joined a channel. In this case,
the message <source> will be the client who is joining, and <channel> will be the channel which that client has joined.
Servers SHOULD NOT send multiple channels in this message to clients, and SHOULD distribute these multiple-channel JOIN
messages as a series of messages with a single channel name on each.

Numeric Replies:

	ERR_NEEDMOREPARAMS (461) ok
	ERR_NOSUCHCHANNEL (403) ok
	ERR_TOOMANYCHANNELS (405) ok
	ERR_BADCHANNELKEY (475) ok
	ERR_BANNEDFROMCHAN (474)
	ERR_CHANNELISFULL (471) ok
	ERR_INVITEONLYCHAN (473) MAYBE TO DO IT DEPEND OF INVITE OPTIONS
	ERR_BADCHANMASK (476) ok
	RPL_TOPIC (332) OK
	RPL_TOPICWHOTIME (333)
	RPL_NAMREPLY (353) OK
	RPL_ENDOFNAMES (366) OK

Command Examples:

  JOIN #foobar                    ; join channel #foobar.

  JOIN &foo fubar                 ; join channel &foo using key "fubar".

  JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
								  and &bar using no key.

  JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
								  and channel #bar using key "foobar".

  JOIN #foo,#bar                  ; join channels #foo and #bar.

Message Examples:

  :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel
								  #Twilight_zone

  :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test

See also:

	IRCv3 extended-join Extension
*/
