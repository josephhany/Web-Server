#include "HTTPPOSTRequest.h" 

HTTPPOSTRequest::HTTPPOSTRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket) {}

void HTTPPOSTRequest::readAndParse(string initial_header)
{
    HTTPRequest::readAndParse(initial_header); 
    long stdin_size = atol(header["content-length"].c_str());//getting content length
    
    for ( ;body.length() < stdin_size; )
    {
        char buffer[1024]; 
        memset ( buffer,0,1024); 
        tcpSocket->readFromSocket(buffer,1023); //Reading from socket into buffer
        body +=buffer;
    }
}
HTTPRequest * HTTPPOSTRequest::clone (TCPSocket * p_tcpSocket)
{
    return new HTTPPOSTRequest(p_tcpSocket);
}
HTTPPOSTRequest::~HTTPPOSTRequest()
{
}
