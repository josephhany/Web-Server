#include "heap.h"


template <typename ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::incCurrentSize () {
    if ( currentSize == maxSize-1) {
        maxSize *= 2;
        items = (ITEM *) realloc(items, maxSize*sizeof(ITEM));
    }
    currentSize ++;
}

template <typename ITEM,int initial_size>
bool BinaryHeap<ITEM,initial_size>::isEmpty () {
    if ( currentSize > 0) return false;
    else return true;
}

template <typename ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::percolateDown(int hole) {
    int child;
    ITEM tmp = std::move(items[hole]);
    for (;hole *2 <= currentSize ;hole=child) {
        child = hole * 2;
        if ( child != currentSize && items[child+1] < items[child]) child++;
        if (items[child] < tmp)
            items[hole] = std::move(items[child]);
        else break;
    }
    items[hole] = std::move(tmp);
}

template <typename ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::buildHeap () {
    for ( int i = currentSize/2;i > 0 ; i--) percolateDown(i);
}
template <typename ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::BinaryHeap ()  {
    maxSize = initial_size+1;
    currentSize = 0;
    items = (ITEM *) calloc(maxSize,sizeof(ITEM));
}
template <typename ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::BinaryHeap(ITEM * p_items,int p_size) {
    maxSize = initial_size+1;
    if ( maxSize < p_size+1) maxSize = p_size+1;
    currentSize = 0;
    items = (ITEM *) calloc(maxSize,sizeof(ITEM));
    for ( int i = 0 ; i < p_size ; i ++) items[++currentSize] = p_items[i];
    buildHeap();
}

template <typename ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::insert(const ITEM & p_item) {
    incCurrentSize();
    int hole = currentSize;
    items[0] = std::move(p_item);
    for (; p_item <  items[hole/2]; hole /=2)
			items[hole] = std::move(items[hole/2]);
    items[hole] = std::move(items[0]);
}
template <typename ITEM,int initial_size>
bool BinaryHeap<ITEM,initial_size>::deleteMin(ITEM &  p_item) {
    if ( isEmpty()) return false;
    p_item = std::move(items[1]);
    items[1] = std::move(items[currentSize -- ]);
    percolateDown(1);
    return true;
}

template <typename ITEM,int initial_size>
ITEM BinaryHeap<ITEM,initial_size>::min() {
	return items[1];
}

template <typename ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::print() {
    int j = 0 ;
    int l = 1;
    for ( int i = 0 ; i < currentSize ; i ++) {
        cout << items[i+1] << "\t" ;
        if (i == j ) {
            cout << endl;
            j += l * 2;
            l *= 2;
        }
    }
}

template <typename ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::~BinaryHeap ()  {
    free (items);
}

