/* 
 * File:   BasicTypes_heap.h
 * Author: fernando
 *
 * Created on 13 de Maio de 2013, 14:18
 */

#ifndef BASICTYPES_HEAP_H
#define	BASICTYPES_HEAP_H
#include <gmpxx.h>
#include <algorithm>
#include <vector>
#include "BasicFunctions.h"
#include "HeapStructure.h"
class num_elem_mpz_heap {
private:
    mpz_class * id;
    ulong ref;
    bool ori;
public:
    num_elem_mpz_heap(mpz_class  n):ref(1),ori(true) {
        id = new mpz_class(n);
    }
    num_elem_mpz_heap() {
        id =NULL;
        ref=0;
    }
    mpz_class getId() const {
        return *id;
    }
    ~num_elem_mpz_heap(){
        if(!ref){
            delete id;
        }
    }
    void upRef(){
        ref++;
    }
    void downRef(){
        ref--;
    }
    num_elem_mpz_heap * copyRef(){
        ref++;
        return this;
    }
    static inline void tryDeleting(num_elem_mpz_heap * candidate){
        if(!candidate->_ref()){
            delete candidate;
        }
    }

    ulong _ref() const {
        return ref;
    }

    void Original(bool b=false) {
        ori=b;
    }

    bool isOrig() const {
        return ori;
    }
    num_elem_mpz_heap & operator++(int a){
        ref++;
    }
    num_elem_mpz_heap & operator--(int a){
        ref--;
    }
};

typedef num_elem_mpz_heap  mpz_heap_elem;
typedef mpz_heap_elem* mpz_heap_elem_ptr;
mpz_heap_elem & operator-(mpz_heap_elem & A,mpz_heap_elem & B);
mpz_class & operator-(mpz_class & A,mpz_heap_elem & B);

mpz_heap_elem & operator+(mpz_heap_elem & A,mpz_heap_elem & B);
bool compHeapElem(mpz_heap_elem * A, mpz_heap_elem * B);
bool operator<(mpz_heap_elem & A,mpz_heap_elem & B);
bool operator>(mpz_heap_elem & A,mpz_heap_elem & B);
bool operator<=(mpz_heap_elem & A,mpz_heap_elem & B);
bool operator>=(mpz_heap_elem & A,mpz_heap_elem & B);
bool operator==(mpz_heap_elem & A,mpz_heap_elem & B);
bool operator!=(mpz_heap_elem & A,mpz_heap_elem & B);
//typedef vector<mpz_heap_elem*> vec_heap_elem;


#endif	/* BASICTYPES_HEAP_H */