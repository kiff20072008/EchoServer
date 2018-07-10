# Makefile for echo client and server

CXX=			g++ $(CXXFLAGS)

ECHO-SERVER=		Server.o ServerMain.o NumbersParser.o
ECHO-CLIENT=		Client.o ClientMain.o NumbersParser.o
OBJS =			$(ECHO-SERVER) $(ECHO-CLIENT)


CXXFLAGS= -std=c++17

all:	server client

server:$(ECHO-SERVER)
	$(CXX) -o server $(ECHO-SERVER) 

client:$(ECHO-CLIENT)
	$(CXX) -o client $(ECHO-CLIENT) 

clean:
	rm -f $(OBJS) $(OBJS:.o=.d)

realclean:
	rm -f $(OBJS) $(OBJS:.o=.d) server client

%.o : %.cpp
	$(CXX) -c -o $@ -MD -MP ${CPPFLAGS} ${CXXFLAGS} $<

-include $(OBJS:.o=.d)
