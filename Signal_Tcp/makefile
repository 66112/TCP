.PHONY:all
all:server client
cc = g++
server:server.cc TcpSignalProcess.hpp
	$(cc) -o $@ $^ -g 
client:client.cc 
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -rf server client
