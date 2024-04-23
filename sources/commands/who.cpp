#include "Command.hpp"

void	Command::who(std::vector<std::string> args, Client* Client)
{
	std::cout << "WHO" << args[0] << Client->get_fd() << std::endl;
}
