#include "TCPSocket.h"
TCPSocket::TCPSocket (int _sock,char * _address, int _port ,int readBufferSize,int writeBufferSize)//This is code for making socket
{
    stream_out_size = 0;
    sock = _sock;
    peerDisconnected = false;
    memset (remote_address ,0 , 128);
    memset (my_address ,0 , 128);
    if ( _address != NULL) strcpy(remote_address,_address);
    port = _port; 
    if ( readBufferSize != -1 && setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(void*) &readBufferSize,sizeof(int)) == -1)
        printf ("Error setting receive buffer\n");
    if ( writeBufferSize != -1 &&  setsockopt(sock, SOL_SOCKET, SO_SNDBUF,(void*) &writeBufferSize,sizeof(int)) == -1)
        printf ("Error setting send buffer\n");
    
    int flag = 0;
    setsockopt(sock,
                IPPROTO_TCP,
                TCP_NODELAY,
                (char *) &flag,
                sizeof(int));
    socklen_t my_sock_size = sizeof(struct sockaddr);
    getsockname (sock,(struct sockaddr *)&myAddr,&my_sock_size);
    strcpy(my_address , inet_ntoa(myAddr.sin_addr));
    rshutdown = false;
    wshutdown= false;
}
TCPSocket::TCPSocket (char * _address, int port ,int readBufferSize,int writeBufferSize)
{
    memset (remote_address, 0, 128);
    memset (my_address, 0, 128);
    stream_out_size = 0;
    peerDisconnected = false;
    strcpy(remote_address, _address);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr; 
    struct hostent *server; 
    server = gethostbyname(remote_address);
    if ( server == NULL ||  server->h_addr == NULL) 
        printf ("Cannot retrieve server address information\n");
    else { 
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(port); 
        int flag = 0;
        setsockopt(sock,
                    IPPROTO_TCP,
                    TCP_NODELAY,
                    (char *) &flag,
                    sizeof(int));
        if ( readBufferSize != -1 && setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(void*) &readBufferSize,sizeof(int)) == -1)
            printf ("Error setting receive buffer\n");
        if ( writeBufferSize != -1 &&  setsockopt(sock, SOL_SOCKET, SO_SNDBUF,(void*) &writeBufferSize,sizeof(int)) == -1)
            printf ("Error setting send buffer\n");
        if (connect(sock,(sockaddr *)&serv_addr,sizeof(serv_addr)) == -1 )  { 
            perror ("Connection error\n");  
            peerDisconnected = true; 
            rshutdown = true;
            wshutdown= true;            
        }
        else { 
            socklen_t my_sock_size = sizeof(struct sockaddr);
            getsockname (sock,(struct sockaddr *)&myAddr,&my_sock_size);
            strcpy(my_address , inet_ntoa(myAddr.sin_addr));
            rshutdown = false; 
            wshutdown= false; 
        }
    }
}
char * TCPSocket::getRemoteAddress() { return remote_address; }

char * TCPSocket::getMyAddress() {return my_address;}

int TCPSocket::readFromSocket (char * buffer, int maxBytes ) {
    if ( buffer != NULL ) {
            memset (buffer,0,maxBytes); 
            int read = 0;
            read = recv (sock,buffer,maxBytes,0); 
            return read; 
    }else return -1; 
}

int TCPSocket::readFromSocketWithTimeout (char * buffer, int maxBytes, long timeoutSec, long timeoutMilli)
{
    fd_set fds;
    int read =-1;  
    struct timeval tv; 
    tv.tv_sec = timeoutSec;
    tv.tv_usec = timeoutMilli;
    FD_ZERO(&fds);
    FD_SET(sock, &fds);
    int select_result =  select(sock+1, &fds, NULL, NULL, &tv);
    if ( select_result >= 0 ) 
    {
        if (FD_ISSET(sock, &fds))
        {
            int read = 0;
            read = recv (sock,buffer,maxBytes,0); 
            if ( rshutdown && wshutdown && read == 0 ) return -1;
            else return read; 
        }
        else if (select_result == 0 ) return 0; 
    } else perror("Error reading from socket: "); 
    return read;
}
int TCPSocket::writeToSocket (const char * buffer, long maxBytes ) 
{
    if ( buffer != NULL ) { 
        int wrote = 0;
        wrote = send (sock,buffer,maxBytes,0); 
        stream_out_size += wrote;
        if ( wrote != maxBytes) perror("socket error"); 
        return wrote; 
    } else return -1; 
}
long TCPSocket::getStreamOutSize() {return stream_out_size;} 
void TCPSocket::setPeerDisconnected(bool value){peerDisconnected = value;} 
bool TCPSocket::isPeerDisconnected() {return peerDisconnected;} 
void TCPSocket::shutDownRead ( ) 
{
    if ( !rshutdown)
    {
        shutdown (sock,SHUT_RD);
        rshutdown = true;
    }
}
void TCPSocket::shutDownWrite ()
{
    if ( !wshutdown)
    {
        shutdown (sock,SHUT_WR);
        wshutdown = true;
    }
}
void TCPSocket::shutDown ( ) 
{
        shutDownRead ();
	shutDownWrite();
}

TCPSocket::~TCPSocket ( ) 
{
        shutDown(); 
        close (sock); 
}
