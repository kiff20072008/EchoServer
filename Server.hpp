#ifndef _SERVER_HPP_
#define _SERVER_HPP_
class NumbersParser;
struct sockaddr_in;

enum whatCon
{
	UDP_,
	TCP_
};

class Server
{
public:
	Server(whatCon con);
	void run();
	~Server();
	void setPort(int port);
private:
	void create();
	void close_socket();
	void serve();
	void handle(int client);
	void printNumbers();	
	struct sockaddr_in *stSockAddr;
	int i32SocketFD, i32ConnectFD;
	NumbersParser *parser_;
	int port_;
	int server_;
	int buflen_;
	char* buf_;
	whatCon con_;
};

#endif // !_SERVER_HPP_
