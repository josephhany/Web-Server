#include "HTTPRequestManager.h"
#include "HTTPMethodNotAllowedExceptionHandler.h"
HTTPRequestManager::HTTPRequestManager()
{
    methods ["GET"] = new HTTPGETRequest(NULL);//Making a new GetRequest object
    methods ["POST"] = new HTTPPOSTRequest(NULL);//Making a new PostRequest object
    methods ["HEAD"] = new HTTPHEADRequest(NULL);//Making a new HeadRequest object
    
}
HTTPRequest * HTTPRequestManager::getService (TCPSocket * p_tcpSocket,string p_method)
{
cout << "Method: " <<p_method << endl; 
    if ( methods[p_method]==NULL) throw (HTTPMethodNotAllowedExceptionHandler());
    return methods[p_method]->clone(p_tcpSocket); // else clone and return the object
}
// Destructor
HTTPRequestManager::~HTTPRequestManager()
{
    for_each (methods.begin(),methods.end(),[](const std::pair<string,HTTPRequest *>& it) -> bool {
        HTTPRequest * httpRequest = std::get<1>(it);
        delete(httpRequest);
        return true;
   });

}
