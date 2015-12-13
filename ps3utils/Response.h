//
// Created by charlton on 10/15/15.
//

#ifndef CLIENT_RESPONSE_H
#define CLIENT_RESPONSE_H
#include <bits/stringfwd.h>
using namespace std;
#include <string>
#include "enums.h"

class Response {
    PS3MAPI_RESPONSECODE responsecode;
    const char *response;
public:
    Response(PS3MAPI_RESPONSECODE responsecode, const char *response);
    PS3MAPI_RESPONSECODE getResponseCode();
    const char * getResponse();
};


#endif //CLIENT_RESPONSE_H
