#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include "includes.h"
#include "TCPSocket.h"


class TCPServerSocket 
{
	protected:
		int sock; 
		struct sockaddr_in serverAddr;
		struct sockaddr_in clientAddr;
		char * address;
		int port;
		int backlog;
	public:
		TCPServerSocket (const char * _address, int _port, int _backlog );
		bool initializeSocket ();
		TCPSocket * getConnection (int timeoutSec=0, int timeoutMilli=0,int readBufferSize=10*1024*1024,int writeBufferSize=10*1024*1024);
		virtual ~TCPServerSocket ( );
};

#endif 
