//
// Created by cj on 10/11/15.
//


#include <bits/stringfwd.h>
using namespace std;

#include <string>
#include <string.h>
#include <iostream>
#include "PS3Client.h"

bool PS3Client::createSocket() {
    sock = socket(AF_INET,SOCK_STREAM, 0);
    if(sock < 0) {
        perror("FAILED to create socket");
        close(sock);
        return false;
    }
   return true;
}


bool PS3Client::closeSocket(){
    close(sock);
}

bool PS3Client::isConnected(){

}

bool PS3Client::sConnect(char *ip, int port) {
    init(ip,port);
    if(connect(sock, (struct sockaddr*)&server, sizeof(server))<0)
    {
        perror("connect failed");
        return false;
    }
    return true;
}

bool PS3Client::sConnect() {
    init(ip,this->port);
    if(connect(sock, (struct sockaddr*)&server, sizeof(this->server))<0)
    {
        perror("connect failed");
        return false;
    }
    return true;
}

void PS3Client::init(char *ip, int port) {
    server.sin_family = AF_INET;
    hp = gethostbyname(ip);
    memcpy(&this->server.sin_addr,hp->h_addr, hp->h_length);
    server.sin_port=htons(port);
}

bool PS3Client::sendData(const char *DATA) {
    cout << DATA << endl;
    if(send(sock, DATA, sizeof(DATA),0) < 0){
        perror("send failed");
        return false;
    }
    return true;
}

char* PS3Client::recvData() {
    char buffer[512];
    if(recv(sock,&buffer, sizeof(buffer),0) < 0){
        perror("recv failed");
    }
    return buffer;
}

PS3Client::PS3Client( char* ip, int port) {
    this->ip = ip;
    this->port = port;
    createSocket();
}

PS3Client::PS3Client() {
    createSocket();
}

bool PS3Client::disconnect() {
    if(!sendData("DISCONNECT")){
        return closeSocket();
    }else{
        return closeSocket();
    }
    return false;
}
//From JMAPI
/*
protected void OpenDataSocket() throws IOException, JMAPIException {
            String[] split = pav.getResponse().substring(start, end).split(",");
            String ip = String.format("%s.%s.%s.%s", split[0], split[1], split[2], split[3]);
            int port = (Integer.valueOf(split[4]) << 8) + (Integer.valueOf(split[5]));
            data_sock = new Socket();
            data_sock.connect(new InetSocketAddress(ip, port));
}*/

void PS3Client::OpenDataSocket() {
    if(sendData("PASV")){
        string res = recvData();
        int start = res.find("(")+1;
        int end = res.find(")");
        string substr = res.substr(start,end-start);
    }
}
