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
    type Insert(type  data);
//    type InsertDelayed(type  data);
    type getMax();
//    type getMaxDelayed();
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
//    void heapfyFromInit(int i );
    int pos;
    int init;
    vector<type> heap;  
};
//template <class type> void HeapStructure<type>::heapfyFromInit(int i){
//    int r = 2*i+1;
//    int l = 2*i;
//    int l1=l+init-1;
//    int r1=r+init-1;
//    int i1=init;
//    int Largest;
//    if((l1<=pos)&&(heap[l1]>heap[i1])){
//        Largest=l;
//    }else{
//        Largest=i;
//    }
//    if((r1<=pos)&&(heap[r1]>heap[Largest+init])){
//        Largest=l;
//    }
//    if(Largest!=i){
//        type temp = heap[i1];
//        heap[i1]=heap[Largest+init];
//        heap[Largest+init]=temp;
//        print();
//        heapfyFromInit(Largest);
//    }
//}
template <class type> HeapStructure<type>::HeapStructure(){
    heap.push_back(type(-1));
    pos=0;
    init=1;
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
    while(k>init&&heap[k/2]<heap[k]){
        type temp = heap[k];
        heap[k]= heap[k/2];
        heap[k/2]=temp;
        k/=2;
    }
}
template <class type> inline type HeapStructure<type>::Insert(type data){
    heap.push_back(data);
    pos++;
    FixUp(pos);
    return data;
}
//template <class type> inline type HeapStructure<type>::InsertDelayed(type data){
//    init--;
//    heap[init]=data;
//    heapfyFromInit(1);
//    return data;
//}
template <class type> inline type HeapStructure<type>::getMax(){
   type temp=heap[1];
   heap[1]=heap[pos];
   heap[pos]=temp;
   pos--;
   FixDown(1,pos);
   type ret = heap[pos+1];
   heap.pop_back();
   return ret;   
}
template <class type> inline void HeapStructure<type>::print(){
   for(int i=init;i<=pos;i++){
       cout<<i<<":"<<log2(heap[i])<<endl;
   }   
}
template <class type>HeapStructure<type> & HeapStructure<type>::operator=(HeapStructure<type> & rhs){
    this->heap.clear();
    this->pos=rhs.GetPos();
    this->heap=rhs.GetHeap();
    return * this;
}
//template <class type> inline type HeapStructure<type>::getMaxDelayed(){
//   type ret = heap[init];
//   init++;
//   return ret;  
//}
typedef HeapStructure<mpz_class> mpz_heap;
#endif	/* HEAPSTRUCTURE_H */

