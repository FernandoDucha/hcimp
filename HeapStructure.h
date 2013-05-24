/* 
 * File:   HeapStructure.h
 * Author: fernando
 *
 * Created on 18 de Maio de 2013, 10:22
 */

#ifndef HEAPSTRUCTURE_H
#define	HEAPSTRUCTURE_H
#include <gmpxx.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
template <class type> class HeapStructure { 
public:
    HeapStructure();
    HeapStructure(HeapStructure<type> & Orig);
    mpz_class Insert(type  data);
    type getMax();
    void print();
    virtual ~HeapStructure();
    int GetPos() const;
    int size(){
        return pos;
    }
    mpz_class pick_max(){
        return heap[1];
    }
    type  GetHeap(ulong i) const;
    vector<type> & GetHeap();
    HeapStructure<type> & operator=(HeapStructure<type> & rhs);
    mpz_class valueMax(){
        return heap[1];
    }
private:
    void FixDown(int k , int N);
    void FixUp(int k);
    int pos;
    vector<type> heap;
    
};
template <class type> HeapStructure<type>::HeapStructure(){
    heap.push_back(mpz_class(-1));
    pos=0;
}
template <class type> HeapStructure<type>::HeapStructure(HeapStructure<type> & Orig){
    pos=Orig.GetPos();
    heap=Orig.GetHeap();
}
template <class type>HeapStructure<type>::~HeapStructure() {
//    delete [] heap;
//    heap=NULL;
}

template <class type> int HeapStructure<type>::GetPos() const {
    return pos;
}
template <class type> type HeapStructure<type>::GetHeap(ulong i) const {
    return heap[i];
}
template <class type> vector<type> & HeapStructure<type>::GetHeap() {
    return heap;
}
template <class type> inline void HeapStructure<type>::FixDown(int k , int N) {
    while(2*k<=N){
        int j=2*k;
        if((j<N)&&(heap[j]<heap[j+1])){
            j++;
        }
        if(!(heap[k]<heap[j])){
            break;
        }
        type temp = heap[k];
        heap[k]= heap[j];
        heap[j]=temp;
        k=j;
    }
}
template <class type> inline void HeapStructure<type>::FixUp(int k) {
    while(k>1&&heap[k/2]<heap[k]){
        type temp = heap[k];
        heap[k]= heap[k/2];
        heap[k/2]=temp;
        k/=2;
    }
}
template <class type> inline mpz_class HeapStructure<type>::Insert(type data){
    heap.push_back(data);
    pos++;
    FixUp(pos);
    return data;
}
template <class type> inline type HeapStructure<type>::getMax(){
   type temp=heap[1];
   heap[1]=heap[pos];
   heap[pos]=temp;
   pos--;
  // print();
   FixDown(1,pos);
 /// print();
   type ret = heap[pos+1];
   heap.pop_back();
   return ret;   
}
template <class type> inline void HeapStructure<type>::print(){
   for(int i=1;i<=pos;i++){
       cout<<i<<":"<<log2(heap[i])<<endl;
   }   
}
template <class type>HeapStructure<type> & HeapStructure<type>::operator=(HeapStructure<type> & rhs){
    this->heap.clear();
    this->pos=rhs.GetPos();
    this->heap=rhs.GetHeap();
    return * this;
}
typedef HeapStructure<mpz_class> mpz_heap;
#endif	/* HEAPSTRUCTURE_H */

