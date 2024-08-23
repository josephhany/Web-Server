#ifndef HTTPFORMSERVICE_H
#define HTTPFORMSERVICE_H
#include "HTTPService.h"
class HTTPFORMService: public HTTPService
{
    protected:
        std::map <string,string> form_data;
        std::map <string,string> raw_form_data;
        string urldecode(string & urlencoded);
        void add_to_form_data(string & form_field);
        void parse_data (HTTPRequest * p_httpRequest);
        string compose_reply();
    public:
        HTTPFORMService();
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPFORMService();
};

#endif // HTTPFORMSERVICE_H
