#ifndef HTTPPOSTREQUEST_H
#define HTTPPOSTREQUEST_H
#include "HTTPRequest.h"

class HTTPPOSTRequest : public HTTPRequest
{
    private:
    public:
        HTTPPOSTRequest(TCPSocket * p_tcpSocket);
        virtual void readAndParse(string initial_header);
        virtual HTTPRequest * clone (TCPSocket * p_tcpSocket); 
        ~HTTPPOSTRequest();
};

#endif
