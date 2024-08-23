#include "HTTPServiceManager.h"
#include "HTTPNotAcceptableExceptionHandler.h"
#include "HTTPFormService.h"
#define WEB_CACHE_ROOT  "./www"
HTTPServiceManager::HTTPServiceManager()
{	
    services ["gif"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"image/gif");//New service for gif images     
    services ["jpg"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"image/jpeg");//New service for jpeg images               
    services ["png"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"image/png");//New service for png images               
    services ["html"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"text/html");//New service for html files               
    services ["pdf"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"application/pdf");//New service for files with pdf format               
    services ["txt"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"text/plain");//New service for text               
    services ["mp3"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"audio/mp3");    //New service for mp3
    //services ["xml"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT),true,"application/xml");
    services ["js"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"text/javascript");    //New service for gif javascript
    services ["webm"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"video/webm");//New service for webcam video    
    services ["ogv"] = new HTTPHTMLService(new FileCache(WEB_CACHE_ROOT,3),true,"video/ogg");    //New service for ogg videos
    services ["form"] = new HTTPFORMService();    //New service for forms
    services ["xml"] = new HTTPFORMService();//New service for xml
}

HTTPService * HTTPServiceManager::getService (string p_resource)//A function that returns the service in the resource after parsing the resource
{
cout << "From HTTPServiceManager resource: " << p_resource <<endl;
    string ext = p_resource.substr(p_resource.find_last_of(".") + 1);
    if ( services[ext]==NULL)
    {
        string base_name = p_resource.substr(p_resource.find_last_of("/") + 1);
      
        if(base_name.find("?")!=-1){
            base_name=base_name.substr(0,base_name.find("?"));
        }

        cout << "Base name: " << base_name <<endl;
        
        if (services[base_name]==NULL) throw (HTTPNotAcceptableExceptionHandler());
        else return services[base_name]->clone();
    }
    else return services[ext]->clone(); 
}

HTTPServiceManager::~HTTPServiceManager()
{
    for_each (services.begin(),services.end(),[](const std::pair<string,HTTPService *>& it) -> bool {
        HTTPService * httpService = std::get<1>(it);
        delete(httpService);
        return true;
   });
}
