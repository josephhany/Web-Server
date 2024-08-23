#ifndef HTTPRESPONSEHEADER_H
#define HTTPRESPONSEHEADER_H
#include "common.h"
#include "TCPSocket.h"


class HTTPResponseHeader // A class represening an HTTP response header
{
    private:
        std::map <string,string,ignorecase> header; 
        string status;
        int status_code; 
        string protocol; 
        TCPSocket * tcpSocket;
    public:
        HTTPResponseHeader(TCPSocket * p_tcpSocket,string p_status,int p_status_code,string p_protocol);
        void setHeader(string p_key,string p_value); 
        void respond ();
        ~HTTPResponseHeader();
};

#endif
