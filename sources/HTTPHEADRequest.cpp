#include "HTTPHEADRequest.h"
#include "TCPSocket.h" 

HTTPHEADRequest::HTTPHEADRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket)
{
}
HTTPRequest * HTTPHEADRequest::clone (TCPSocket * p_tcpSocket)
{
    return new HTTPHEADRequest(p_tcpSocket);
}
HTTPHEADRequest::~HTTPHEADRequest()
{
}
