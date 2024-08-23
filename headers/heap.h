#include <iostream>

using namespace std;

template <typename ITEM,int initial_size>
class BinaryHeap {
    protected:
        ITEM * items;
        int maxSize,currentSize;
        void incCurrentSize ();
        bool isEmpty ();
        void percolateDown(int hole);
        void buildHeap();
    public:
        BinaryHeap ();
        BinaryHeap (ITEM * p_items, int p_size);
        void insert (const ITEM & p_item );
        bool deleteMin(ITEM &  p_item);
        void print ();
ITEM min();
        virtual ~BinaryHeap();
};
