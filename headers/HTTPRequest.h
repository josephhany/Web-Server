#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include "common.h"
#include "TCPSocket.h"


// A class representing an HTTP Request Header
class HTTPRequest
{
    protected:
        std::map <string,string,ignorecase> header;
        string method;
        string resource;
        string protocol;
        TCPSocket * tcpSocket;
        string body;
        void addToHeaderMap(string header_item);
    public:
        HTTPRequest(TCPSocket * p_tcpSocket);
        virtual void readAndParse(string initial_header);
        string getResource (); 
        string & getBody();
        string getMethod();
        string getHeaderValue(string header_item_name);
        virtual HTTPRequest * clone (TCPSocket * p_tcpSocket) = 0; 
        virtual ~HTTPRequest();
};

#endif
