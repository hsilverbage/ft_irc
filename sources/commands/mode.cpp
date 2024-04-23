#include "Command.hpp"

void	Command::mode(std::vector<std::string> args, Client* Client)
{
	std::cout << "MODE" << args[0] << Client->get_fd() << std::endl;
}
