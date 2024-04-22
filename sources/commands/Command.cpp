#include "Command.hpp"

Command::Command()
{
}

Command::Command(Server* Serv) : _Serv(Serv)
{
	_commands["PASS"] = &Command::pass;
	_commands["JOIN"] = &Command::join;
	_commands["PART"] = &Command::part;
	_commands["QUIT"] = &Command::quit;
	_commands["NICK"] = &Command::nick;
	_commands["KICK"] = &Command::kick;
	_commands["MODE"] = &Command::mode;
	_commands["WHO"] = &Command::who;
	_commands["INVITE"] = &Command::invite;
	_commands["TOPIC"] = &Command::topic;
	_commands["USER"] = &Command::user;
	_commands["PRIVMSG"] = &Command::privmsg;
}

Command::~Command() {}

void	Command::exec_cmd(std::vector<std::string> args, int fd)
{
	std::map<std::string, find_cmd_function>::iterator it = _commands.find(args[0]);

	if (it != _commands.end())
		*(it->second)(args, client);
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
