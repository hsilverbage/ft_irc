#ifndef COMMAND_HPP
#define COMMAND_HPP

#define MAXCHANNEL 10
#define MAXCLIENT 10

#include "Server.hpp"

class Server;
class Client;
class Channel;

class Command
{
	public:

		Command();
		Command(Server* Serv);
		~Command();

		void parse_cmd(std::string buff, int fd);
		void exec_cmd(std::vector<std::string> args, int fd);

	private:

		typedef void (Command::*find_cmd_function)(std::vector<std::string>, Client *);
		std::map<std::string, find_cmd_function> _commands;

		Server*	_Serv;

		void	pass(std::vector<std::string> args, Client* client);
		void	join(std::vector<std::string> args, Client* client);
		void	part(std::vector<std::string> args, Client* client);
		void	quit(std::vector<std::string> args, Client* client);
		void	nick(std::vector<std::string> args, Client* client);
		void	kick(std::vector<std::string> args, Client* client);
		void	mode(std::vector<std::string> args, Client* client);
		void	who(std::vector<std::string> args, Client* client);
		void	invite(std::vector<std::string> args, Client* client);
		void	topic(std::vector<std::string> args, Client* client);
		void	user(std::vector<std::string> args, Client* client);
		void	privmsg(std::vector<std::string> args, Client* client);
		void	ban(std::vector<std::string> args, Client* client);
		void	unban(std::vector<std::string> args, Client* client);
};

#endif
