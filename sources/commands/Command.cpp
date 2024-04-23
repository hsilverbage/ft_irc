#include "Command.hpp"

Command::Command() {}

Command::Command(Server* Serv) : _Serv(Serv)
{
	_commands["PASS"]	 = &Command::pass;
	_commands["JOIN"]	 = &Command::join;
	_commands["PART"]	 = &Command::part;
	_commands["QUIT"]	 = &Command::quit;
	_commands["NICK"]	 = &Command::nick;
	_commands["KICK"]	 = &Command::kick;
	_commands["MODE"]	 = &Command::mode;
	_commands["WHO"]	 = &Command::who;
	_commands["INVITE"]	 = &Command::invite;
	_commands["TOPIC"]	 = &Command::topic;
	_commands["USER"]	 = &Command::user;
	_commands["PRIVMSG"] = &Command::privmsg;
}

Command::~Command() {}

void Command::exec_cmd(std::vector<std::string> args, int fd)
{
	Client*	client = _Serv->find_client_with_fd(fd);
	
	try
	{
		find_cmd_function	ft_ptr = _commands.at(args[0]);
	
		(this->*ft_ptr)(args, client);
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
	for (size_t i = 0; i < args.size(); i++)
		std::cout << args[i] << fd << std::endl;	
	std::cout << std::endl;	
}

void Command::parse_cmd(std::string buff, int fd)
{
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
				exec_cmd(args, fd);
			line.clear();
			args.clear();
			i = 0;
		}
	}
}
