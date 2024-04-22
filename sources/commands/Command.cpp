#include "Command.hpp"

Command::Command() {}

// Command::Command(Server* Serv) : _Server(Serv)
// {

// }

Command::~Command() {}

void	Command::exec_cmd(std::vector<std::string> args, int fd)
{
	std::cout << "from fd : " << fd << std::endl;
	for (size_t i = 0; i < args.size(); i++)
		std::cout << args[i] << std::endl;
}

void	Command::parse_cmd(std::string buff, int fd)
{
	// std::cout << buff << "from fd :" << fd << std::endl;

	std::string line;
	std::vector<std::string> args;

	for (size_t i = 0; i < buff.size(); i++)
	{
		if (buff[i] == '\n')
		{
			line = buff.substr(0, i);
			buff.erase(0, i + 1);

			for (size_t j = 0; j < line.size(); j++)
			{
				if (line[j] == ' ' || j == line.size() - 1)
				{
					args.push_back(line.substr(0, j));
					line = line.erase(0, j + 1);
					j	 = 0;
				}
			}
			if (args.size() > 0)
			{
				exec_cmd(args, fd);
			}
			line.clear();
			args.clear();
			i = 0;
		}
	}
}
