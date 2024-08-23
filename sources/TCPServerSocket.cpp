#include "TCPServerSocket.h"
// Constructor
TCPServerSocket::TCPServerSocket (const char * _address, int _port, int _backlog )//Constructor for making a new TSP server socket
{
	if ( _address != NULL && strcmp (_address,"") != 0)
	{
		address = (char *) calloc (strlen(_address)+1,sizeof(char));//address
		memset (address,0,strlen(_address)+1);
		strcpy (address,_address);
	}
	else address= NULL;
	port = _port; 
	backlog=_backlog; 
}
bool TCPServerSocket::initializeSocket ( ) 
{
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) return false;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);//Adding the port to the socket
        if ( address != NULL ) 
        {
            if (strcmp (address,"") !=0 ) serverAddr.sin_addr.s_addr = inet_addr(address);
            else serverAddr.sin_addr.s_addr = INADDR_ANY;
        } 
        else serverAddr.sin_addr.s_addr = INADDR_ANY;
        bzero(&(serverAddr.sin_zero), 8); 

        int flag = 0;
        int result = setsockopt(sock,
                          IPPROTO_TCP,
                          TCP_NODELAY,
                          (char *) &flag,
                          sizeof(int));
        if ( result < 0 )
        {
	       close (sock);
      	       sock = -1;
       	       return false;
    	}

         int sock_opt = 1;
         result = setsockopt(sock,
                           SOL_SOCKET,
                           SO_REUSEADDR,
                           (void *)&sock_opt,sizeof (sock_opt));
        if ( result < 0 )
 	{
 		close (sock);
 		sock = -1;
 		return false;
 	}
        if (::bind(sock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)//binding
        {
		close (sock);
		sock = -1;
		return false;
	}

        if (listen(sock, backlog) == -1)
        {
		close (sock);
		sock = -1;
		return false;
	}
        return true;
}


TCPSocket * TCPServerSocket::getConnection (int timeoutSec, int timeoutMilli,int readBufferSize,int writeBufferSize )
{//Getting a new connection
	socklen_t sin_size = sizeof(clientAddr);
        int newsock = 0;
	if (timeoutSec==0 && timeoutMilli == 0 )
		newsock = accept(sock, (struct sockaddr *)&clientAddr,&sin_size);//accepting a connection from client
	else { 
                fd_set fds; 
                struct timeval tv;
		tv.tv_sec = timeoutSec;
		tv.tv_usec = timeoutMilli;
		FD_ZERO(&fds);
		FD_SET(sock, &fds);
		select(sock+1, &fds, NULL, NULL, &tv);
		if (FD_ISSET(sock, &fds)) 
			newsock = accept(sock, (struct sockaddr *)&clientAddr,&sin_size);//accepting a connection from client
	}
        if ( newsock < 1 ) 
        {   
            perror("ERROR on accept");
            return NULL;
        }
        else{ 
                TCPSocket * tcpSocket = new TCPSocket(newsock,(char *)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,readBufferSize,writeBufferSize);
                return tcpSocket;
        }
        
	return NULL;
}
TCPServerSocket::~TCPServerSocket ( ) 
{
	shutdown (sock,SHUT_RDWR);
	close (sock);
	if ( address != NULL ) free (address); 
}
