/* 
 * File:   PPN_Heap.h
 * Author: fernando
 *
 * Created on 13 de Maio de 2013, 16:09
 */

#ifndef PPN_HEAP_H
#define	PPN_HEAP_H
#include <string>
#include <iostream>
#include <fstream>
#include "BasicFunctions.h"
#include "BasicTypes_heap.h"
#include "HashExtended.h"
#include "HeapStrctPtrMin.h"
#include "CombLookUp.h"
//#include <google/profiler.h>

using namespace std;
class PPN_Heap {
    
public:
    PPN_Heap(char * filename);
    PPN_Heap();
    void openNewProblem(char * filename);
    virtual ~PPN_Heap();
    void lerArquivo(char * problemFile);
    void runDFS();
    void runLDS();
    void _runLDS();
    void runBFS();
    void KK();
    mpz_node* getRaiz() const;
private:
    void KK(mpz_node * node);
    void KK(HeapStrctPtrMin & node);
    void runBFS(mpz_node_bfs * node);
    void runDFS(mpz_node * node);
    void runLDS(mpz_node * node);
    void _runLDS(mpz_node * node);
    void runLDS(mpz_node * node, u_int32_t depth, u_int32_t k );
    mpz_node * raiz;
    mpz_node_bfs * raiz_bfs;
    int nElementos;
    int nroParticoes;
    int tempo;
    bool perfect;
    bool finished;
    int perfectVal;
    Cronometro chrono;
    mpz_class min;
    mpz_class nodes_inspected;
    mpz_class nodes_pruned;
    char* problem_file;
    CombLookUp combs;
    ofstream res;
};

#endif	/* PPN_HEAP_H */

