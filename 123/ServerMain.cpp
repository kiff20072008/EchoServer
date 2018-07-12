#include "Server.hpp"
#include "TCPServer.hpp"
#include "UDPServer.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

int main(void) 
{
	Server *server;
	std::string str;

	std::cout << "Pls choose 'TCP' or 'UDP':" << std::endl;
	std::cin >> str;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	while (true)
	{
		if (str == "TCP")
		{
			server = new TCPServer();
			break;
		}
		else if (str == "UDP")
		{
			server = new UDPServer();
			break;
		}
		else
		{
			str.erase();
			std::cout << "Pls choose 'TCP' or 'UDP':" << std::endl;
			std::cin >> str;
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		}
	}
	try
	{
		int option;
		int port = 3000;
		std::cout << "Input port" << std::endl;
		std::cin >> port;
		server->setPort(port);
		server->run();
	}
	catch (std::exception *ex)
	{
		std::cout << ex->what() << std::endl;
		return 1;
	}
	return 0;
}