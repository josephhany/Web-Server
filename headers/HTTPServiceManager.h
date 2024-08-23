#ifndef HTTPSERVICEMANAGER_H
#define HTTPSERVICEMANAGER_H
#include "HTTPHTMLService.h"

class HTTPServiceManager
{
    private:
        std::map <string,HTTPService *> services;
    public:
        HTTPServiceManager();
        HTTPService * getService (string p_resource);
        ~HTTPServiceManager();
};


#endif