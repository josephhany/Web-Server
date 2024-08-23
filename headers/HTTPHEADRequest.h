#ifndef HTTPHEADREQUEST_H
#define HTTPHEADREQUEST_H
#include "HTTPRequest.h"

class HTTPHEADRequest : public HTTPRequest
{
    private:
    public:
        HTTPHEADRequest(TCPSocket * p_tcpSocket);
        virtual HTTPRequest * clone (TCPSocket * p_tcpSocket);
        ~HTTPHEADRequest();
};

#endif
