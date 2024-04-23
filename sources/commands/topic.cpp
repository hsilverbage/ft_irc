#include "Command.hpp"

void	Command::topic(std::vector<std::string> args, Client* Client)
{
	std::cout << "TOPIC" << args[0] << Client->get_nickname() << std::endl;
}
