//
// Created by cj on 10/11/15.
//

#include <bits/stringfwd.h>
using namespace std;

#include <string>
#include <iostream>
#include <string.h>
#include "CMAPI.h"


CMAPI::CMAPI(char* ip, int port) : PS3Client(ip,port) {
    this->ip = ip;
    this->port = port;
}

const char*CMAPI::request(const char *str) {
    ConnectIt();
    std::string a = "GET /";
    a += str;
    a += " HTTP/1.1\r\nHOST: ip \r\nConnection: close\r\n";
    const char* k = nullptr;
    if(sendData(a.c_str())){
        cout << "Sent" << endl;

        k = recvData();
    }
    closeSocket();
    return k;
}

bool CMAPI::ConnectIt() {
    sConnect();
    string b(recvData());
    string res;
    PS3MAPI_RESPONSECODE resc;
    parseResponseCode(b, &res, &resc);
    if(resc == PS3MAPICONNECTED){
        string recv2 = recvData();
        string res2;
        PS3MAPI_RESPONSECODE  resc2;
        parseResponseCode(recv2, &res2, &resc2);
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

void CMAPI::parseResponseCode(string content, string *response, PS3MAPI_RESPONSECODE *responsecode) {
    *response = ReplaceString( ReplaceString(content.substr(4), "\n", ""), "\r", "");
    int response_num = atoi(content.substr(0,3).c_str());
    switch(response_num){
        case PS3MAPI_RESPONSECODE::PS3MAPICONNECTED:
                *responsecode = PS3MAPICONNECTED;
            break;
        case PS3MAPI_RESPONSECODE::PS3MAPICONNECTEDOK:
            *responsecode = PS3MAPI_RESPONSECODE::PS3MAPICONNECTEDOK;
            break;
        case PS3MAPI_RESPONSECODE::COMMANDOK:
            *responsecode = PS3MAPI_RESPONSECODE::COMMANDOK;
            break;
        case PS3MAPI_RESPONSECODE::DATACONNECTIONALREADYOPEN:
            *   responsecode = PS3MAPI_RESPONSECODE::DATACONNECTIONALREADYOPEN;
            break;
        case PS3MAPI_RESPONSECODE::ENTERINGPASSIVEMOVE:
            *   responsecode = PS3MAPI_RESPONSECODE::ENTERINGPASSIVEMOVE;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYACTIONCOMPLETED:
            *   responsecode = PS3MAPI_RESPONSECODE::MEMORYACTIONCOMPLETED;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYSTATUSOK:
            *   responsecode = PS3MAPI_RESPONSECODE::MEMORYSTATUSOK;
            break;
        case PS3MAPI_RESPONSECODE::REQUESTSUCCESSFUL:
            *   responsecode = PS3MAPI_RESPONSECODE::REQUESTSUCCESSFUL;
            break;
        case PS3MAPI_RESPONSECODE::MEMORYACTIONPENDING:
            *   responsecode = PS3MAPI_RESPONSECODE::MEMORYACTIONPENDING;
            break;
        default:
            *   responsecode = PS3MAPI_RESPONSECODE::FAIL;
            break;
    }

}

bool CMAPI::Disconnect() {
    return disconnect();
}


Response CMAPI::doCommand(char *cmd) {
    if(sendData(cmd)){
        string response;
        PS3MAPI_RESPONSECODE responsecode;
        string content(recvData());
        parseResponseCode(content, &response, &responsecode);
        return Response(responsecode, response.c_str());
    }
    return Response(FAIL, "Error");
}


//Not completed
void CMAPI::PS3GetMemory(int process, int address, unsigned char* &memory) {
    this->setBinaryMode(true);

    char* cmd = "PROCESS GETMEMORY ";
    strcat(cmd, std::to_string(process).c_str());
    strcat(cmd, " ");
    strcat(cmd, std::to_string(address).c_str());
    if(sendData(cmd)){

    }
    this->setBinaryMode(false);
}

void CMAPI::PS3SetMemory(int process, int address, unsigned char* bytes) {

}

Response CMAPI::PS3Shutdown() {
    Response r = doCommand("PS3 SHUTDOWN");
    disconnect();
    return r;
}

Response CMAPI::PS3Reboot() {
    return doCommand("PS3 REBOOT");
}

Response CMAPI::PS3SoftReboot() {
    return doCommand("PS3 SOFTREBOOT");
}

Response CMAPI::PS3HardReboot() {
    return doCommand("PS3 HARDREBOOT");
}

Response CMAPI::PS3Notify(char* msg) {
    char* cmd = "PS3 NOTIFY ";
    strcat(cmd, msg);
    return doCommand(cmd);
}

Response CMAPI::PS3Buzzer(BUZZER buzzer) {
    char* cmd = "PS3 BUZZER";
    strcat(cmd, std::to_string(buzzer).c_str());
    return doCommand(cmd);
}

Response CMAPI::PS3Led(LEDCOLOR color, LEDMODE mode) {
    char* cmd = "PS3 LED ";
    strcat(cmd, std::to_string(color).c_str());
    strcat(cmd, " ");
    strcat(cmd, std::to_string(mode).c_str());
    return doCommand(cmd);
}

Response CMAPI::PS3GetFwType() {
    return doCommand("PS3 GETFWTYPE");
}

Response CMAPI::PS3GetFwVersion() {
    return doCommand("PS3 GETFWVERSION");
}

Response CMAPI::PS3DisableSysCall(SYSCALL8MODE syscall8MODE) {
    char* cmd = "PS3 DISABLESYSCALL ";
    strcat(cmd, std::to_string(syscall8MODE).c_str());
    return doCommand(cmd);
}

Response CMAPI::PS3CheckSysCall(int mode) {
    char* cmd = "PS3 CHECKSYSCALL ";
    strcat(cmd, std::to_string(mode).c_str());
    return doCommand(cmd);
}

Response CMAPI::PS3ParialCheckSysCall() {
    return doCommand("PS3 PCHECKSYSCALL8");
}

Response CMAPI::PS3ParialDisableSysCall(int mode) {
    char* cmd = "PS3 PDISABLESYSCALL8 ";
    strcat(cmd, std::to_string(mode).c_str());
    return doCommand(cmd);
}

Response CMAPI::GetServerMinVersion() {
    return doCommand("SERVER GETMINVERSION");
}
Response CMAPI::GetServerMaxVersion() {
    return doCommand("SERVER GETVERSION");
}
Response CMAPI::GetCoreMinVersion() {
    return  doCommand("CORE GETMINVERSION");
}
Response CMAPI::GetCoreMaxVersion() {
    return doCommand("CORE GETVERSION");
}

Response CMAPI::PS3GetTemperature() /*cpu|rsx*/ {
    return doCommand("PS3 GETTEMP");
}
Response CMAPI::PS3GetIdps() {
    return doCommand("PS3 GETIDPS");
}
Response CMAPI::PS3GetPsid() {
    return doCommand("PS3 GETPSID");
}
Response CMAPI::PS3SetIdps(char* idps) /*0-16, 16-32*/ {
    if(strlen(idps) != 32){
        return Response(PS3MAPI_RESPONSECODE::FAIL ,"IDPS needs to be 32 characters long");
    }
    char* cmd = "PS3 SETIDPS ";
    strcat(cmd, string(idps).substr(0, 16).c_str());
    strcat(cmd, " ");
    strcat(cmd, string(idps).substr(16,32).c_str());
    return doCommand(cmd);
}
Response CMAPI::PS3SetPsid(char* psid) /*0-16, 16-32*/ {
    if(strlen(psid) != 32){
        return Response(PS3MAPI_RESPONSECODE::FAIL ,"PSID needs to be 32 characters long");
    }
    char* cmd = "PS3 SETPSID ";
    strcat(cmd, string(psid).substr(0, 16).c_str());
    strcat(cmd, " ");
    strcat(cmd, string(psid).substr(16,32).c_str());
    return doCommand(cmd);
}
Response CMAPI::PS3DeleteHistory() {
    return doCommand("PS3 DELHISTORY");
}
Response CMAPI::PS3RemoveHook(){
    return doCommand("PS3 REMOVEHOOK");
}
Response CMAPI::PS3GetName(int process){
    char* cmd = "PS3 GETNAME ";
    strcat(cmd, std::to_string(process).c_str());
    return doCommand(cmd);
}
Response CMAPI::PS3GetAllPid() /*split by |*/{
    return doCommand("PS3 GETALLPID");
}

void CMAPI::setBinaryMode(bool mode) {
    char* cmd = "TYPE ";
    strcat(cmd, (mode) ? "I" : "A");
    if(sendData(cmd)){
        char* b = recvData();
        cout << b << endl;
    }
}

/*
//----MEMORY
//MEMORY GET {pid} {address} {bytes(num of bytes)}
//MEMORY SET {pid} {address} {bytes} ??

//----MODULE
MODULE GETALLPRXID {pid} //int
MODULE GETNAME {pid} {prxid} //int
MODULE GETFILENAME {pid} {prxid}
MODULE LOAD {pid} {path}
MODULE UNLOAD {pid} {prxix}

//----VSH
MODULE GETVSHPLUGINFO {slot}
MODULE LOADVSHPLUG {slot} {path}
MODULE UNLOADVSHPLUGS {slot}

//OPENDATASOCKET
PASV // THEN U USE THE DETAILS TO OPEN PORT ON THE CLIENT SIDE
*/
