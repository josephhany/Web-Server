#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "HTTPTransaction.h"

class GarbageCollector
{ 
    private:
        vector <HTTPTransaction *> http_transaction_store;
    public:
        GarbageCollector();
        void addHTTPTransaction(HTTPTransaction * p_http_transaction); 
        void cleanup();	
	    void terminate ();
        ~GarbageCollector(); 
};
#endif 
