#include "Command.hpp"

void	Command::who(std::vector<std::string> args, Client* client)
{
	std::cout << "WHO CMD\t" << args[0] << client->get_nickname() << std::endl;
}
