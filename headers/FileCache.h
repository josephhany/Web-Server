#ifndef FILECACHE_H
#define FILECACHE_H
#include "FileCacheItem.h"

class FileCache
{
    private:
        std::map <string,FileCacheItem *> cache;
        string root;
        //BinaryHeap <FileCacheIem, 7> minHeap; 
        int max;    
    public:
        FileCache(string p_root, int p_max); 
        FileCacheItem * getFile(string p_file_name);
        ~FileCache (); 
};

#endif
