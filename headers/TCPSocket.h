
#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "includes.h"


class TCPSocket
{
    private:
            char remote_address[128];
            char my_address[128];
            struct sockaddr_in myAddr;
            int port;
            int sock;
            bool peerDisconnected;
            bool rshutdown;
            bool wshutdown;
            long stream_out_size;
    public:
            TCPSocket (int _sock ,char * _address=NULL,int _port=0,int readBufferSize=65536,int writeBufferSize=65536);
            TCPSocket (char * _address, int port,int readBufferSize=65536,int writeBufferSize=65536);
            char * getRemoteAddress();
            char * getMyAddress();
            int readFromSocket (char * buffer, int maxBytes );
            int readFromSocketWithTimeout (char * buffer, int maxBytes, long timeoutSec, long timeoutMilli);
            int writeToSocket (const char * buffer, long maxBytes );
            void setPeerDisconnected(bool value);
            bool isPeerDisconnected();
            void shutDownRead();
            void shutDownWrite();
            void shutDown();
            long getStreamOutSize();
            ~TCPSocket ( ); 
};

#endif

