#include "FileCache.h"
#include "heap.cpp"

FileCache::FileCache(string p_root, int p_max) { root = p_root;max=p_max; }
FileCacheItem * FileCache::getFile(string p_file_name)
{//Add priority queue, and modify map, here and in the constructor

    string file_name = root+p_file_name;

    if ( cache[file_name] == NULL ) {
	if(cache.size()==max){
		BinaryHeap<FileCacheItem*, 5> heap;
		for(auto it=cache.begin();it!=cache.end();it++)
			heap.insert(it->second);
		cache.erase(heap.min()->file);
		cout<<heap.min()->file<<" was removed from Cache "<<endl;
	}
        FileCacheItem * fileCacheItem = new FileCacheItem(file_name);
        cache[file_name] = fileCacheItem;
	//heap.insert(fileCacheItem);
        cout<<"not from cache"<<endl;
        return fileCacheItem;
    }
    cout<<"from cache"<<endl;
    cache[file_name]->incCount();
    return cache[file_name];


}
FileCache::~FileCache () { // Destructor
    for_each (cache.begin(),cache.end(),[](const std::pair<string,FileCacheItem *>& it) -> bool {
            FileCacheItem * fileCacheItem = std::get<1>(it); 
            delete(fileCacheItem); 
            return true;
       });
}
