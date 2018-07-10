#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_
#include <string>
struct sockaddr_in;
enum whatCon
{
	UDP_,
	TCP_
};


class Client
{
public:
	Client(whatCon con);
	~Client();
	void setDataUDP(std::string host, int port);
	void setDataTCP(std::string ip, int port);
	void run();
private:
	virtual void create();
	virtual void close_socket();
	void echo();

	struct sockaddr_in *stSockAddr;
	int i32Res;
	int i32SocketFD;
	std::string ip_;

	whatCon con_;
	int port_;

	std::string host_;
	int server_;
	int buflen_;
	char* buf_;
	
};
#endif // !_CLIENT_HPP_
