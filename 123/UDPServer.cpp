#include "UDPServer.hpp"
#include "Defenitions.hpp"

UDPServer::UDPServer():Server()
{
	std::cout <<getServerType() << " server created" << std::endl;
}

UDPServer::~UDPServer()
{
	close(server_);
}

void UDPServer::create()
{
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_ = socket(PF_INET, SOCK_STREAM, 0);
	if (!server_) 
	{
		throw new std::logic_error("Socket getting error");
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	int reuse = 1;

	if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		throw new std::logic_error("Setsockopt error");
	}

	if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		throw new std::logic_error("Bind error");
	}
	if (listen(server_, SOMAXCONN) < 0) {
		throw new std::logic_error("Listen error");
	}
}

std::string UDPServer::getServerType()
{
	return std::string("UDP");
}

bool UDPServer::getAccept()
{
	struct sockaddr_in client_addr;
	socklen_t clientlen = sizeof(client_addr);
	return ((client_ = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0);
}

int UDPServer::readStr()
{
	return rcount = recv(client_, buf_, 64, 0);
}

//todo to rcount 
int UDPServer::sendStr()
{
	return send(client_, buf_, 64, 0);
}
