#include "Server.hpp"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Error : wrong number of arguments\nUsage : ./ircserv <port> <password>" << std::endl;
		return (-1);
	}
	try
	{
		Server Serv(argv[1], argv[2]);
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);

		Serv.ServInit();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (-1);
	}
	return (0);
}
