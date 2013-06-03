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
    bool prune(mpz_class min, ulong nPart);
    void SetSum(mpz_class sum);
    mpz_class GetSum() const;
private:
    mpz_class sum;
};
inline void HeapStrctPtrMin::SetSum(mpz_class sum) {
    this->sum = sum;
}
inline mpz_class HeapStrctPtrMin::GetSum() const {
    return sum;
}
inline bool HeapStrctPtrMin::prune(mpz_class min, ulong nPart){
    mpz_class max= pick_max()->getId();
    mpz_class factor= max-(sum-max)/(nPart-1);
    if(factor>=min){
        return true;
    }else{
        return false;
    }
}
inline HeapStrctPtrMin::~HeapStrctPtrMin() {
    pos=-1;
}

inline mpz_heap_elem* HeapStrctPtrMin::getMax(){
   mpz_heap_elem* temp=heap[1];
   heap[1]=heap[pos];
   heap[pos]=temp;
   pos--;
   FixDown(1,pos);
   mpz_heap_elem* ret = heap[pos+1];
   sum-=ret->getId();
   heap.pop_back();
   return ret;   
}
inline mpz_class HeapStrctPtrMin::Insert(mpz_heap_elem * data){
    heap.push_back(data);
    pos++;
    sum+=data->getId();
    FixUp(pos);
    return data->getId();
}
inline HeapStrctPtrMin& HeapStrctPtrMin::operator=(HeapStrctPtr& rhs){
    pos=rhs.GetPos();
    heap=rhs.GetHeap();
}    

#endif	/* HEAPSTRCTPTRMIN_H */

