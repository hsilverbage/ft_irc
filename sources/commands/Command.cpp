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
	_commands["INVITE"]	 = &Command::invite;
	_commands["TOPIC"]	 = &Command::topic;
	_commands["USER"]	 = &Command::user;
	_commands["PRIVMSG"] = &Command::privmsg;
	_commands["BAN"]	 = &Command::ban;
	_commands["UNBAN"]   = &Command::unban;
}

Command::~Command() {}

void Command::exec_cmd(std::vector<std::string> args, int fd)
{
	std::map<int, Client*>::iterator it;
	it = _Serv->get_clients_map().find(fd);
	if (it != _Serv->get_clients_map().end())
	{
		try
		{
			Client* client			 = it->second;
			find_cmd_function ft_ptr = _commands.at(args[0]);

			(this->*ft_ptr)(args, client);
		}
		catch (const std::out_of_range& e)
		{
			std::cout << "COMMAND NOT FUND" << args[0] << std::endl;
		}
	}
}

void Command::parse_cmd(std::string buff, int fd)
{
	std::string line = "";
	std::vector<std::string> args;

	for (size_t i = 0; i < buff.size(); i++)
	{
		if (buff[i] == '\n')
		{
			line = buff.substr(0, i + 1);
			buff.erase(0, i + 1);
			for (size_t j = 0; j < line.size(); j++)
			{
				if (line[j] == ' ' || line[j] == '\r' || line[j] == '\n' || j == line.size() - 1)
				{
					args.push_back(line.substr(0, j));
					line = line.erase(0, j + 1);
					j	 = 0;
				}
			}
			if (args.size() > 0)
				exec_cmd(args, fd);
			i = 0;
			line.clear();
			args.clear();
		}
		if (buff.empty())
			return;
	}
}
