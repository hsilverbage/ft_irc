#include "Command.hpp"

void Command::pass(std::vector<std::string> args, Client* client)
{
	if (client->get_nickname() != "" || client->get_username() != "")
		return;
	if (args.size() < 2)
	{
		NumericReplies::ERR_NEEDMOREPARAMS(client, "PASS");
		client->set_isConnected(false);
		return;
	}
	std::string pass = args[1];
	if (args.size() > 2)
	{
		for (size_t i = 2; i < args.size(); i++)
		{
			pass += ' ';
			pass += args[i];
		}
	}
	if (pass != this->_Serv->get_pwd())
	{
		NumericReplies::ERR_PASSWDMISMATCH(client);
		client->set_isConnected(false);
		return;
	}
	std::cout << "setting is connected to true" << std::endl;
	client->set_isConnected(true);
}

/*
PASS message

	 Command: PASS
  Parameters: <password>

The PASS command is used to set a ‘connection password’. If set, the password must be set before any attempt to register
the connection is made. This requires that clients send a PASS command before sending the NICK / USER combination.

The password supplied must match the one defined in the server configuration. It is possible to send multiple PASS
commands before registering but only the last one sent is used for verification and it may not be changed once the
client has been registered.

If the password supplied does not match the password expected by the server, then the server SHOULD send
ERR_PASSWDMISMATCH (464) and MAY then close the connection with ERROR. Servers MUST send at least one of these two
messages.

Servers may also consider requiring SASL authentication upon connection as an alternative to this, when more information
or an alternate form of identity verification is desired.

Numeric replies:

	ERR_NEEDMOREPARAMS (461)
	ERR_ALREADYREGISTERED (462)
	ERR_PASSWDMISMATCH (464)

Command Example:

  PASS secretpasswordhere

*/
