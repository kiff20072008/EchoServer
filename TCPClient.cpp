#include "TCPClient.hpp"
#include "Defenitions.hpp"

TCPClient::TCPClient()
{
	std::cout << getServerType() << " Client created" << std::endl;
}

TCPClient::~TCPClient()
{
	shutdown(server_, SHUT_RDWR);

	close(server_);
}

void TCPClient::setData(std::string data)
{
	ip_ = data;
}

void TCPClient::create()
{
	std::cout << "Start " << getServerType() << std::endl;
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server_ == -1)
	{
		throw new std::logic_error("Error cant create socket");
	}
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port_);
	client_ = inet_pton(PF_INET, ip_.c_str(), &server_addr.sin_addr);
	if (client_ < 0)
	{
		close(server_);
		throw new std::logic_error("Error. First operator doesn't correct");
	}
	else if (!client_)
	{
		close(server_);
		throw new std::logic_error("Error. Second operator doesn't contain correct IP");

	}
	if (connect(server_, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
	{
		close(server_);
		throw new std::logic_error("Connect error");
	}
	std::cout << "Connected!" << std::endl;
}

void TCPClient::echo()
{
	std::string str;
	std::cin >> str;
	for (;;)
	{
		if (write(server_, str.c_str(), str.length()) == -1)
		{
			close(server_);
			throw new std::logic_error("Error writing data");
		}
		rcount_ = read(server_, buf_, BUFLEN);
		if (rcount_ == -1)
		{
			close(server_);
			throw new std::logic_error("Error reading data");
		}
		for (ssize_t i = 0; i < rcount_; ++i)
		{
			std::cout << buf_[i];
		}
		std::cout << std::endl;
		str.erase();
		std::cin >> str;
	}
}

std::string TCPClient::getServerType()
{
	return "TCP";
}
