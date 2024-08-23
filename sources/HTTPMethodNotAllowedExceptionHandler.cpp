#include "HTTPMethodNotAllowedExceptionHandler.h"
#include "HTTPResponseHeader.h"
// Constructor
HTTPMethodNotAllowedExceptionHandler::HTTPMethodNotAllowedExceptionHandler(){}

void HTTPMethodNotAllowedExceptionHandler::handle (TCPSocket * p_tcpSocket) //this is an exception handler than notifies the user with this error if the method is not allowed
{
    string response = "<H1>405: Method Not Allowed</H1>";
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"Method Not Allowed",405,"HTTP/1.1");
    httpResponseHeader->setHeader("Content-Type","text/html");
    httpResponseHeader->setHeader("Content-Length",to_string(response.length()));
    httpResponseHeader->respond();
    p_tcpSocket->writeToSocket(response.c_str(),response.length());
    delete (httpResponseHeader);

}

HTTPMethodNotAllowedExceptionHandler::~HTTPMethodNotAllowedExceptionHandler(){}