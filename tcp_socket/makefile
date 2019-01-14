.PHONY:all
all:server client
cc = g++
server:server.cc Tcpserver.hpp
	$(cc) -o $@ $^  
client:client.cc 
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
