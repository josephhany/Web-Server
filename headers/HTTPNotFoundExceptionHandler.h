#ifndef HTTPNOTFOUNDEXCEPTIONHANDLER_H
#define HTTPNOTFOUNDEXCEPTIONHANDLER_H

#include "HTTPExceptionHandler.h"
class HTTPNotFoundExceptionHandler: public HTTPExceptionHandler
{
    private:
    public:
        HTTPNotFoundExceptionHandler();     
        virtual void handle (TCPSocket * p_tcpSocket) ;
        ~HTTPNotFoundExceptionHandler(); 
};

#endif