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
#include <map>
#include <set>
#include <unordered_set>
#include <limits>
#include <gsl/gsl_rng.h>
#include "BasicFunctions.h"
#include "BasicTypes_heap.h"
#include "HashExtended.h"
#include "HeapStrctPtrMin.h"
#include "CombLookUp.h"
#include "SolutionObject.h"
//#include <google/profiler.h>

using namespace std;

class PPN_Heap {
public:
    typedef pair<uint16_t,double> InsMove;
    typedef SolutionObject::swap swap;
    typedef pair<swap,double> SwapMove;
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
    void ILS_KK();
    SolutionObject * KKConstruct();
    SolutionObject * GraspConstruct(double alpha);
    void ILS_Grasp(double alpha);
    mpz_node* getRaiz() const;
    void pertubation(SolutionObject * sol,gsl_rng * rng, double strength, int Invertions, int Swaps);
    void pertubation1(SolutionObject * sol, gsl_rng * rng, double strength, int Invertions, int Swaps);
private:
    void steepestDescent(SolutionObject * sobj);
    void KK(HeapStrctPtrMin & node, map<mpz_class, mpz_class> & A1, map<mpz_class, mpz_class> & A2);
    void KK(mpz_node * node);
    void KK(HeapStrctPtrMin & node);
    void runBFS(mpz_node_bfs * node);
    void runDFS(mpz_node * node);
    void runLDS(mpz_node * node);
    void _runLDS(mpz_node * node);
    void runLDS(mpz_node * node, u_int32_t depth, u_int32_t k);
    void cleanHistory(){
        for(int i=0;i<nElementos;i++){
            for(int j=0;j<nElementos;j++){
                pertubationHistory[i][j]=false;
            }
        }
    }
    mpz_node * raiz;
    mpz_node_bfs * raiz_bfs;
    bool ** pertubationHistory;
    uint16_t nElementos;
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
    map<mpz_class, uint16_t> numLookUpTable;
    map<uint16_t,mpz_class> invNumLookUpTable;

    ofstream res;
};

#endif	/* PPN_HEAP_H */

