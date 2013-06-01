/* 
 * File:   CompleteKarmarkarKarp.h
 * Author: fernando
 *
 * Created on 5 de Setembro de 2011, 18:02
 */

#ifndef COMPLETEKARMARKARKARP_H
#define	COMPLETEKARMARKARKARP_H

#include "Combinatorics.h"
#include "BasicTypes.h"
#include <iostream>
#include <limits.h>
#include <pthread.h>
#include "Cronometro.h"
#include "NumberPartitionProblem.h"
using namespace std;


struct CKKnode{
    long long id;
    NodeList * nodeList;
    ListStructurePtr<CKKnode*> * children;
    CKKnode(){
        id=0;
        nodeList=new NodeList();
        children = new ListStructurePtr<CKKnode*>(ListStructurePtr<CKKnode*>::ORDEM_CRESCENTE);        
    }
    ~CKKnode(){
        delete nodeList;
        delete children;
        children=NULL;
        nodeList=NULL;
    }
    void cleanNode(){
//        node_list_struct<ListOfSums*> *nl;
//        while((nl=nodeList->List->nextFromLastAcc())!=NULL){
//            node_list_struct<BookKeeping*> *bkp;
//            while((bkp=nl->element->List->nextFromLastAcc())!=NULL){
//                delete bkp->element->List;
//                bkp->element->List=NULL;
//            } 
//            delete nl->element->List;
//            nl->element->List=NULL;
//        }
//        delete nodeList->List;
//        nodeList->List=NULL;
        delete nodeList;
        nodeList=NULL;
    }
    void updateNodeId(){
        id=nodeList->id;       
    }
    void cleanChildren(){
        delete children;
        children=NULL;
    }

    long long getId() const {
        return id;
    }
};

class CompleteKarmarkarKarp {
    
public:
    CompleteKarmarkarKarp(ListStructure<number_element> * source, int nroParticoes);
    CompleteKarmarkarKarp(NumberPartitionProblem * npp, int nroParticoes);
    CompleteKarmarkarKarp(const CompleteKarmarkarKarp& orig);
    virtual ~CompleteKarmarkarKarp();
    void GenerateRaiz(ListStructure<number_element> *source, int nPart);
    void createChildren(CKKnode *Parent);
    ListStructurePtr<ListOfSums*>* cloneListOfListOfSums(ListStructurePtr<ListOfSums*>* list);
    ListOfSums * cloneListOfSums(ListOfSums* los);
    BookKeeping * mergeBookKepings(BookKeeping* A, BookKeeping* B);
    ListStructurePtr<ListOfSums*> *  mergeListOfSums(ListOfSums* A, ListOfSums* B);
    bool prune(CKKnode *node);
    void run();
    long long GetMin() const;
    // ListOfSums permuteVectors(BookKeeping * A, int nonZeroA,BookKeeping * B, int nonZeroB, NodeList & node);
private:
    ListOfSums * normalize(ListOfSums * A);
    CKKnode * raiz;
    int numberOfNonZeroElements(ListOfSums * A);
    int nroParticoes;
    long long min;
    long long nodesInspected;
    long long nodesPruned;
    Cronometro c;//(Cronometro::SEGUNDOS);
    NumberPartitionProblem * p;
};
struct nodeExplorer{
    CompleteKarmarkarKarp *ckk;
    CKKnode * nodeToExplore;
};
void * explore(void*ptr);
#endif	/* COMPLETEKARMARKARKARP_H */

