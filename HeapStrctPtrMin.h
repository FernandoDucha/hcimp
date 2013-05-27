/* 
 * File:   HeapStrctPtrMin.h
 * Author: fernando
 *
 * Created on May 26, 2013, 8:20 PM
 */

#ifndef HEAPSTRCTPTRMIN_H
#define	HEAPSTRCTPTRMIN_H
#include "HeapStrctPtr.h"
class HeapStrctPtrMin : public HeapStrctPtr {
public:
    HeapStrctPtrMin(){}
    virtual ~HeapStrctPtrMin();
    mpz_class Insert(mpz_heap_elem * ptr);
    mpz_heap_elem * getMax();
    HeapStrctPtrMin& operator=(HeapStrctPtr& rhs);    
private:

};
inline HeapStrctPtrMin::~HeapStrctPtrMin() {
 
}
inline mpz_heap_elem* HeapStrctPtrMin::getMax(){
   mpz_heap_elem* temp=heap[1];
   heap[1]=heap[pos];
   heap[pos]=temp;
   pos--;
  // print();
   FixDown(1,pos);
 /// print();
   mpz_heap_elem* ret = heap[pos+1];
   heap.pop_back();
   return ret;   
}
inline mpz_class HeapStrctPtrMin::Insert(mpz_heap_elem * data){
    heap.push_back(data);
    pos++;
    FixUp(pos);
    return data->getId();
}
inline HeapStrctPtrMin& HeapStrctPtrMin::operator=(HeapStrctPtr& rhs){
    pos=rhs.GetPos();
    heap=rhs.GetHeap();
}    

#endif	/* HEAPSTRCTPTRMIN_H */

