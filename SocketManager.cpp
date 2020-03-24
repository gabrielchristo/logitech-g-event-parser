#include "SocketManager.hpp"

UDP_SocketManager::UDP_SocketManager(){
	this->remoteSize = sizeof this->remote;
}

void UDP_SocketManager::createIpv4Server(std::string ip, int port){

	this->remotefd = socket(AF_INET, SOCK_DGRAM, 0);

	this->remote.sin_family = AF_INET;
	this->remote.sin_addr.s_addr = inet_addr(ip.c_str());
	this->remote.sin_port = htons(port);

}

void UDP_SocketManager::connectToServer(){
	connect(this->remotefd, (struct sockaddr *) &remote, this->remoteSize);
}

void UDP_SocketManager::sendData(void* data, size_t len){
	if(send(this->remotefd, data, len, 0) == -1)
		fprintf(stderr, "Failure on send socket data\t Errno: %d\n", errno);
}
