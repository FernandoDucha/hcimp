/*
 * ListStructure.h
 *
 *  Created on: Feb 22, 2009
 *      Author: fordem
 */

#ifndef LISTSTRUCTURE_H_
#define LISTSTRUCTURE_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "node_list_struct.h"
using namespace std;
template <class ListableObj> class ListStructure {
private:
    node_list_struct<ListableObj> *Front;
    node_list_struct<ListableObj> *Rear;
    node_list_struct<ListableObj> *LastAcc;
    int Size;
    ListableObj RemoveNodeList(node_list_struct<ListableObj> * aux);
    bool OrderCrescente;


protected:

    node_list_struct<ListableObj> * createNodeList(ListableObj chave) {
        node_list_struct<ListableObj> * ret = new node_list_struct<ListableObj > ();
        ret->element = chave;
        return ret;
    }

public:
    static const bool ORDEM_CRESCENTE = true;
    static const bool ORDEM_DECRESCENTE = false;
    ~ListStructure();

    ListStructure(bool OrdCresc) throw (const char *) {
        Size = 0;
        Rear = Front = NULL;
        LastAcc = NULL;
        OrderCrescente = OrdCresc;
    }

    bool compare(ListableObj a, ListableObj b) {
        if (OrderCrescente) {
            return a.id > b.id;
        } else {
            return a.id < b.id;
        }
    }
    // Funções Genéricas
    ListableObj RemoveFront();
    void Add(ListableObj novo);
    void Add(ListStructure<ListableObj>* list);
    void append(ListableObj novo);
    ListableObj RemoveRear();
    void PrintLista();
    void ClearList();
    //Funções Para Nodos
    ListableObj RemoveObject(ListableObj Value);
    ListableObj RemoveObject(node_list_struct<ListableObj>* node);
    bool PesquisaNodo(ListableObj Value);
    void resetLastAcc();
    node_list_struct<ListableObj>* nextFromLastAcc();
    ListableObj retrieveNode(int Value);
    node_list_struct<ListableObj>* retrieve_K_esimo(int Kesimo);
    ListableObj peekFirst();
    ListableObj peekLast();

    ListableObj * getVector();
    ListableObj retrieveClosest(ListableObj Value);
    //    int getNroElements() {
    //        int resp = 0;
    //        if (Front != NULL) {
    //            node_list_struct<ListableObj> * aux = Front;
    //            while (aux != NULL) {
    //                //	printf("## %d ##\n",aux->Obj->getValue());
    //                resp += aux->Obj->getSize();
    //                aux = aux->next;
    //            }
    //        }
    //        return resp;
    //    }
    ListStructure<ListableObj> * clone();
    //Para Comodite...

    int getSize() const {
        return Size;
    }

    void setSize(int Size) {
        this->Size = Size;
    }
    ListableObj operator[](int index);
};

template <class ListableObj> ListableObj ListStructure<ListableObj>::operator[](int index) {
    return retrieve_K_esimo(index);
}

template <class ListableObj> void ListStructure<ListableObj>::resetLastAcc() {
    LastAcc = NULL;
}

template <class ListableObj> node_list_struct<ListableObj>* ListStructure<ListableObj>::nextFromLastAcc() {
    if (LastAcc != NULL) {
        LastAcc = LastAcc->next;
    } else {
        LastAcc = Front;
    }
    return LastAcc;
}

template <class ListableObj> ListStructure<ListableObj> * ListStructure<ListableObj>::clone() {
    ListStructure<ListableObj> * ret = new ListStructure<ListableObj > (ORDEM_DECRESCENTE);
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            //ListableObj chave = aux->id;
            ret->Add(aux->element);
            aux = aux->next;
        }
        return ret;
    }
    return ret;
}

/************************************************************************
 * DEBUG
 ************************************************************************/
template <class ListableObj> void ListStructure<ListableObj>::PrintLista() {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            cout<<aux->element.id<<endl;
            //				printf("## %d ##\n",aux->Obj->getValue());
            aux = aux->next;
        }
    }
}

/***********************************************************************
 * PESQUISA E ADIÇÃO
 ***********************************************************************/
template<class ListableObj> inline ListableObj ListStructure<ListableObj>::retrieveClosest(ListableObj Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            ListableObj firstDiff(abs(aux->element.id - Value.id));
            if (aux->next != NULL) {
                ListableObj secondDiff(abs(aux->next->element.id - Value.id));
                if (firstDiff.id < secondDiff.id) {
                    return aux->element.id;
                }
            } else {
                return aux->element.id;
            }
            aux = aux->next;

        }
    }
}

template<class ListableObj> inline void ListStructure<ListableObj>::append(ListableObj novo) {
    node_list_struct<ListableObj> *aux = createNodeList(novo);
    //aux->element.id = novo;
    //	if(!aux->Obj->isValid()){
    //		return;
    //	}
    if (Size == 0) {
        Rear = Front = aux;
        Front->next = NULL;
        Front->prev = NULL;
        Rear->next = NULL;
        Rear->prev = NULL;
    } else {
        if (Size == 1) {
            Rear = aux;
            Rear->prev = Front;
            Rear->next = NULL;
            Front->next = Rear;
        } else {
            aux->next = NULL;
            aux->prev = Rear;
            Rear->next = aux;
            Rear = aux;
        }
    }
    Size = Size + 1;
}
template <class ListableObj> inline void ListStructure<ListableObj>::Add(ListStructure<ListableObj>* list){
    node_list_struct<ListableObj> * elem;
    while((elem=list->nextFromLastAcc())!=NULL){
        Add(elem->element);
    }
}
template <class ListableObj> inline void ListStructure<ListableObj>::Add(ListableObj novo) {
    node_list_struct<ListableObj> *aux = createNodeList(novo);
    aux->element = novo;
    //	if(!aux->Obj->isValid()){
    //		return;
    //	}
    if (Size == 0) {
        Rear = Front = aux;
        Front->next = NULL;
        Front->prev = NULL;
        Rear->next = NULL;
        Rear->prev = NULL;
    } else {

        if (Size == 1) {
            if (compare(aux->element, Front->element)) {
                Rear = aux;
                Rear->prev = Front;
                Rear->next = NULL;
                Front->next = Rear;

            } else {
                Front = aux;
                Front->next = Rear;
                Front->prev = NULL;
                Rear->prev = Front;
            }
        } else {
            node_list_struct<ListableObj> * temp = Front;
            bool flag = false;
            while (temp != NULL) {
                if (compare(temp->element, aux->element)) {
                    aux->next = temp;
                    aux->prev = temp->prev;
                    if (temp->prev == NULL) {
                        temp->prev = aux;
                        Front = aux;
                        Front->prev = NULL;
                    } else {
                        temp->prev->next = aux;
                        temp->prev = aux;
                    }
                    flag = true;
                    break;
                }
                temp = temp->next;
            }
            if (!flag) {
                aux->prev = Rear;
                Rear->next = aux;
                aux->next = NULL;
                Rear = aux;
            }
        }
    }
    Size = Size + 1;
}

template<class ListableObj> inline ListableObj ListStructure<ListableObj>::retrieveNode(int Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            if (aux->element->id != Value)
                aux = aux->next;
            else {
                return aux->element->id;
            }
        }
    }
    return NULL;
}

template<class ListableObj> inline node_list_struct<ListableObj>* ListStructure<ListableObj>::retrieve_K_esimo(int Kesimo) {
    int cont = 0;
    node_list_struct<ListableObj> * aux = Front;
    if (Front != NULL) {
        while (aux != NULL) {
            if (cont == Kesimo)break;
            aux = aux->next;
            cont++;
        }
    }
    //printf("%x\n",aux);
    return (aux != NULL) ? aux : NULL;

}

template<class ListableObj> inline void ListStructure<ListableObj>::ClearList() {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            node_list_struct<ListableObj> * temp = aux;
            aux = aux->next;
            if (aux != NULL)
                delete temp;
        }
    }
    delete Rear;
    Front = NULL;
    Rear = NULL;
    Size = 0;
}

template<class ListableObj> inline bool ListStructure<ListableObj>::PesquisaNodo(ListableObj Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL && (aux->element.id != Value.id)) {
            aux = aux->next;
        }
        if (aux != NULL) {
            return true;
        }
    }
    return false;
}

template<class ListableObj> ListableObj * ListStructure<ListableObj>::getVector() {
    ListableObj * ret;
    ret = new ListableObj[Size];
    node_list_struct<ListableObj> * aux = Front;
    int cont = 0;
    while (aux != NULL) {
        ret[cont] = aux->element;
        aux = aux->next;
        cont++;
    }
    return ret;
}

template<class ListableObj>  ListableObj ListStructure<ListableObj>::peekFirst() {
    return Front->element;
}
template<class ListableObj>  ListableObj ListStructure<ListableObj>::peekLast() {
    return Rear->element;
}

/***********************************************************************
 * REMOÇÃO
 ***********************************************************************/
template <class ListableObj>ListableObj ListStructure<ListableObj>::RemoveObject(node_list_struct<ListableObj>* node){
    if(node->prev==NULL){
        Front=node->next;
        Front->prev=NULL;
    }else if(node->next==NULL){
        Rear=node->prev;
        Rear->next=NULL;
    }else{
        node_list_struct<ListableObj> * prev=node->prev;
        node_list_struct<ListableObj> * next=node->next;
        prev->next=next;
        next->prev=prev;        
    }
    Size--;
    ListableObj ret=node->element;
    delete node;
    return ret;
}
template <class ListableObj> inline ListableObj ListStructure<ListableObj>::RemoveFront() {
    if (Front == NULL)
        return ListableObj::returnNULL();
    node_list_struct<ListableObj> * aux = Front;
    if (Rear == Front) {
        Rear = NULL;
        Front = NULL;
    } else {
        Front = Front->next;
        Front->prev = NULL;
    }
   // ListableObj ret = aux->element->id;
    //delete aux;
    Size = Size - 1;
    ListableObj ret = aux->element;
    delete aux;
    return ret;
}

template <class ListableObj> inline ListableObj ListStructure<ListableObj>::RemoveRear() {
    if (Rear == NULL)
        return NULL;
    node_list_struct<ListableObj> * aux = Rear;
    if (Rear == Front) {
        Rear = NULL;
        Front = NULL;
    } else {
        Rear = Rear->prev;
        Rear->next = NULL;
    }
    ListableObj ret = aux->element->id;
    delete aux;
    Size = Size - 1;
    return ret;
}

template<class ListableObj> inline ListableObj ListStructure<ListableObj>::RemoveNodeList(node_list_struct<ListableObj> *aux) {
    if (aux != NULL) {
        if (Size == 1) {
            ListableObj resp = aux->element;
            Size = Size - 1;
            delete aux;
            Front = Rear = NULL;
            return resp;
        }
        if (aux == Front) {
            ListableObj resp = aux->element;
            aux->next->prev = NULL;
            Front = aux->next;
            Size = Size - 1;
            delete aux;
            return resp;
        } else if (aux == Rear) {
            ListableObj resp = aux->element;
            aux->prev->next = NULL;
            Rear = aux->prev;
            Size = Size - 1;
            delete aux;
            return resp;
        } else {
            ListableObj resp = aux->element;
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
            Size = Size - 1;
            delete aux;
            return resp;
        }
    } else {
        return ListableObj(-1);
    }
}

template<class ListableObj> inline ListableObj ListStructure<ListableObj>::RemoveObject(ListableObj Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL && (aux->element.id != Value.id)) {
            aux = aux->next;
        }
        if (aux != NULL) {
            return RemoveNodeList(aux);
        }
    }
    return ListableObj(-1);
}

/***********************************************************************
 * Destrutor
 ***********************************************************************/
template<class ListableObj> inline ListStructure<ListableObj>::~ListStructure() {
    if (Front != NULL && Size > 0) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            node_list_struct<ListableObj> * temp = aux;
            aux = aux->next;
            //if (aux != NULL)
            delete temp;
        }
        //delete Rear;
        //		Front==NULL;
        //		Rear==NULL;
    }
}

#endif /* LISTSTRUCTURE_H_ */
