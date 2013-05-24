#include "BasicTypes_heap.h"
mpz_heap_elem & operator-(mpz_heap_elem & A,mpz_heap_elem & B){
    mpz_heap_elem * a = new mpz_heap_elem(A.getId()-B.getId());
    return *a;
}

mpz_heap_elem & operator+(mpz_heap_elem & A,mpz_heap_elem & B){
    mpz_heap_elem * a = new mpz_heap_elem(A.getId()+B.getId());
    return *a;
}
bool compHeapElem(mpz_heap_elem * A, mpz_heap_elem * B){
    return A->getId()<B->getId();
}
bool operator<(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()<B.getId());
}

bool operator>(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()>B.getId());
}
bool operator<=(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()<=B.getId());
}

bool operator>=(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()>=B.getId());
}
bool operator==(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()==B.getId());
}

bool operator!=(mpz_heap_elem & A,mpz_heap_elem & B){
    return (A.getId()!=B.getId());
}
mpz_class & operator-(mpz_class & A,mpz_heap_elem * B){
    A-=B->getId();
    return A;
}