#include "HTTPTransaction.h"
#include "HTTPGETRequest.h"
#include "HTTPNotAcceptableExceptionHandler.h"
#include "HTTPMethodNotAllowedExceptionHandler.h"

HTTPTransaction::HTTPTransaction (TCPSocket * p_tcpSocket,HTTPServiceManager * p_httpServiceManager,HTTPRequestManager * p_httpRequestManager)
{
    httpServiceManager = p_httpServiceManager;
    tcpSocket = p_tcpSocket;
    httpRequestManager = p_httpRequestManager;
};

HTTPRequest * HTTPTransaction::fetchHTTPRequest ()
{
    cout<<"fetching"<<endl;
    char buffer[100];
    memset (buffer,0,100);
    int read  = 0 ;
    for ( int i = 0 ; i < 10 && read == 0; i ++)
        read = tcpSocket->readFromSocket(buffer,99); //reading from socket to buffer
    if ( read == 0) return NULL;
    stringstream iss(buffer); 
    string method="";
    getline(iss,method,' ');//Getting a line from the buffer 
 
   HTTPRequest * httpRequest = httpRequestManager->getService(tcpSocket,method);    
    if (httpRequest != NULL ) httpRequest->readAndParse(buffer);//Parsed head and body
    return httpRequest; 
}
void HTTPTransaction::process()
{
    HTTPRequest * httpRequest;
    try{ 
        httpRequest= fetchHTTPRequest (); //httpRequest is assigned to either an HTTPPostRequest or HTTPGetRrequest depending on the method in the body.
        if ( httpRequest != NULL)
        {
            HTTPService * s  =httpServiceManager->getService(httpRequest->getResource());//Making a new service its type base on the httpRequest.
            s->execute(httpRequest,tcpSocket);
            delete (httpRequest);
        }
        tcpSocket->shutDown();
    }
    catch (HTTPNotAcceptableExceptionHandler httpNotAcceptableExceptionHandler )
    { 
        httpNotAcceptableExceptionHandler.handle(tcpSocket);
        delete (httpRequest);
        tcpSocket->shutDown();
    }
    catch (HTTPMethodNotAllowedExceptionHandler httpMethodNotAllowedExceptionHandler )
    { 
        httpMethodNotAllowedExceptionHandler.handle(tcpSocket);
        tcpSocket->shutDown();
    }
    
}
void HTTPTransaction::threadMainBody ()
{
    process();
}
void HTTPTransaction::startHTTPTransaction(HTTPTransaction * me)
{
	me->threadMainBody();
}
void HTTPTransaction::setThread(std::thread * p_th)
{
	th = p_th;
	th->detach();
}
bool HTTPTransaction::isRunning()
{
	return !th->joinable();
}

void HTTPTransaction::waitForRunToFinish()
{
	th->join();
}
HTTPTransaction::~HTTPTransaction()
{
    delete (tcpSocket); 
}
