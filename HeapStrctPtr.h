/* 
 * File:   HeapStructure.h
 * Author: fernando
 *
 * Created on 18 de Maio de 2013, 10:22
 */

#ifndef HEAPSTRCTPTR_H
#define	HEAPSTRCTPTR_H
#include "BasicTypes_heap.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
class HeapStrctPtr { 
public:
    HeapStrctPtr();
    HeapStrctPtr(int nMax);
    HeapStrctPtr(HeapStrctPtr & Orig);
    mpz_class Insert(mpz_heap_elem*  data);
    mpz_heap_elem* getMax();
    void print();
    virtual ~HeapStrctPtr();
    int GetPos() const;
    void printRefs();
    int size(){
        return pos;
    }
    mpz_heap_elem * pick_max(){
        return heap[1];
    }
    mpz_heap_elem*  GetHeap(ulong i) const;
    vector<mpz_heap_elem*> & GetHeap();
    HeapStrctPtr & operator=(HeapStrctPtr & rhs);
    mpz_class valueMax(){
        return heap[1]->getId();
    }
private:
    void FixDown(int k , int N);
    void FixUp(int k);
    int pos;
    vector<mpz_heap_elem*> heap;
    
};
typedef HeapStrctPtr mpz_heap_ptr;

inline void HeapStrctPtr::FixDown(int k , int N) {
    while(2*k<=N){
        int j=2*k;
        if((j<N)&&(*heap[j]<*heap[j+1])){
            j++;
        }
        if(!(*heap[k]<*heap[j])){
            break;
        }
        mpz_heap_elem* temp = heap[k];
        heap[k]= heap[j];
        heap[j]=temp;
        k=j;
    }
}
inline void HeapStrctPtr::FixUp(int k) {
    while(k>1&&*heap[k/2]<*heap[k]){
        mpz_heap_elem* temp = heap[k];
        heap[k]= heap[k/2];
        heap[k/2]=temp;
        k/=2;
    }
}
inline mpz_class HeapStrctPtr::Insert(mpz_heap_elem* data){    
    heap.push_back(data);
    (*data)++;
    pos++;
 //  print();
 //   cout<<heap[pos]->getId()<<endl;
    FixUp(pos);
    return data->getId();
}
inline mpz_heap_elem* HeapStrctPtr::getMax(){
   mpz_heap_elem* temp=heap[1];
   heap[1]=heap[pos];
   heap[pos]=temp;
   pos--;
  // print();
   FixDown(1,pos);
 /// print();
   mpz_heap_elem* ret = heap[pos+1];
   (*ret)--;
   heap.pop_back();
   return ret;   
}
inline void HeapStrctPtr::print(){
   for(int i=1;i<=pos;i++){
       cout<<i<<":"<<log2(heap[i]->getId())<<"---"<<heap[i]->_ref()<<"---"<<(bool)heap[i]->isOrig()<<endl;
   }   
}
inline void HeapStrctPtr::printRefs(){
   for(int i=1;i<=pos;i++){
       cout<<i<<":"<<heap[i]->_ref()<<endl;
   }   
}
#endif	/* HEAPSTRUCTURE_H */

