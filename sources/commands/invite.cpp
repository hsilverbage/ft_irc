#include "Command.hpp"

void	Command::invite(std::vector<std::string> args, Client* Client)
{
	std::cout << "INVITE" << args[0] << Client->get_fd() << std::endl;
}
