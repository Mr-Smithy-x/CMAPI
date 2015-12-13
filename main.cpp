using namespace std;
#include <iostream>
#include "CMAPI.h"

int main() {

    CMAPI * j = new CMAPI("192.168.0.101",7887);
    if(j->ConnectIt())
    {
        Response r = j->PS3GetFwType();
        Response g = j->PS3GetFwVersion();
        Response x = j->PS3Reboot();
        cout << x.getResponse() << endl;
    }
    else
    {
        cout << "failed" << endl;
        j->Disconnect();
    }
    return 0;
}

