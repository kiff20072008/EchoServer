#include "TCPServer.hpp"
#include "Defenitions.hpp"

TCPServer::TCPServer() :Server()
{
	std::cout << getServerType() << " server created" << std::endl;
}

TCPServer::~TCPServer()
{
	shutdown(client_, SHUT_RDWR);
	close(client_);
}

void TCPServer::create()
{
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));

	server_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server_ == -1)
	{
		throw new std::logic_error("Error socket creation");
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port_);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(server_, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
	{
		close(server_);
		throw new std::logic_error("Connect error");
	}

	if (listen(server_, 10) == -1)
	{
		close(server_);
		throw new std::logic_error("Listen error");
	}
}

std::string TCPServer::getServerType()
{
	return std::string("TCP");
}

bool TCPServer::getAccept()
{
	return ((client_ = accept(server_, 0, 0))>=0);
}

int TCPServer::readStr()
{
	return read(client_, buf_, BUFLEN);
}

int TCPServer::sendStr()
{
	return write(client_, buf_, rcount_);
}
