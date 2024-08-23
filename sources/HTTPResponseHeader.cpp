
#include "HTTPResponseHeader.h"
HTTPResponseHeader::HTTPResponseHeader(TCPSocket * p_tcpSocket,string p_status,int p_status_code,string p_protocol):
tcpSocket(p_tcpSocket),status(p_status),status_code(p_status_code),protocol(p_protocol)
{
    
}
void HTTPResponseHeader::setHeader(string p_key,string p_value)
{
    header[p_key]=p_value; 
}

void HTTPResponseHeader::respond ()
{
   
    string header_string = protocol;
    header_string += " ";
    header_string += to_string(status_code);
    header_string += " ";
    header_string += status;
    header_string += "\r\n"; //Filling the response header with status and protocol
    for_each (header.begin(),header.end(),[&header_string](const std::pair<string,string>& it) -> bool {//Filling string header with all the headers in the map called header
            header_string +=  std::get<0>(it); 
            header_string += ": " ;
            header_string += std::get<1>(it);
            header_string += "\r\n";
            return true; 
    });
    header_string += "\r\n"; 
    tcpSocket->writeToSocket(header_string.c_str(),header_string.length());//Writing the header to the socket
}
// Destructor
HTTPResponseHeader::~HTTPResponseHeader(){}
