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
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	server.run(argv[1], argv[2]);
	return (0);
}
