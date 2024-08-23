#ifndef HTTPTRANSACTION_H
#define HTTPTRANSACTION_H
#include "HTTPServiceManager.h"
#include "HTTPRequest.h"
#include "HTTPRequestManager.h"

class HTTPTransaction
{
    private:
        TCPSocket * tcpSocket;
        HTTPServiceManager * httpServiceManager;
        HTTPRequestManager * httpRequestManager;
        thread * th;
        HTTPRequest * fetchHTTPRequest ();
        void process();
    public:
        HTTPTransaction (TCPSocket * p_tcpSocket,HTTPServiceManager * p_httpServiceManager,HTTPRequestManager * p_httpRequestManager);
        void  threadMainBody (); 
        static void startHTTPTransaction(HTTPTransaction * me);
        void setThread(thread * p_th);
        bool isRunning();
        void waitForRunToFinish();
        ~HTTPTransaction();
};

#endif
