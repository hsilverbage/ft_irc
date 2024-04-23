#include "Command.hpp"

void	Command::nick(std::vector<std::string> args, Client* Client)
{
	std::cout << "NICK" << args[0] << Client->get_nickname() << std::endl;
}
