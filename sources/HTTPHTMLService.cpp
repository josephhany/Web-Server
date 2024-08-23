#include "HTTPHTMLService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

HTTPHTMLService::HTTPHTMLService(FileCache * p_fileCache,bool p_clean_cache, string p_file_type )
        :HTTPService(p_fileCache,p_clean_cache) {
		file_type=p_file_type;
	} 
bool HTTPHTMLService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{
    try { 
        cout << "HTML called" <<endl;
        string resource = p_httpRequest->getResource();//Getting the resource
        FileCacheItem * fileCacheItem = fileCache->getFile(resource); //Getting the file 
        fileCacheItem = fileCacheItem->fetchContent();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");//Getting the value of the header
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");//Making a new response object;
        httpResponseHeader->setHeader("Content-Type",/*"image/webp"*/file_type); //setting a header
        httpResponseHeader->setHeader("Last-Modified",fileCacheItem->getLastUpdateTime());//setting a header
        httpResponseHeader->setHeader("Connection","close");//setting a header
        httpResponseHeader->setHeader("Content-Length",to_string(fileCacheItem->getSize()));//setting a header
        httpResponseHeader->respond();//Responding 
        p_tcpSocket->writeToSocket(fileCacheItem->getStream(),fileCacheItem->getSize());//Writing to socket
        delete (httpResponseHeader);
        delete (fileCacheItem);
        return true;
    } 
    catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)
    { 
        httpNotFoundExceptionHandler.handle(p_tcpSocket); 
        return false;
    }
}
HTTPService * HTTPHTMLService::clone ()
{
    return new HTTPHTMLService(fileCache,false);  
}
HTTPHTMLService::~HTTPHTMLService() 
{
}
