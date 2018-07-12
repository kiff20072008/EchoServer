#include "Server.hpp"

#include"NumbersParser.hpp"
#include "Defenitions.hpp"

//todo delete
#include <cctype>

Server::Server()
{
	buf_ = new char[BUFLEN + 1];
	
	parser_ = new NumbersParser();
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

void Server::create()
{
}

void Server::serve()
{
	while (getAccept())
	{
		handle();
	}
}

void Server::handle()
{
	while (1)
	{
		std::cout <<"!1" <<std::endl;
		if (rcount = readStr() < 0)
		{
			continue;
		}
		if (rcount == 0)
		{
			continue;
		}
		sendNumToParser(rcount);
		if ((sendStr()) !=rcount)
		{
			std::cout << "Error send data length != read data length " << std::endl;
		}
		if (rcount == 0)
		{
			continue;
		}
	}
}


void Server::printNumbers()
{
	std::cout << parser_->getAllNum() << std::endl;
}



void Server::sendNumToParser(unsigned int size)
{
	std::cout << "Reading message\n";
	for (ssize_t i = 0; i < size; ++i)
	{
		std::cout << buf_[i];
	}
	std::cout << std::endl;

	for (ssize_t i = 0; i < size; ++i)
	{
		if (isdigit(buf_[i]))
		{
			parser_->getNumber(buf_[i] - '0');
		}
	}
	printNumbers();
}

std::string Server::getServerType()
{
	return std::string("NONE");
}

bool Server::getAccept()
{
	return false;
}

int Server::readStr()
{
	return 0;
}

int Server::sendStr()
{
	return 0;
}
