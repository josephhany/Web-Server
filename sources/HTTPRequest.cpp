#include "HTTPRequest.h" 
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void HTTPRequest::addToHeaderMap(string header_item)//Parsing the string and adding the keys, values to the header map
{
    cout<<"header: "<<header_item<<endl;
    stringstream iss(header_item); 
    string key="";
    string value = ""; 
    getline(iss,key,':'); 
    getline(iss,value,'\r'); 
    trim(value);
    header[key] = value; 
}

HTTPRequest::HTTPRequest(TCPSocket * p_tcpSocket)
{
    tcpSocket = p_tcpSocket; 
}


void HTTPRequest::readAndParse(string initial_header)//Reading the header  sent and parsing it
{
    char buffer[1024];
    memset (buffer,1024,0);
    string http_stream=initial_header; 
    for ( ;http_stream.find("\r\n\r\n") ==std::string::npos; )//Reading until the header ends
    { 
        tcpSocket->readFromSocket(buffer,1023);//reading into buffer
        http_stream +=buffer;//adding into httpstream
        memset (buffer,0,1024);//
    }
    stringstream iss(http_stream);//parsing httpstream 
    getline(iss,method,' '); //Getting until the first space and i is the method
    getline(iss,resource,' ');//Until the second space is the resource
    cout << "resouce: " <<resource << endl;
    getline(iss,protocol,'\n');
    protocol.pop_back();

    string line = " ";
    for (;!line.empty();)
    {
        getline(iss,line,'\n');
        line.pop_back(); 
        if ( !line.empty()) addToHeaderMap(line); 
    }
    getline(iss,line,'\n'); 
    body = line;

}
string HTTPRequest::getResource ()
{
    return resource;//getting the resource
}
string HTTPRequest::getMethod(){
return method;
}

string HTTPRequest::getHeaderValue(string header_item_name)
{
    return header[header_item_name];//Getting headervalue of a certain item name
}

string & HTTPRequest::getBody()
{
    return body;//getting the body
}
HTTPRequest::~HTTPRequest(){}
