#include "FileCacheItem.h"
#include "HTTPNotFoundExceptionHandler.h"
#include <sys/stat.h>

// Load file content of the target file
void FileCacheItem::load ()
{
    FILE * f = fopen (file_name.c_str(),"r");
    if ( f ==NULL) throw(HTTPNotFoundExceptionHandler());
    fseek(f,0,2);
    cache_item_size = ftell(f); 
    fseek(f,0,0);
    if ( cache_item_stream != NULL) free (cache_item_stream);
    cache_item_stream = (char *) calloc(cache_item_size,sizeof(char));
    fread (cache_item_stream,1,cache_item_size,f);
    stat(file_name.c_str(), &cache_item_stat);
    fclose(f);
}

FileCacheItem::FileCacheItem()
{
    file_name = ""; 
    cache_item_stream = NULL; 
//HeapID=1;
visitedCount=1;
}
// Parameterized Constructor
FileCacheItem::FileCacheItem(string p_file_name)
{
    file_name = p_file_name; 
    cache_item_stream = NULL; 
    load(); 
//HeapID=1;
visitedCount=1;
file=p_file_name;
}
FileCacheItem * FileCacheItem::fetchContent()
{
    fetch_mutex.lock();
    try{
        struct stat attrib;
        if (stat(file_name.c_str(), &attrib) == -1)
        {
            fetch_mutex.unlock();
            throw(HTTPNotFoundExceptionHandler());
        }
        if ( attrib.st_mtime != cache_item_stat.st_mtime ) load(); 
        FileCacheItem * fileCacheItem = new FileCacheItem();
        *fileCacheItem = *this; 
        fetch_mutex.unlock(); 
        return fileCacheItem; 
    }catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)
    { 
            fetch_mutex.unlock(); 
            throw(httpNotFoundExceptionHandler); 
            return NULL;
    }
}

char * FileCacheItem::getLastUpdateTime ()
{
    memset (time_string,0,100); 
    struct tm tm = *gmtime(((time_t *) &cache_item_stat.st_mtime));
    strftime(time_string, 100, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return time_string; 
}
char * FileCacheItem::getStream()
{
    return cache_item_stream; 
}
long FileCacheItem::getSize()
{
    return cache_item_size; 
}

void FileCacheItem::operator=(const FileCacheItem & p_fileCacheItem)
{
    assign_mutex.lock();
    if ( cache_item_stream != NULL) free (cache_item_stream);
    cache_item_stream = (char *) calloc(p_fileCacheItem.cache_item_size,sizeof(char));
    cache_item_size=p_fileCacheItem.cache_item_size;
    cache_item_stat = p_fileCacheItem.cache_item_stat;
    memcpy (cache_item_stream,p_fileCacheItem.cache_item_stream,cache_item_size);
    assign_mutex.unlock(); 
}

bool FileCacheItem::operator > (const FileCacheItem& f)
{
    return (visitedCount > f.visitedCount);
        
}

bool FileCacheItem::operator < (const FileCacheItem& f)
{
    return (visitedCount < f.visitedCount);
        
}

void FileCacheItem::incCount(){
	visitedCount++;
}

FileCacheItem::~FileCacheItem()
{
    if ( cache_item_stream != NULL ) free (cache_item_stream);
}
