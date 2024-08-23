/* 
 * File:   main.cpp
 * Author: kmsobh
 *
 * Created on October 21, 2016, 12:20 PM
 */

#include "TCPServerSocket.h"
#include "HTTPTransaction.h"
#include "GarbageCollector.h"
#include "HTTPRequestManager.h"

using namespace std;

int main(int argc, char** argv) {

    // add code here to exteract command line arguments
    GarbageCollector * garbageCollector = new GarbageCollector();
    HTTPServiceManager * httpServiceManager = new HTTPServiceManager();
    HTTPRequestManager * httpRequestManager = new HTTPRequestManager();
    TCPServerSocket * tcpServerSocket = new TCPServerSocket("127.0.0.1",9999,100);

    // add your code here

    tcpServerSocket->initializeSocket();//Initializing socket with for the server with port sent previously

    while(1) // Loop forever
    {
        // Wait for connection and return a TCPSocket object upon one
        TCPSocket * tcpSocket = tcpServerSocket->getConnection(0,0,-1,-1); //Accept multiple clients in parrellel 
        if (tcpSocket == NULL) break;  // if tcpSocket is NULL then error occured and we break the loop
        garbageCollector->cleanup(); // Invoke the garbage collector cleaner in case of expired connections
        HTTPTransaction * c = new HTTPTransaction (tcpSocket, httpServiceManager, httpRequestManager); // Instantiate a new Connection object and pass the returned TCP socket to it
        std::thread * t = new std::thread (HTTPTransaction::startHTTPTransaction,c); // Start the connection thread to communicate with the client
        c->setThread(t);
        garbageCollector->addHTTPTransaction(c); // Add the connection to the garbage collector to be cleaned up when expired
    }


    delete(garbageCollector); // Delete the garbage collector
    delete (tcpServerSocket); // Terminate and delete the TCP server socket

    return 0;
}

