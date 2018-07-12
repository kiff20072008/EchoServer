#ifndef _UDP_CLIENT_HPP_
#define _UDP_CLIENT_HPP_

#include "Client.hpp"

class UDPClient : public Client
{
public:
	UDPClient();
	~UDPClient() override;
	void setData(std::string data) override;
private:
	void create() override;
	void echo() override;
	std::string getServerType() override;
	std::string host_;


};


#endif // !_UDP_CLIENT_HPP_
