#include "Command.hpp"

void	Command::pass(std::vector<std::string> args, Client* Client)
{
	std::cout << "PASS" <<  args[0] << Client->get_nickname() << std::endl;
}
