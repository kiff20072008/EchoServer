#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include "Server.hpp"
//class Server;

class TCPServer :public Server
{
public:
	TCPServer();
	~TCPServer();

private:
	void create() override;
	std::string getServerType() override;
	bool getAccept() override;
	int readStr() override;
	int sendStr() override;

};

#endif // !_TCP_SERVER_HPP_
