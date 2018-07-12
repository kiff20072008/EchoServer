#ifndef _TCP_CLIENT_HPP_
#define _TCP_CLIENT_HPP_
#include "Client.hpp"

class TCPClient : public Client
{
public:
	TCPClient();
	~TCPClient() override;
	void setData(std::string data) override;
private:
	void create() override;
	void echo() override;
	std::string getServerType() override;
	std::string ip_;


};

#endif // !_TCP_CLIENT_HPP_
