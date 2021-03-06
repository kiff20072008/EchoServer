#ifndef _SERVER_HPP_
#define _SERVER_HPP_
#include "NumbersParser.hpp"

class Server
{
public:
	Server();
	void run();
	virtual ~Server();
	void setPort(int port);
protected:
	virtual void create()=0;
	void serve();
	void handle();
	void printNumbers();	
	void sendNumToParser();
	virtual std::string getServerType() = 0;
	virtual bool getAccept() = 0;
	virtual int readStr() = 0;
	virtual int sendStr() = 0;


	NumbersParser parser_;
	int port_;
	int server_,client_;
	char* buf_;
	int rcount_;
};

#endif // !_SERVER_HPP_
