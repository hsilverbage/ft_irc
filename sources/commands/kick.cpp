#include "Command.hpp"

void	Command::kick(std::vector<std::string> args, Client* Client)
{
	std::cout << "KICK" << args[0] << Client->get_nickname() << std::endl;
}
