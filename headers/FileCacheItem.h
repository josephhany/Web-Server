#ifndef FILECACHEITEM_H
#define FILECACHEITEM_H

#include "includes.h"
class FileCacheItem
{
    private:
        string file_name;
        char * cache_item_stream;
        long cache_item_size;
        struct stat cache_item_stat; 
        char time_string[100]; 
        void load ();
        mutex fetch_mutex;
        mutex assign_mutex;
        int visitedCount;
    public:
        FileCacheItem();
        FileCacheItem(string p_file_name);
        FileCacheItem * fetchContent();
        char * getLastUpdateTime ();
        char * getStream();
        long getSize();
        void operator=(const FileCacheItem & p_fileCacheItem);
        ~FileCacheItem();
string file;
void incCount();

bool operator < (const FileCacheItem& f);
bool operator > (const FileCacheItem& f);

};

#endif
