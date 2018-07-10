#include "Server.hpp"
#include"NumbersParser.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <errno.h>
#define BUFLEN 64

Server::Server(whatCon con):con_(con)
{
	buflen_ = BUFLEN;
	buf_ = new char[BUFLEN + 1];
}
void Server::run()
{
	create();
	serve();
}

Server::~Server()
{
	close_socket();
}

void Server::setPort(int port)
{
	port_ = port;
}

void Server::create()
{
	parser_ = new NumbersParser();

	if (con_ == TCP_)
	{
		i32SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (i32SocketFD == -1)
		{
			throw new std::logic_error("Error socket creation");
		}

		stSockAddr = new sockaddr_in();
		memset(stSockAddr, 0, sizeof(*stSockAddr));

		stSockAddr->sin_family = PF_INET;

		stSockAddr->sin_port = htons(port_);
		stSockAddr->sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(i32SocketFD, (struct sockaddr*) stSockAddr, sizeof(*stSockAddr)) == -1)
		{
			close(i32SocketFD);
			throw new std::logic_error("Connect error");
		}
		if (listen(i32SocketFD, 10) == -1)
		{
			close(i32SocketFD);
			throw new std::logic_error("Listen error");
		}
		ssize_t i;
		ssize_t rcount;
		std::cout << "TCP server now listen" << std::endl;
	}
	else
	{
		struct sockaddr_in server_addr;
		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port_);
		server_addr.sin_addr.s_addr = INADDR_ANY;

		server_ = socket(PF_INET, SOCK_STREAM, 0);
		if (!server_) {
			throw new std::logic_error("socket");
		}

		int reuse = 1;
		if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
			throw new std::logic_error("setsockopt");
		}

		if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
			throw new std::logic_error("bind");
		}
		if (listen(server_, SOMAXCONN) < 0) {
			throw new std::logic_error("listen");
		}
		std::cout << "UDP server now listen" << std::endl;
	}
}

void Server::close_socket()
{
	if (con_ == TCP_)
	{
		shutdown(i32ConnectFD, SHUT_RDWR);
		close(i32ConnectFD);
	}
	else
	{
		close(server_);
	}
}

void Server::serve()
{
	int rcount;
	if (con_ == TCP_)
	{
		for (;;)
		{
			i32ConnectFD = accept(i32SocketFD, 0, 0);
			if (i32ConnectFD < 0) 
			{
				close(i32SocketFD);
				throw new std::logic_error("Accept error");
			}
			for (;;)
			{
				if ((rcount = read(i32ConnectFD, buf_, BUFLEN)) == -1)
				{
					continue;
				}
					std::cout << "Reading message\n" ;
					std::cout << buf_ << std::endl;
					
					for (ssize_t i = 0; i < rcount; ++i)
					{
						if (isdigit(buf_[i]))
						{
							parser_->getNumber(buf_[i] - '0');
						}
					}
					std::cout << parser_->getAllNum().str() << std::endl;
					
					if (write(i32ConnectFD, buf_, rcount) == -1)
					{
						shutdown(i32ConnectFD, SHUT_RDWR);
						close(i32SocketFD);
						throw new std::logic_error("Error writing data");
					}
			}
		}
	}
	else
	{
		int client;
		struct sockaddr_in client_addr;
		socklen_t clientlen = sizeof(client_addr); 
		while ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
		{	
			handle(client);
		}

	}
}

void Server::handle(int client)
{
	int rcount;
	while (1) 
	{
		if ((rcount = recv(client, buf_, 64, 0)) <0)
		{
			continue;
		}
		if (rcount == 0)
		{
			continue;
		}
		std::cout << "Reading message\n";
		std::cout << buf_ << std::endl;
		for (ssize_t i = 0; i < rcount; ++i)
		{
			if (isdigit(buf_[i]))
			{
				parser_->getNumber(buf_[i] - '0');
			}
		}
		std::cout << parser_->getAllNum().str() << std::endl;
		if ((rcount = send(client, buf_, 64, 0)) <0)
		{
			continue;
		}
		if (rcount == 0)
		{
			continue;
		}
	}
	close(client);
}

void Server::printNumbers()
{
	std::cout << parser_->getAllNum().str();
}