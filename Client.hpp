#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <string>


class Client
{
public:
	Client();
	virtual ~Client();
	void run();
	void setPort(int port );
	virtual void setData(std::string data) = 0;
protected:
	virtual void create()=0;
	virtual void echo() = 0;
	virtual std::string getServerType() = 0;

	int rcount_;
	int port_;

	int server_,client_;
	char* buf_;
	
};
#endif // !_CLIENT_HPP_
