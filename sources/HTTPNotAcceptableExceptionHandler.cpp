#include "HTTPNotAcceptableExceptionHandler.h"
#include "HTTPResponseHeader.h"
HTTPNotAcceptableExceptionHandler::HTTPNotAcceptableExceptionHandler(){}

void HTTPNotAcceptableExceptionHandler::handle (TCPSocket * p_tcpSocket)
{
	string response = "<H1>406: Not Acceptable</H1>";
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"Not Acceptable",406,"HTTP/1.1"); //this is an exception handler than notifies the user with this error if the request is not acceptable
    httpResponseHeader->setHeader("Content-Type","text/html");
    httpResponseHeader->setHeader("Content-Length",to_string(response.length()));
    httpResponseHeader->respond();
    p_tcpSocket->writeToSocket(response.c_str(),response.length());
    delete (httpResponseHeader);
//    you need to add your code here to handle 406 HTTP Errors
}
HTTPNotAcceptableExceptionHandler::~HTTPNotAcceptableExceptionHandler()
{
    
}
