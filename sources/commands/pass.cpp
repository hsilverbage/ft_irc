#include "Command.hpp"

void	Command::pass(std::vector<std::string> args, Client* Client)
{
	(void) Client;
	std::cout << "PASS" <<  args[0] << std::endl;
}
