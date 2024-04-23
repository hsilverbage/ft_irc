#include "Command.hpp"

void	Command::privmsg(std::vector<std::string> args, Client* Client)
{
	std::cout << "PRIVMSG" << args[0] << Client->get_fd() << std::endl;
}
