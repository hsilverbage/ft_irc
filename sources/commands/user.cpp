#include "Command.hpp"

void	Command::user(std::vector<std::string> args, Client* Client)
{
	(void) Client;
	std::cout << "USER" << args[0] << std::endl;
}
