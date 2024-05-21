#include "Command.hpp"

void Command::pass(std::vector<std::string> args, Client* client)
{
	if (client->get_nickname() != "" || client->get_username() != "" || client->get_isConnected())
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
		client->set_pwdIsCorrect(false);
		return;
	}
	client->set_pwdIsCorrect(true);
	if (client->get_pwdIsCorrect() && client->get_nickname() != "" && client->get_username() != "" && client->get_isConnected() == false)
	{
		NumericReplies::RPL_WELCOME(client);
		client->set_isConnected(true);
	}
}

