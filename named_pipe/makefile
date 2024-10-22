.PHONY:all
all:server client

server:server.cc
	g++ -o server server.cc -std=c++11 -g
client:client.cc
	g++ -o client client.cc -std=c++11 -g

.PHONY:clean
clean:
	rm -f server client

