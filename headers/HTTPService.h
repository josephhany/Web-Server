#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H
#include "FileCache.h"
#include "TCPSocket.h"
#include "HTTPRequest.h"

class HTTPService
{
    protected:
        FileCache * fileCache;
        bool clean_cache;
        long getTimeStamp (string date_string);
    public:
        HTTPService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket) = 0;
        virtual HTTPService * clone () = 0;
        virtual ~HTTPService();
};

#endif
