#pragma once

#include <iostream>
#include <string>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


class UDP_SocketManager{

public:

	UDP_SocketManager();
	~UDP_SocketManager();

	void createIpv4Server(std::string ip, int port);

	void connectToServer();

	void sendData(void* data, size_t len);


private:

	struct sockaddr_in remote;
	socklen_t remoteSize;
	int remotefd;

};
