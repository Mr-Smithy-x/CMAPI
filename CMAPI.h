//
// Created by cj on 10/11/15.
//

#ifndef CLIENT_JMAPI_H
#define CLIENT_JMAPI_H

#include <sstream>
#include "ps3utils/enums.h"
#include "ps3utils/Response.h"
#include "ps3utils/PS3Client.h"

class CMAPI : protected PS3Client{
    public:
    CMAPI(char *ip, int port);
    bool Disconnect();
    bool ConnectIt();
    Response PS3Reboot();
    Response PS3SoftReboot();
    Response PS3HardReboot();
    Response PS3Shutdown();
    Response PS3GetFwVersion();
    Response PS3GetFwType();
    Response PS3Notify(char *msg);
    Response PS3ParialCheckSysCall();
    Response PS3DeleteHistory();
    Response PS3Buzzer(BUZZER buzzer);
    Response PS3Led(LEDCOLOR color, LEDMODE mode);
    Response PS3DisableSysCall(SYSCALL8MODE syscall8MODE);
    Response PS3CheckSysCall(int mode);
    Response PS3ParialDisableSysCall(int mode);
    Response PS3GetTemperature();
    Response PS3GetIdps();
    Response PS3GetPsid();
    Response PS3SetIdps(char *idps);
    Response PS3SetPsid(char *psid);
    Response GetServerMinVersion();
    Response GetServerMaxVersion();
    Response GetCoreMinVersion();
    Response GetCoreMaxVersion();
    Response PS3RemoveHook();
    Response PS3GetName(int process);
    Response PS3GetAllPid();
    void PS3GetMemory(int process, int address, unsigned char* &memory);
    void PS3SetMemory(int process, int address, unsigned char* bytes);
    const char * request(const char *string);

private:
    char *ip;
    int port;
    Response doCommand(char* cmd);
    void parseResponseCode(string content, string *response, PS3MAPI_RESPONSECODE *responsecode);

    void setBinaryMode(bool mode);

};


#endif //CLIENT_JMAPI_H
