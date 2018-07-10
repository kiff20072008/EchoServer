#include "Client.hpp"
#include <exception>
#include <iostream>
#include<string>
#include <algorithm>

int main(void) {
	
	Client *client;
	std::string str;
	std::cout << "Pls choose TCP or UDP" << std::endl;
	std::cin >> str;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	while (true)
	{
		if (str == "TCP")
		{
			client = new Client(whatCon::TCP_);
			break;
		}
		else if (str == "UDP")
		{
			client = new Client(whatCon::UDP_);
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
		if (str == "TCP")
		{
			int option;
			int port=3000;
			std::string ip="127.0.0.1";
			std::cout << "Input port" << std::endl;
			std::cin >> port;
			std::cout << "Input ip" << std::endl;
			std::cin >> ip;
			client->setDataTCP(ip, port);
			client->run();
		}
		else
		{
			int option;
			int port = 3000;
			std::string host = "localhost";
			std::cout << "Input port" << std::endl;
			std::cin >> port;
			std::cout << "Input host" << std::endl;
			std::cin >> host;
			client->setDataUDP(host, port);
			client->run();
		}
	}
	catch (std::exception *ex)
	{
		std::cout << ex->what() << std::endl;
	}
	return 0;
}