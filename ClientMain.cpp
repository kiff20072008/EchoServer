#include "Client.hpp"
#include "TCPClient.hpp"
#include "UDPClient.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <algorithm>

int main(void) {
	
	Client *client;
	std::string str;

	std::cout << "Pls choose 'TCP' or 'UDP':" << std::endl;
	std::cin >> str;
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	while (true)
	{
		if (str == "TCP")
		{
			client = new TCPClient();
			break;
		}
		else if (str == "UDP")
		{
			client = new UDPClient;
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
		client->setPort(port);
		if (str == "TCP")
		{
			std::string ip="127.0.0.1";
			std::cout << "Input ip" << std::endl;
			std::cin >> ip;
			client->setData(ip);
		}
		else
		{
			std::string host = "localhost";
			std::cout << "Input host" << std::endl;
			std::cin >> host;
			client->setData(host);
		}
		client->run();
	}
	catch (std::exception *ex)
	{
		std::cout << ex->what() << std::endl;
	}
	return 0;
}