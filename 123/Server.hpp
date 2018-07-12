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
	virtual void create();
	void serve();
	void handle();
	void printNumbers();	
	void sendNumToParser(unsigned int size);
	virtual std::string getServerType();
	virtual bool getAccept() ;
	virtual int readStr() ;
	virtual int sendStr() ;


	NumbersParser* parser_;
	int port_;
	int server_,client_;
	char* buf_;
	int rcount;
};

#endif // !_SERVER_HPP_
