#include "Client.hpp"
#include "Defenitions.hpp"


Client::Client()
{
	buf_ = new char[BUFLEN + 1];
	
}

Client::~Client()
{
	delete[] buf_;
}


void Client::setPort(int port)
{
	port_ = port;
}

void Client::run()
{
	create();
	echo();
}

