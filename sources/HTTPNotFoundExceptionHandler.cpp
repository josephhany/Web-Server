#include "HTTPNotFoundExceptionHandler.h"
#include "HTTPResponseHeader.h"
// Constructor
HTTPNotFoundExceptionHandler::HTTPNotFoundExceptionHandler(){}

void HTTPNotFoundExceptionHandler::handle (TCPSocket * p_tcpSocket)
{
	string response = "<center><H1>404: Not Found </H1></center>";
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"Not Found",404,"HTTP/1.1"); //this is an exception handler than notifies the user with this error if the page is not found
    httpResponseHeader->setHeader("Content-Type","text/html");
    httpResponseHeader->setHeader("Content-Length",to_string(response.length()));
    httpResponseHeader->respond();
    p_tcpSocket->writeToSocket(response.c_str(),response.length());
    delete (httpResponseHeader);
   //    you need to add your code here to handle 404 HTTP Errors
}

HTTPNotFoundExceptionHandler::~HTTPNotFoundExceptionHandler(){}
