#ifndef HTTPREQUESTMANAGER_H
#define HTTPREQUESTMANAGER_H
#include "HTTPGETRequest.h"
#include "HTTPPOSTRequest.h"
#include "HTTPHEADRequest.h"

class HTTPRequestManager 
{
    private:
        std::map <string,HTTPRequest *,ignorecase> methods; 
    public:
        HTTPRequestManager();
        HTTPRequest * getService (TCPSocket * p_tcpSocket,string p_method); 
        ~HTTPRequestManager();
};


#endif 
