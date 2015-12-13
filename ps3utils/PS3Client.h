//
// Created by cj on 10/11/15.
//

#ifndef CLIENT_PS3CLIENT_H
#define CLIENT_PS3CLIENT_H
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class PS3Client {
private:
    typedef int SOCKET;
    int port;
    char* ip;
    SOCKET sock;
    struct sockaddr_in server;
    struct hostent *hp;

public:
    PS3Client();

    PS3Client(char* ip, int port);
    bool createSocket();
    void init(char* ip, int port);
    bool sConnect(char* ip, int port);
    bool sendData(const char *DATA);
    char * recvData();
    bool closeSocket();
    bool disconnect();
    bool isConnected();
    bool sConnect();

    void CloseDataSocket();
    void ConnectDataSocket();
    void OpenDataSocket();


};


#endif //CLIENT_PS3CLIENT_H
