#ifndef HTTPEXCEPTIONHANDLER_H
#define HTTPEXCEPTIONHANDLER_H

#include "TCPSocket.h"

class HTTPExceptionHandler
{
    private:
    public:
        HTTPExceptionHandler();
        virtual void handle (TCPSocket * tcpSocket) = 0;
        virtual ~HTTPExceptionHandler();
};

#endif