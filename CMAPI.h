//
// Created by cj on 10/11/15.
//

#ifndef CLIENT_JMAPI_H
#define CLIENT_JMAPI_H
#include "ps3utils/enums.h"
#include "ps3utils/Response.h"
#include "ps3utils/PS3Client.h"

class CMAPI : protected PS3Client{
    public:
    CMAPI(char *ip, int port);
    bool Disconnect();
    bool ConnectIt();
    Response * PS3Reboot();
    Response * PS3Shutdown();
    Response * PS3GetFwVersion();
    Response * PS3GetFwType();
    Response * PS3DisableSysCall();
    Response * PS3CheckSysCall();
    Response * PS3ParialCheckSysCall();
    Response * PS3DeleteHistory();
    void getMemory(int process, int address, unsigned char &memory);

    char * request(const char *string);

private:
    char *ip;
    int port;
    void parseResponseCode(string content, string &response, PS3MAPI_RESPONSECODE &responsecode);
    void setBinaryMode(bool mode);

};


#endif //CLIENT_JMAPI_H
