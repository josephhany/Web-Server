#include "GarbageCollector.h"

GarbageCollector::GarbageCollector(){ }

void GarbageCollector::addHTTPTransaction(HTTPTransaction * p_httpTransaction) {
    http_transaction_store.push_back(p_httpTransaction);
}
void GarbageCollector::cleanup() {
    for (int i = 0 ; i < http_transaction_store.size(); )
    {
        if ( !http_transaction_store[i]->isRunning()) 
        {
            http_transaction_store[i]->waitForRunToFinish();
            HTTPTransaction * httpTransaction = http_transaction_store[i]; 
            delete (httpTransaction); 
            http_transaction_store.erase(http_transaction_store.begin()+i);
        }
        else i++; 
    }
}
void GarbageCollector::terminate() {
    for ( ; http_transaction_store.size() > 0; )
    {
            http_transaction_store[0]->waitForRunToFinish();
            HTTPTransaction * httpTransaction = http_transaction_store[0]; 
            delete (httpTransaction);
            http_transaction_store.erase(http_transaction_store.begin()); 
    }
}
GarbageCollector::~GarbageCollector()
{
    terminate(); 
}

