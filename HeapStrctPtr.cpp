/* 
 * File:   HeapStructure.cpp
 * Author: fernando
 * 
 * Created on 18 de Maio de 2013, 10:22
 */

#include "HeapStrctPtr.h"


HeapStrctPtr & HeapStrctPtr::operator=(HeapStrctPtr & rhs){
    this->heap.clear();
    this->pos=rhs.GetPos();
    for(int i=1;i<=pos;i++){
        mpz_heap_elem * temp = rhs.GetHeap(i)->copyRef();
        heap.push_back(temp);
    }
    return * this;
}
HeapStrctPtr::HeapStrctPtr(){
    heap.push_back(new mpz_heap_elem(-1));
    pos=0;
}
HeapStrctPtr::HeapStrctPtr(HeapStrctPtr & Orig){
    heap.push_back(new mpz_heap_elem(-1));
    pos=Orig.GetPos();
    for(int i=1;i<=pos;i++){
        mpz_heap_elem * temp = Orig.GetHeap(i)->copyRef();
        heap.push_back(temp);
    }
//    print();
}
HeapStrctPtr::~HeapStrctPtr() {
    for(int i=pos;i>=0;i++){
        mpz_heap_elem * temp =heap[i];
        heap.pop_back();
        *temp--;
        mpz_heap_elem::tryDeleting(temp);
    }
}

int HeapStrctPtr::GetPos() const {
    return pos;
}
mpz_heap_elem* HeapStrctPtr::GetHeap(ulong i) const {
    return heap[i];
}
vector<mpz_heap_elem*> & HeapStrctPtr::GetHeap() {
    return heap;
}