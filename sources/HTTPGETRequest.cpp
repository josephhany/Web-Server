#include "HTTPGETRequest.h"
#include "TCPSocket.h" 

HTTPGETRequest::HTTPGETRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket)
{
}
HTTPRequest * HTTPGETRequest::clone (TCPSocket * p_tcpSocket)
{
    return new HTTPGETRequest(p_tcpSocket);
}
HTTPGETRequest::~HTTPGETRequest()
{
}
