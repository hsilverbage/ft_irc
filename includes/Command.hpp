#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"

class Server;
class Client;

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

		void pass(std::vector<std::string> args, Client* Client);
		void join(std::vector<std::string> args, Client* Client);
		void part(std::vector<std::string> args, Client* Client);
		void quit(std::vector<std::string> args, Client* Client);
		void nick(std::vector<std::string> args, Client* Client);
		void kick(std::vector<std::string> args, Client* Client);
		void mode(std::vector<std::string> args, Client* Client);
		void who(std::vector<std::string> args, Client* Client);
		void invite(std::vector<std::string> args, Client* Client);
		void topic(std::vector<std::string> args, Client* Client);
		void user(std::vector<std::string> args, Client* Client);
		void privmsg(std::vector<std::string> args, Client* Client);
};

#endif
