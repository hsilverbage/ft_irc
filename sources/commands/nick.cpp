#include "Command.hpp"

void	Command::nick(std::vector<std::string> args, Client* Client)
{
	(void) Client;
	std::cout << "NICK" << args[0] << std::endl;
}
