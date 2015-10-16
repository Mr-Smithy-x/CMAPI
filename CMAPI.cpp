//
// Created by cj on 10/11/15.
//

#include <bits/stringfwd.h>
using namespace std;

#include <string>
#include <iostream>
#include "CMAPI.h"
#include "ps3utils/Response.h"
#include "ps3utils/PS3Client.h"


CMAPI::CMAPI(char* ip, int port) : PS3Client(ip,port) {
    this->ip = ip;
    this->port = port;
}

char*CMAPI::request(const char *str) {
    ConnectIt();
    std::string a = "GET /";
    a += str;
    a += " HTTP/1.1\r\nHOST: 98.113.98.224\r\nConnection: close\r\n";
    char* k = nullptr;
    if(sendData(a.c_str())){
        cout << "Sent" << endl;
        k = recvData();
    }
    closeSocket();
    return k;
}

Response *CMAPI::PS3Reboot() {
    bool a = sendData("PS3 REBOOT");
    if(a){

        string response;
        PS3MAPI_RESPONSECODE responsecode;
        string content(recvData());
        parseResponseCode(content, response, responsecode);
        return new Response(responsecode, response);
    }
}

Response *CMAPI::PS3Shutdown() {
    bool a = sendData("PS3 SHUTDOWN");
    if(a){
        string response;
        PS3MAPI_RESPONSECODE responsecode;
        string content(recvData());
        parseResponseCode(content, response, responsecode);
        disconnect();
        return new Response(responsecode, response);
    }
}

bool CMAPI::ConnectIt() {
    sConnect();
    string recv(recvData());
    string res;
    PS3MAPI_RESPONSECODE resc;
    parseResponseCode(recv, res, resc);
    if(resc == PS3MAPICONNECTED){
        string recv2 = string(recvData());
        string res2;
        PS3MAPI_RESPONSECODE  resc2;
        parseResponseCode(recv2, res2, resc2);
        return resc2 == PS3MAPICONNECTEDOK;
    }
    return false;
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

void CMAPI::parseResponseCode(string content, string &response, PS3MAPI_RESPONSECODE &responsecode) {
    response = ReplaceString( ReplaceString(content.substr(4), "\n", ""), "\n", "");
    int response_num = atoi(content.substr(0,3).c_str());
    switch(response_num){
        case PS3MAPI_RESPONSECODE::PS3MAPICONNECTED:
                responsecode = PS3MAPICONNECTED;
            break;
        case PS3MAPI_RESPONSECODE::PS3MAPICONNECTEDOK:
                responsecode = PS3MAPI_RESPONSECODE::PS3MAPICONNECTEDOK;
            break;
        case PS3MAPI_RESPONSECODE::COMMANDOK:
                responsecode = PS3MAPI_RESPONSECODE::COMMANDOK;
            break;
        case PS3MAPI_RESPONSECODE::DATACONNECTIONALREADYOPEN:
                responsecode = PS3MAPI_RESPONSECODE::DATACONNECTIONALREADYOPEN;
            break;
        case PS3MAPI_RESPONSECODE::ENTERINGPASSIVEMOVE:
                responsecode = PS3MAPI_RESPONSECODE::ENTERINGPASSIVEMOVE;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYACTIONCOMPLETED:
                responsecode = PS3MAPI_RESPONSECODE::MEMORYACTIONCOMPLETED;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYSTATUSOK:
                responsecode = PS3MAPI_RESPONSECODE::MEMORYSTATUSOK;
            break;
        case PS3MAPI_RESPONSECODE::REQUESTSUCCESSFUL:
                responsecode = PS3MAPI_RESPONSECODE::REQUESTSUCCESSFUL;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYACTIONPENDING:
                responsecode = PS3MAPI_RESPONSECODE::MEMORYACTIONPENDING;
            break;
        default:
                responsecode = PS3MAPI_RESPONSECODE::FAIL;
            break;
    }

}

bool CMAPI::Disconnect() {
    return disconnect();
}

void CMAPI::getMemory(int process, int address, unsigned char &memory) {
    string a("PROCESS GETMEMORY " + std::to_string(process) + " " + std::to_string(address));
    if(sendData(a.c_str())){

    }
}



Response *CMAPI::PS3GetFwType() {
    return nullptr;
}

Response *CMAPI::PS3GetFwVersion() {
    return nullptr;
}

Response *CMAPI::PS3DisableSysCall() {
    return nullptr;
}

Response *CMAPI::PS3CheckSysCall() {
    return nullptr;
}

Response *CMAPI::PS3ParialCheckSysCall() {
    return nullptr;
}

Response *CMAPI::PS3DeleteHistory() {
    return nullptr;
}

void CMAPI::setBinaryMode(bool mode) {

}
