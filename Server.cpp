#include "Server.hpp"

#include"NumbersParser.hpp"
#include "Defenitions.hpp"

//todo delete
#include <cctype>

Server::Server()
{
	buf_ = new char[BUFLEN + 1];
}

void Server::run()
{
	create();
	std::cout <<getServerType() << " server now listen" << std::endl;
	serve();
}

Server::~Server()
{
	delete[] buf_;
}

void Server::setPort(int port)
{
	port_ = port;
}

void Server::serve()
{
	for (;;)
	{
		if (getAccept())
		{
			handle();
		}
	}
}

void Server::handle()
{
	for (;;)
	{
		if ((rcount_ = readStr()) <= 0)
		{
			continue;
		}
		sendNumToParser();
		if ((sendStr()) !=rcount_)
		{
			std::cout << "Error send data length != read data length " << std::endl;
		}
	}
}

void Server::printNumbers()
{
	std::cout << parser_.getAllNum() << std::endl;
}

void Server::sendNumToParser()
{
	std::cout << "Reading message\n";
	for (ssize_t i = 0; i < rcount_; ++i)
	{
		std::cout << buf_[i];
		if (isdigit(buf_[i]))
		{
			parser_.getNumber(buf_[i] - '0');
		}
	}
	std::cout << std::endl;
	printNumbers();
}
