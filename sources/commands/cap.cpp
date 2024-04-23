#include "Command.hpp"

void	Command::cap(std::vector<std::string> args, Client* Client)
{
	std::cout << "CAP CMD\t" << args[0] << Client->get_nickname() << std::endl;
}
