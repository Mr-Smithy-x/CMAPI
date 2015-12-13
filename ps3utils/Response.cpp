//
// Created by charlton on 10/15/15.
//

#include "Response.h"

Response::Response(PS3MAPI_RESPONSECODE responsecode, const char *response) {
    this->responsecode = responsecode;
    this->response = response;
}

PS3MAPI_RESPONSECODE Response::getResponseCode() {
    return this->responsecode;
}

const char * Response::getResponse() {
    return this->response;
}
