#ifndef HTTPMETHODNOTALLOWEDEXCEPTIONHANDLER_H
#define HTTPMETHODNOTALLOWEDEXCEPTIONHANDLER_H

#include "HTTPExceptionHandler.h"

class HTTPMethodNotAllowedExceptionHandler: public HTTPExceptionHandler
{
    private:
    public:
        HTTPMethodNotAllowedExceptionHandler();
        virtual void handle (TCPSocket * p_tcpSocket) ;
        ~HTTPMethodNotAllowedExceptionHandler(); 
};

#endif