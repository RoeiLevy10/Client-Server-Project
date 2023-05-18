CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: clean StompWCIClient

StompWCIClient: bin/StompProtocol.o bin/ConnectionHandler.o bin/event.o bin/Frame.o bin/Game.o bin/KeyboardThread.o bin/SocketThread.o bin/StompClient.o 
	g++ -o bin/StompWCIClient bin/StompProtocol.o bin/ConnectionHandler.o bin/event.o bin/Frame.o bin/Game.o bin/KeyboardThread.o bin/SocketThread.o bin/StompClient.o $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/event.o: src/event.cpp
	g++ $(CFLAGS) -o bin/event.o src/event.cpp

bin/Frame.o: src/Frame.cpp
	g++ $(CFLAGS) -o bin/Frame.o src/Frame.cpp

bin/Game.o: src/Game.cpp
	g++ $(CFLAGS) -o bin/Game.o src/Game.cpp

bin/KeyboardThread.o: src/KeyboardThread.cpp
	g++ $(CFLAGS) -o bin/KeyboardThread.o src/KeyboardThread.cpp

bin/SocketThread.o: src/SocketThread.cpp
	g++ $(CFLAGS) -o bin/SocketThread.o src/SocketThread.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

bin/StompProtocol.o: src/StompProtocol.cpp
	g++ $(CFLAGS) -o bin/StompProtocol.o src/StompProtocol.cpp


EchoClient: bin/ConnectionHandler.o bin/echoClient.o
	g++ -o bin/EchoClient bin/ConnectionHandler.o bin/echoClient.o $(LDFLAGS)

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp


.PHONY: clean

clean:
	rm -f bin/*
	