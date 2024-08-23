#include "HTTPFormService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"
string HTTPFORMService::urldecode(string & urlencoded)
{
    string urldecoded=""; 
    for ( int i = 0 ;i < urlencoded.length();) 
    { 
        char c = urlencoded[i];
        if (i < urlencoded.length() - 2 && c == '%') { 
            char c1 = urlencoded[i + 1]; 
            char c2 = urlencoded[i + 2];
            c1 = tolower(c1);
            c2 = tolower(c2);
            if (isxdigit(c1) && isxdigit(c2)) {
                if (c1 <= '9') c1 = c1 - '0';
                else c1 = c1 - 'a' + 10;
                if (c2 <= '9') c2 = c2 - '0';
                else c2 = c2 - 'a' + 10;
                c = (char) ((16 * c1) + c2);
                if ( c == '\n') urldecoded += "<br/>";
                urldecoded+=c;
                i += 3;
            } else {
                urldecoded+= c;
                i++;
            }
        } else {
            if (c == '+') c = ' ';
            urldecoded+= c;
            i++;
        }        
    }
    return urldecoded;
}
void HTTPFORMService::add_to_form_data(string & form_field)
{
    string key=form_field.substr(0,form_field.find("="));//Parsing what is before = to be the key
string value=form_field.substr(form_field.find("=")+1,form_field.length());//Parsing what is after = to be the value

    value=value.substr(0,value.size()-1);
    //raw_form_data[key]=urldecode(value);
    form_data[key]=urldecode(value);//filling the map

}

void HTTPFORMService::parse_data (HTTPRequest * p_httpRequest)
{
    string data  = p_httpRequest->getBody();//getting the body of the request 
    
   // cout<<"body: "<<data<<endl;
    string field = ""; 
        
    if(data==""){//Get not post
        string url=  p_httpRequest->getResource().substr(p_httpRequest->getResource().find_last_of("/") + 1);//getting the url from the resource
        url=url.substr(url.find("?")+1,url.size());//parsing the url. After ? are the variables which will be sent to the addToFormData method         
        cout << "Full URL: " << url << endl; //all variables without ? and what is before it 
    
        while(url.find("=")!=-1){
            if(url.find("&")!=-1){//parse till &
                field=url.substr(0,url.find("&"));
                url=url.substr(url.find("&")+1,url.size());
            }else{//parse till end (Last field)
                field=url.substr(0,url.size());
                 url="";
           
            }
            
            cout << "Current field: " << field << endl;
 field += "&"; 
       
             add_to_form_data(field);
        }        
        
    }else{
    stringstream iss(data);
    for (;!iss.eof();)
    {
        getline(iss,field,'&'); 
        field += "&"; 
        add_to_form_data(field);
    }
    }
}

string HTTPFORMService::compose_reply()
{
    string reply = "<html><head><title>Form Engine</title></head><body>";
    reply += "<table width='100%' border='1'>";     

    for_each (raw_form_data.begin(),raw_form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {//Code for filling reply with the html table
            reply += "<tr><td>";
            reply += std::get<0>(it);
            reply += "</td><td>";
            reply += std::get<1>(it);
            reply += "</td></tr>";
            return true; 
    });
    reply += "</table><br/>";
    reply += "<table width='100%' border='1'>"; 
    for_each (form_data.begin(),form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {//Making html table
            reply += "<tr><td>";
            reply += std::get<0>(it);
            reply += "</td><td>";
            reply += std::get<1>(it);
            reply += "</td></tr>";
            return true; 
    });
    reply += "</table>";
    reply += "</body></html>";
    return reply;

}
HTTPFORMService::HTTPFORMService( )
        :HTTPService(NULL,false) {

} 

bool HTTPFORMService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{

     cout << "Form called" <<endl;
      
    parse_data(p_httpRequest);//Parsing the data sent by httpRequest
    string reply = compose_reply();//Composing reply to get the html page
    // you need to add code here
        string resource = reply;
 
       
   
        //FileCacheItem * fileCacheItem = fileCache->getFile(resource); 
        //fileCacheItem = fileCacheItem->fetchContent();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");//Setting headers here for the response
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
        httpResponseHeader->setHeader("Content-Type","text/html"); 
        httpResponseHeader->setHeader("Last-Modified","");
        httpResponseHeader->setHeader("Connection","close");
        httpResponseHeader->setHeader("Content-Length",to_string(resource.size()));

         
        if(p_httpRequest->getMethod()!="HEAD"){       
           httpResponseHeader->respond();
            p_tcpSocket->writeToSocket(resource.c_str(),resource.size());//If head is true this won't be done
   
         }
        //delete (httpResponseHeader);
        //delete (fileCacheItem);
        
}

HTTPService * HTTPFORMService::clone ()
{
    return new HTTPFORMService();  
}
HTTPFORMService::~HTTPFORMService(){}
