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
    std::string response;
public:
    Response(PS3MAPI_RESPONSECODE responsecode, std::string response);
    PS3MAPI_RESPONSECODE getResponseCode();
    std::string getResponse();
};


#endif //CLIENT_RESPONSE_H
