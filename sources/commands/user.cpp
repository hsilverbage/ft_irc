#include "Command.hpp"

void	Command::user(std::vector<std::string> args, Client* Client)
{
	std::cout << "USER" << args[0] << Client->get_nickname() << std::endl;
}
