#include "Command.hpp"

void	Command::quit(std::vector<std::string> args, Client* Client)
{
	std::cout << "QUIT" << args[0] << Client->get_fd() << std::endl;
}
