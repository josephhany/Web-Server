#ifndef HTTPNOTACCEPTABLEEXCEPTIONHANDLER_H
#define HTTPNOTACCEPTABLEEXCEPTIONHANDLER_H

#include "HTTPExceptionHandler.h"
class HTTPNotAcceptableExceptionHandler: public HTTPExceptionHandler
{ 
    private:
    public:
        HTTPNotAcceptableExceptionHandler();
        virtual void handle (TCPSocket * p_tcpSocket) ;
        ~HTTPNotAcceptableExceptionHandler();
};

#endif