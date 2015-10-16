using namespace std;
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "CMAPI.h"

int main() {

    cout << "HI" << endl;
    CMAPI * j = new CMAPI("192.168.0.101",7887);
    if(j->ConnectIt())
    {
        Response *r = j->PS3Reboot();
        printf("%i - ",r->getResponseCode());
        printf(r->getResponse().c_str());
        delete r;
    }
    else
    {
        j->Disconnect();
    }
    return 0;
}

