#include "UDPClient.hpp"
#include "Defenitions.hpp"

UDPClient::UDPClient()
{
	std::cout << getServerType() << " Client created" << std::endl;
}

UDPClient::~UDPClient()
{
	close(server_);
}

void UDPClient::setData(std::string data)
{
	host_ = data;
}

void UDPClient::create()
{
	std::cout << "Start " << getServerType() << std::endl;
	struct hostent *hostEntry;
	hostEntry = gethostbyname(host_.c_str());
	if (!hostEntry)
	{
		throw new std::logic_error("No such host name: " + host_);
	}
	struct sockaddr_in server_addr;
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

void UDPClient::echo()
{
	std::string str;
	std::cin >> str;
	for (;;)
	{
		send(server_, str.c_str(), str.length(), 0);
		rcount_ = recv(server_, buf_, 64, 0);
		for (ssize_t i = 0; i < rcount_; ++i)
		{
			std::cout << buf_[i];
		}
		std::cout << std::endl;
		str.erase();
		std::cin >> str;
	}
}

std::string UDPClient::getServerType()
{
	return "UDP";
}
