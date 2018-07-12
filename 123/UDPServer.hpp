#ifndef _UDP_SERVER_HPP_
#define _UDP_SERVER_HPP_

#include "Server.hpp"
//class Server;

class UDPServer :public Server
{
public:
	UDPServer();
	~UDPServer();

private:
	void create() override;
	std::string getServerType() override;
	bool getAccept() override;
	int readStr() override;
	int sendStr() override;

};

#endif // !_UDP_SERVER_HPP_
