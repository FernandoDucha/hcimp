/* 
 * File:   HashExtended.h
 * Author: fernando
 *
 * Created on 21 de Maio de 2013, 07:54
 */

#ifndef HASHEXTENDED_H
#define	HASHEXTENDED_H
#include <vector>
#include <set>
#include "Mpz_Heap_Node_Template.h"
using namespace std;
class HashExtended {
    typedef mpz_node_bfs * heap_node_p;
public:
    HashExtended(int maxDepth,int maxElements);    
    virtual ~HashExtended();
    void put(mpz_node_bfs * novo);
    void nextCyle();
    int getNElem() const;
    ulong sizeHeight(int i);
    mpz_node_bfs * peekFirst();
    int getLastHeight() const;
    mpz_node_bfs ** getHeightVector(int h){
        return hash[h];
    }
    ulong getHeightCoun(int h){
        return auxcount[h];
    }
    
private:
    bool contains(vector<mpz_heap_elem*> v, mpz_heap_elem * elem);
    heap_node_p ** hash;
    ulong * count,*auxcount;
    int maxSize,searchSpace;
    int nElem;
    int maxElem;
};

#endif	/* HASHEXTENDED_H */

