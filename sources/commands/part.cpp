#include "Command.hpp"

void	Command::part(std::vector<std::string> args, Client* Client)
{
	std::cout << "PART" << args[0] << Client->get_nickname() << std::endl;
}
