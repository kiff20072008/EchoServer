#include "Client.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <exception>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define BUFLEN 64
Client::Client(whatCon con):con_(con)
{
	buflen_ = BUFLEN;
	buf_ = new char[BUFLEN + 1];
}

Client::~Client()
{
	if (con_ == TCP_)
	{
		shutdown(i32SocketFD, SHUT_RDWR);

		close(i32SocketFD);
	}
	else
	{
		close_socket();
	}
}

void Client::setDataUDP(std::string host, int port)
{
	host_ = host;
	port_ = port;
}

void Client::setDataTCP(std::string ip, int port)
{
	ip_ = ip;
	port_ = port;
}

void Client::run()
{
	create();
	echo();
}

void Client::create()
{
	if (con_ == UDP_)
	{
		std::cout << "Start UDP"<<std::endl;
		struct sockaddr_in server_addr;
		struct hostent *hostEntry;
		hostEntry = gethostbyname(host_.c_str());
		if (!hostEntry) 
		{
			throw new std::logic_error( "No such host name: " + host_);
		}
		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port_);
		memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);
		server_ = socket(PF_INET, SOCK_STREAM, 0);
		if (!server_) 
		{
			throw new std::logic_error("Error socket");
		}
		if (connect(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
		{
			throw new std::logic_error("Error connect");
		}
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Start TCP" << std::endl;
		i32SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		if (i32SocketFD == -1) 
		{
			throw new std::logic_error("Error cant create socket");
		}
		stSockAddr = new sockaddr_in();
		memset(stSockAddr, 0, sizeof(*stSockAddr));

		stSockAddr->sin_family = PF_INET;
		stSockAddr->sin_port = htons(3000);
		i32Res = inet_pton(PF_INET, "127.0.0.1", &stSockAddr->sin_addr);
		if (i32Res < 0)
		{
			close(i32SocketFD);
			throw new std::logic_error("Error. First operator doesn't correct");
		}
		else if (!i32Res) 
		{
			close(i32SocketFD);
			throw new std::logic_error("Error. Second operator doesn't contain correct IP");
			
		}
		if (connect(i32SocketFD, (struct sockaddr*) stSockAddr, sizeof(*stSockAddr)) == -1)
		{
			close(i32SocketFD); 
			throw new std::logic_error("Connect error");
		}
		std::cout << "Connected!" << std::endl;
	}
}

void Client::close_socket()
{
	close(server_);
}

void Client::echo()
{
	ssize_t rcount;
	std::string str;
	std::cin>>str;
	for(;;)
	{
		if (con_ == TCP_)
		{
			if (write(i32SocketFD,str.c_str(), str.length()) == -1)
			{
				std::cout << "Error writing data";
				close(i32SocketFD);
				exit(EXIT_FAILURE);
			}
			rcount = read(i32SocketFD, buf_, 64);
			if (rcount == -1)
			{
				std::cout << "Error reading data";
				close(i32SocketFD);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			send(server_, str.c_str(), str.length(), 0);
			rcount = recv(server_, buf_, 64, 0);
		}
		for (ssize_t i = 0; i < rcount; ++i)
		{
			std::cout << buf_[i];
		}
		std::cout << std::endl;
		str.erase();
		std::cin >> str;
	}
}


