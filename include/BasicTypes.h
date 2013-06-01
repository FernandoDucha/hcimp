/* 
 * File:   BasicTypes.h
 * Author: fernando
 *
 * Created on 5 de Setembro de 2011, 18:03
 */

#ifndef BASICTYPES_H
#define	BASICTYPES_H
#include "ListStructurePtr.h"
#include "ListStructure.h"
#include <gmpxx.h>
#include <math.h>
#include <fstream>
#include <limits.h>
#include "Avl.h"
#include <limits>
#define MAXBKPING 100
using namespace std;
struct los_bfs;

struct number_element {
    long long id;

    number_element(long long n) {
        id = n;
    }

    number_element() {
        id = 0;
    }

    long long getId() const {
        return id;
    }

};

struct number_element_mpz {
    mpz_class id;
    char fromMerge;
    int ref;
    number_element_mpz(mpz_class n) {
        id = n;
        fromMerge=0;
        ref=1;
    }

    number_element_mpz() {
        id = 0;
    }

    mpz_class getId() const {
        return id;
    }

    number_element_mpz & operator=(number_element_mpz & A) {
        this->id = A.id;
        return *this;
    }


};

number_element_mpz & operator-(number_element_mpz & A,number_element_mpz & B);

number_element_mpz & operator+(number_element_mpz & A,number_element_mpz & B);



template <class tipo_elemento>struct list_element {
    long long id;

    list_element() {
        id = 0;
        //NNEWS++;
        List = new ListStructurePtr<tipo_elemento > (ListStructurePtr<tipo_elemento>::ORDEM_DECRESCENTE);
    }
    ListStructurePtr<tipo_elemento> * List;

    void addElementToList(tipo_elemento novo) {
        List->Add(novo);
        id += novo->id;
    }

    void addListToList(ListStructurePtr<tipo_elemento>*list) {
        node_list_struct<tipo_elemento>* tipel = list->nextFromLastAcc();
        while (tipel != NULL) {
            addElementToList(tipel->element);
            tipel = list->nextFromLastAcc();
        }
        list->ClearList();
        delete list;
        list = NULL;
    }

    ~list_element() {
        //NDELS++;
        delete List;
        List = NULL;
    }

    long long getId() const {
        return id;
    }
};

template <class tipo_elemento>struct list_element_MPZ {
    mpz_class id;
    int ref;
    //char del;

    list_element_MPZ() {
        // id = 0;
        ref = 1;
        // del = d;
        List = new ListStructurePtr<tipo_elemento > (ListStructurePtr<tipo_elemento>::ORDEM_DECRESCENTE);
    }
    ListStructurePtr<tipo_elemento> * List;

    node_list_struct<tipo_elemento>* addElementToList(tipo_elemento novo) {
        node_list_struct<tipo_elemento>*ret = List->Add(novo);
        id += novo->id;
        return ret;
        // cout<<id<<endl;
    }
    void addListToListSpecial(ListStructurePtr<tipo_elemento>* list);
    list_element_MPZ<tipo_elemento> * clone();

    void addListToList(ListStructurePtr<tipo_elemento>*list) {
        node_list_struct<tipo_elemento>* tipel = list->nextFromLastAcc();
        while (tipel != NULL) {
            tipel->element->ref++;
            addElementToList(tipel->element);
            tipel = list->nextFromLastAcc();
        }
        list = NULL;
    }

    void removeElement(tipo_elemento elem) {
        List->RemoveObject(elem);
        id -= elem->id;
    }

    void removeElement(node_list_struct<tipo_elemento>* elem) {
        id -= elem->element->id;
        List->RemoveObject(elem);
    }

    tipo_elemento removeFirst() {
        tipo_elemento ret = List->RemoveFront();
        id -= ret->id;
        return ret;
    }
    void cleanList();
    bool clean();

    ~list_element_MPZ() {
        //NDELS++;
        //mpz_clear(id.get_mpz_t());
        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
        delete List;
        List = NULL;
    }

    mpz_class getId() const {
        return id;
    }
};

template <class tipo_elemento>struct NodeTree {
    //mpz_class id;
    int ref;
    //char del;

    NodeTree() {
        //id = 0;
        ref = 1;
        // del = d;
        List = new AvlTree<tipo_elemento > ();
    }
    AvlTree<tipo_elemento> * List;

    void addElementToList(tipo_elemento novo) {
        List->Insert(novo);
        // id += novo->id;
        // cout<<id<<endl;
    }
    void addListToListSpecial(ListStructurePtr<tipo_elemento>* list);

    void addListToList(AvlTree<tipo_elemento>*list) {
        list->InsertTreeOnTree(List);
        // id=List->GetId();
    }

    NodeTree<tipo_elemento> * clone() {
        NodeTree<tipo_elemento> * ret = new NodeTree<tipo_elemento > ();
        delete ret->List;
        ret->List = List->clone();
        //ret->id=ret->List->GetId();
        return ret;
    }

    void removeElement(tipo_elemento elem) {
        List->Delete(elem);
        //id -= elem->id;
    }

    tipo_elemento removeFirst() {
        tipo_elemento ret = List->RemoveMax();
        //cout<<List->Check()<<endl;
        //id -= ret->id;
        return ret;
    }

    void cleanList() {
        List->cleanList();
    }
    int getSize(){
        return List->getSize();
    }
    ~NodeTree() {
        //NDELS++;
        //mpz_clear(id.get_mpz_t());
        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
        delete List;
        List = NULL;
    }

    mpz_class getId() const {
        return List->GetId();
    }
};

struct BookKeeping_mpz {
    mpz_class id;
    BookKeeping_mpz**List;
    int nElem;
    int ref;
    //ListStructurePtr<list_element_MPZ<BookKeeping_mpz*>*>*parent;
    //list_element_MPZ<BookKeeping_mpz*> *parent;

    BookKeeping_mpz(int s) {
        nElem = 0;
        if (s > 0) {
            List = new BookKeeping_mpz*[s];
        } else {
            List = NULL;
        }
        ref = 0;
        //parent =new ListStructurePtr<list_element_MPZ<BookKeeping_mpz*>*>(ListStructurePtr<list_element_MPZ<BookKeeping_mpz*>*>::ORDEM_DECRESCENTE);
    }

    BookKeeping_mpz(BookKeeping_mpz * bkpm) {
        id = bkpm->id;
        nElem = bkpm->nElem;
        if (nElem != 0)
            List = new BookKeeping_mpz*[nElem];
        else
            List = NULL;
        for (int i = 0; i < nElem; i++) {
            List[i] = bkpm->List[i];
        }
        ref = 0;
        // parent =new ListStructurePtr<list_element_MPZ<BookKeeping_mpz*>*>(ListStructurePtr<list_element_MPZ<BookKeeping_mpz*>*>::ORDEM_DECRESCENTE);
    }

    static void upRef(BookKeeping_mpz * bkp) {
        if (bkp->List == NULL) {
            //bkp->parent->append(bkp1);
            return;
        } else {
            for (int j = 0; j < bkp->nElem; j++) {
                upRef(bkp->List[j]);
            }
            bkp->ref++;
            //bkp->parent->append(bkp1); 
        }
    }

    static void downRef(BookKeeping_mpz * bkp) {
        if (bkp->List == NULL) {
            //delete bkp->parent->RemoveFront();
            return;

        } else {
            for (int j = 0; j < bkp->nElem; j++) {
                downRef(bkp->List[j]);
            }
            bkp->ref--;
            //delete bkp->parent->RemoveFront();
            if (bkp->ref == 0) {
                delete bkp;
            }
        }
    }

    ~BookKeeping_mpz() {
        delete [] List;
        List = NULL;
        // delete parent;
        //  parent = NULL;
    }

    void addElementToList(BookKeeping_mpz * novo) {
        List[nElem] = novo;
        id += novo->id;
        nElem++;
    }

    void addElementToList(number_element_mpz novo) {
        id = novo.id;
    }

    void subPrint(BookKeeping_mpz * bkp, int &i, int &count) {
        if (bkp->List == NULL) {
            cout << i << "--" << bkp->id << endl;
            if (bkp->id != 0) {
                count++;
            }
            i++;
        } else {
            for (int j = 0; j < bkp->nElem; j++) {
                subPrint(bkp->List[j], i, count);
            }

        }
    }

    int print() {
        int i = 1;
        int count = 0;
        subPrint(this, i, count);
        return count;
    }

    void setId(mpz_class id) {
        this->id = id;
    }

    mpz_class getId() const {
        return id;
    }
};

struct Pertubation {

    Pertubation(int re, int tr) {
        realoc = re;
        trocas = tr;
    }

    Pertubation() {
        realoc = -1;
        trocas = -1;
    }
    int realoc;
    int trocas;
};
typedef list_element<number_element*>BookKeeping;
typedef list_element<BookKeeping*>ListOfSums; //list_element< list_element< number_element> > 
typedef list_element<ListOfSums*>NodeList;
//typedef list_element_MPZ<number_element_mpz*>BookKeeping_mpz;
typedef list_element_MPZ<BookKeeping_mpz*>ListOfSums_mpz; //list_element< list_element< number_element> > 
typedef list_element_MPZ<ListOfSums_mpz*>NodeList_mpz_dfs;
typedef list_element_MPZ<number_element_mpz*>NodeList_dfs;

//typedef list_element_MPZ<number_element_mpz*>NodeList_dfs;

typedef NodeTree<ListOfSums_mpz*>NodeList_mpz;
typedef NodeTree<number_element_mpz*>NodeList_lds;
typedef NodeTree<los_bfs*>node_lst_tree;

template <class tipo_elemento> void list_element_MPZ<tipo_elemento>::addListToListSpecial(ListStructurePtr<tipo_elemento>* list) {
    node_list_struct<ListOfSums_mpz*> *los;
    while ((los = list->nextFromLastAcc()) != NULL) {
        node_list_struct<BookKeeping_mpz*>*bkp;
        ListOfSums_mpz * l = new ListOfSums_mpz();
        while ((bkp = los->element->List->nextFromLastAcc()) != NULL) {
            BookKeeping_mpz *b = new BookKeeping_mpz(bkp->element->nElem);
            b->nElem = bkp->element->nElem;
            // b->TotalNElem = bkp->element->TotalNElem;
            b->id = bkp->element->id;
            for (int i = 0; i < b->nElem; i++) {
                b->List[i] = bkp->element->List[i];
            }
            l->addElementToList(b);
        }
        this->addElementToList(l);
    }
}

template <class tipo_elemento> list_element_MPZ<tipo_elemento>* list_element_MPZ<tipo_elemento>::clone() {
    ListOfSums_mpz * ret = new ListOfSums_mpz();
    node_list_struct<BookKeeping_mpz*>* bkp;
    while ((bkp = List->nextFromLastAcc()) != NULL) {
        BookKeeping_mpz * b = new BookKeeping_mpz(bkp->element);
        BookKeeping_mpz::upRef(bkp->element);
        ret->addElementToList(b);
    }
    return ret;
}

template <class tipo_elemento> void list_element_MPZ<tipo_elemento>::cleanList() {
    node_list_struct<ListOfSums_mpz*> *nl;
    while ((nl = List->nextFromLastAcc()) != NULL) {
        nl->element->ref--;
        if (nl->element->ref == 0) {
            BookKeeping_mpz*bkp;
            while ((bkp = nl->element->List->RemoveFront()) != NULL) {
                //bkp->element->downRef(bkp->element,nl->element);
                BookKeeping_mpz::downRef(bkp);
                //                delete bkp;
            }

            //nl->element->List->ClearList();
            delete nl->element;
        }
    }
    List->ClearList();
}

template <class tipo_elemento> bool list_element_MPZ<tipo_elemento>::clean() {
    ref--;
    if (ref == 0) {
        BookKeeping_mpz * bkp;
        while ((bkp = List->RemoveFront()) != NULL) {
            BookKeeping_mpz::downRef(bkp);
        }
        return true;
    }
    return false;
}

#endif	/* BASICTYPES_H */

