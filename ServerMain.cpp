#include "Server.hpp"

#include <iostream>
#include<string>
#include <algorithm>

int main(void) 
{
	Server *server;
	std::string str;
	std::cout << "Pls choose TCP or UDP" << std::endl;
	std::cin >> str;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	while (true)
	{
		if (str == "TCP")
		{
			std::cout << "TCP SERVER Create" << std::endl;
			server = new Server(whatCon::TCP_);
			break;
		}
		else if (str == "UDP")
		{
			std::cout << "UDP SERVER Create" << std::endl;
			server = new Server(whatCon::UDP_);
			break;
		}
		else
		{
			str.erase();
			std::cout << "Pls choose TCP or UDP" << std::endl;
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
		if (str == "TCP")
		{
			std::cout << "TCP SERVER Start" << std::endl;
		}
		else
		{
			std::cout << "UDP SERVER Start" << std::endl;
		}
		server->setPort(port);
		server->run();
	}
	catch (std::exception *ex)
	{
		std::cout << ex->what() << std::endl;
	}
	return 0;
}