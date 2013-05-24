/* 
 * File:   CompleteKarmarkarKarp_MPZ.h
 * Author: fernando
 *
 * Created on 5 de Setembro de 2011, 18:02
 */

#ifndef CompleteKarmarkarKarp_MPZ_H
#define	CompleteKarmarkarKarp_MPZ_H
#include<sys/types.h>
//#include <sys/ipc.h>
#include <sys/shm.h>
//#include <sys/sem.h>
#include <errno.h>
#include "Combinatorics.h"
#include <iostream>
#include <limits.h>
#include <pthread.h>
#include "Cronometro.h"
#include "BasicTypes.h"
#include "BasicFunctions.h"
#include "NumberPartitionProblem_MPZ.h"
#include "Hash.h"
#include "Semaphore.h"
using namespace std;
#define MAX_RETRIES 10

struct info {

    info() {
        created_nodes = 0;
        pruned_nodes = 0;
        min = 0;
    }
    mpz_class created_nodes;
    mpz_class pruned_nodes;
    mpz_class min;
    int pidpai;
    int pidfilho;
};

struct CKKnode_mpz {
    NodeList_mpz * nodeList;
    char left;
    char right;

    CKKnode_mpz() {
        left = 0;
        right = 0;
        nodeList = new NodeList_mpz();
    }

    void clean() {
        nodeList->cleanList();
        delete nodeList;
        nodeList = NULL;
    }

    ~CKKnode_mpz() {
        delete nodeList;
        nodeList = NULL;
    }

    int getId() {
        return right;
    }

    void setNULL() {
        nodeList = NULL;
    }
};

struct CKKnode_bfs {
    node_lst_bfs * nodeList;
    char left;
    char right;

    CKKnode_bfs() {
        left = 0;
        right = 0;
        nodeList = NULL;
    }

    CKKnode_bfs(int s) {
        left = 0;
        right = 0;
        nodeList = new node_lst_bfs(s);

    }

    ~CKKnode_bfs() {
        nodeList->cleanList();
        delete nodeList;
        nodeList = NULL;
    }

    int getId() {
        return right;
    }

    CKKnode_bfs & operator=(CKKnode_bfs node) {
        nodeList = node.nodeList;
        right = node.right;
        left = node.left;
        //node.nodeList=NULL;
    }

    void setNULL() {
        nodeList = NULL;
    }
};

struct CKKnode_bfs_mpz {
    node_lst_bfs_mpz nodeList;
    char left;
    char right;

    CKKnode_bfs_mpz() {
        left = 0;
        right = 0;
        //nodeList = NULL;
    }

    CKKnode_bfs_mpz(int s) : nodeList(s) {
        left = 0;
        right = 0;
        //nodeList= new node_lst_bfs_mpz(s);
        //nodeList = new node_lst_bfs_mpz(s);

    }

    ~CKKnode_bfs_mpz() {
        //nodeList->cleanList();
        //delete nodeList;
        //nodeList = NULL;
    }

    int getId() {
        return right;
    }

    CKKnode_bfs_mpz & operator=(CKKnode_bfs_mpz node) {
        nodeList = node.nodeList;
        right = node.right;
        left = node.left;
        //node.nodeList=NULL;
    }

    //    void setNULL() {
    //        nodeList = NULL;
    //    }
};
struct CKKnode_lds {
    NodeList_lds nodeList;
    CKKnode_lds() {
    
    }
    ~CKKnode_lds() {
        //nodeList->cleanList();
        //delete nodeList;
        //nodeList = NULL;
    }

    mpz_class getId() {
        return nodeList.getId();
    }

//    CKKnode_bfs_mpz & operator=(CKKnode_bfs_mpz node) {
//        nodeList = node.nodeList;
//    }
};
struct CKKnode_dfs {
    NodeList_dfs nodeList;
    CKKnode_dfs() {
    
    }
    ~CKKnode_dfs() {
        //nodeList->cleanList();
        //delete nodeList;
        //nodeList = NULL;
    }

    mpz_class getId() {
        return nodeList.getId();
    }

//    CKKnode_bfs_mpz & operator=(CKKnode_bfs_mpz node) {
//        nodeList = node.nodeList;
//    }
};
struct ToBeSearched;

struct ToBeSearched {
    bool flag;

    ToBeSearched() {
        id = 0;
        flag = true;
        nodebfs = NULL;
        node = NULL;
    }

    ToBeSearched(CKKnode_mpz* n, char c) {
        nodebfs = NULL;
        node = n;
        id = c;
        flag = true;
    }

    ToBeSearched(CKKnode_bfs* n, char c) {
        node = NULL;
        nodebfs = n;
        id = c;
        flag = true;
    }

    void clean() {
        if (flag) {
            if (node) {
                node->nodeList->cleanList();
                delete node;
            } else if (nodebfs) {
                nodebfs->nodeList->cleanList();
                delete nodebfs;
            }

        }
    }

    ToBeSearched& operator=(ToBeSearched b) {
        this->flag = b.flag;
        this->id = b.id;
        this->node = b.node;
        this->nodebfs = b.nodebfs;
        return *this;
    }

    ToBeSearched& operator=(ToBeSearched * b) {
        this->flag = b->flag;
        this->id = b->id;
        this->node = b->node;
        this->nodebfs = b->nodebfs;
        return *this;
    }

    double getId() const {
        return id;
    }

    bool isNULL() {
        return ((nodebfs == NULL) && (node == NULL));
    }
    static ToBeSearched returnNULL();
    CKKnode_bfs * nodebfs;
    CKKnode_mpz * node;
    char id;
};

class CompleteKarmarkarKarp_MPZ {
public:
    CompleteKarmarkarKarp_MPZ(ListStructure<number_element_mpz> * source, int nroParticoes);
    CompleteKarmarkarKarp_MPZ(NumberPartitionProblem_MPZ * npp, int nroParticoes);
    CompleteKarmarkarKarp_MPZ(const CompleteKarmarkarKarp_MPZ& orig);
    virtual ~CompleteKarmarkarKarp_MPZ();
    void GenerateRaiz(ListStructure<number_element_mpz> *source);
    void GenerateRaizBFS(ListStructure<number_element_mpz> *source);
    void GenerateRaizBFS_mpz(ListStructure<number_element_mpz> *source);
    void GenerateRaizLDS(ListStructure<number_element_mpz> *source);
    void GenerateRaizDFS(ListStructure<number_element_mpz> *source);
    void LDS(CKKnode_mpz*Parent,int initDisc);
    void subLDS(CKKnode_mpz * Parent, int depth, int k);
    void LDS(CKKnode_lds*Parent,int initDisc);
    void subLDS(CKKnode_lds * Parent, int depth, int k);
    void depthFirst(CKKnode_mpz *Parent);
    void depthFirst(CKKnode_dfs *Parent);
    void breadthFirst(CKKnode_bfs * Parent, int alpha);
    void breadthFirst(CKKnode_bfs_mpz * Parent, int alpha);
    //node_lst_vector * createVector(node_lst_bfs_mpz * A);
    void breadthFirst(CKKnode_mpz * Parent, int alpha);
    ListStructurePtr<ListOfSums_mpz*>* cloneListOfListOfSums(ListStructurePtr<ListOfSums_mpz*>* list);
    AvlTree<ListOfSums_mpz*>* cloneListOfListOfSums(AvlTree<ListOfSums_mpz*>* list);
    AvlTree<los_bfs*>* cloneListOfListOfSums(AvlTree<los_bfs*>* list);
    ListOfSums_mpz * cloneListOfSums(ListOfSums_mpz* los);
    BookKeeping_mpz * mergeBookKepings(BookKeeping_mpz* A, BookKeeping_mpz* B);
    bkp_bfs * mergeBookKepings(bkp_bfs*A, bkp_bfs*B);

    ListStructurePtr<ListOfSums_mpz*> * mergeListOfSums(ListOfSums_mpz* A, ListOfSums_mpz* B);
    ListStructurePtr<ListOfSums_mpz*> * mergeListOfSums1(ListOfSums_mpz* A, ListOfSums_mpz* B);
    ListStructurePtr<ListOfSums_mpz*> * mergeListOfSums(ListOfSums_mpz* A, ListOfSums_mpz* B, int k);
    ListStructurePtr<los_bfs*>* mergeListOfSums(los_bfs* A, los_bfs*B);
    ListStructurePtr<los_bfs*>* mergeListOfSums1(los_bfs* A, los_bfs*B);
    node_lst_tree * createTree(node_lst_bfs * A);
    node_lst_vector * createVector(node_lst_bfs * A);
    bool prune(CKKnode_dfs * node);
    bool prune(CKKnode_mpz *node);
    bool prune1(CKKnode_mpz * node);
    bool prune1(CKKnode_bfs * node);
    bool prune1(CKKnode_bfs_mpz * node);
    bool prune(CKKnode_lds * node);
    void runBFS(int alpha);
    void runBFS1(int alpha);
    void runDFS();
    void runDFS1();
    void runLDS();
    void runLDS1(int InitDisc1,int InitDisc2);
    mpz_class GetMin() const;
    void KK(CKKnode_mpz * node, int d);
    void KK(CKKnode_bfs * node, int d, int n);
    void KK(node_lst_tree * node, int d);
    void KK(node_lst_vector * v);
    void KK(CKKnode_bfs_mpz * node);
private:
    ListOfSums_mpz * normalize(ListOfSums_mpz * A);
    los_bfs * normalize(los_bfs * A);
    Hash<int, CKKnode_bfs*>*hashSearch;
    ListStructurePtr<CKKnode_bfs*>* bfslist;
    Hash<int, CKKnode_bfs_mpz*>*hashSearch1;
    ListStructurePtr<CKKnode_bfs_mpz*>* bfslist1;

    Hash<int, CKKnode_mpz*>*hashSearch_mpz;
    ListStructurePtr<CKKnode_mpz*>* bfslist_mpz;
    CKKnode_mpz * raiz;
    CKKnode_bfs * raizBFS;
    CKKnode_bfs_mpz *raizBFS_mpz;
    CKKnode_lds * raizLDS;
    CKKnode_dfs * raizDFS;
    int numberOfNonZeroElements(ListOfSums_mpz * A);
    int numberOfNonZeroElements(los_bfs * A);
    int nroParticoes;
    long long * nodesInspected;
    long long * nodesPruned;
    long long NIActual;
    double NodesPersecond;
    //number_element_mpz * NumberVector;
    Cronometro c; //(Cronometro::SEGUNDOS);
    NumberPartitionProblem_MPZ * p;
    int nls;
    key_t key;
    key_t key_s;
    int shmid;
    void * min;
    int semid;
    int semid_s;
    Combinatorics * comb;
    Semaphore * sem;
};

struct nodeExplorer_mpz {
    CompleteKarmarkarKarp_MPZ *ckk;
    CKKnode_mpz * nodeToExplore;
};
void * explore_mpz(void*ptr);
int initsem(key_t key, int nsems);

#endif	/* CompleteKarmarkarKarp_MPZ_H */

