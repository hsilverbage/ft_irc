#include "Command.hpp"

void	Command::join(std::vector<std::string> args, Client* Client)
{
	std::cout << "JOIN" << args[0] << Client->get_fd() << std::endl;
}
