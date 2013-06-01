/*
 * ListStructure.h
 *
 *  Created on: Feb 22, 2009
 *      Author: fordem
 */

#ifndef LISTSTRUCTUREPTR_H_
#define LISTSTRUCTUREPTR_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "node_list_struct.h"
#include <gmpxx.h>
using namespace std;
//template <class TipoChave>struct node_list_struct {
//    TipoChave element;
//    node_list_struct * next;
//    node_list_struct * prev;
//};

template <class ListableObj> class ListStructurePtr {
private:
    node_list_struct<ListableObj> *Front;
    node_list_struct<ListableObj> *Rear;
    node_list_struct<ListableObj> *LastAcc;
    int Size;
    ListableObj RemoveNodeList(node_list_struct<ListableObj> * aux);
    bool OrderCrescente;


protected:

    node_list_struct<ListableObj> * createNodeList(ListableObj chave) {
        //NNEWS++;
        node_list_struct<ListableObj> * ret = new node_list_struct<ListableObj > ();
        ret->element = chave;
        return ret;
    }

public:
    static const bool ORDEM_CRESCENTE = true;
    static const bool ORDEM_DECRESCENTE = false;
    ~ListStructurePtr();

    ListStructurePtr(bool OrdCresc) throw (const char *) {
        Size = 0;
        Rear = Front = NULL;
        LastAcc = NULL;
        OrderCrescente = OrdCresc;
    }

    bool compare(ListableObj a, ListableObj b) {
        if (OrderCrescente) {
            return a->getId() >= b->getId();
        } else {
            return a->getId() <= b->getId();
        }
    }
    // Funções Genéricas
    ListableObj RemoveFront();
    node_list_struct<ListableObj>* Add(ListableObj novo);
    void Add(ListStructurePtr<ListableObj>* list);
    void append(ListableObj novo);
    node_list_struct<ListableObj>* RemoveRear();
    void PrintLista();
    void ClearList();
    //Funções Para Nodos
    ListableObj RemoveObject(ListableObj Value);
    ListableObj RemoveObject(node_list_struct<ListableObj>* node);
    bool PesquisaNodo(ListableObj Value);
    void resetLastAcc();
    node_list_struct<ListableObj>* nextFromLastAcc();
    ListableObj retrieveNode(int Value);
    ListableObj retrieve_K_esimo(int Kesimo);
    ListableObj peekFirst();
    ListableObj peekLast();

    ListableObj * getVector();
    ListableObj retrieveClosest(int Value);
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
    ListStructurePtr<ListableObj> * clone();
    //Para Comodite...

    int getSize() const {
        return Size;
    }

    void setSize(int Size) {
        this->Size = Size;
    }
    ListableObj operator[](int index);
};

template <class ListableObj> ListableObj ListStructurePtr<ListableObj>::operator[](int index) {
    return retrieve_K_esimo(index);
}

template <class ListableObj> void ListStructurePtr<ListableObj>::resetLastAcc() {
    LastAcc = NULL;
}

template <class ListableObj> node_list_struct<ListableObj>* ListStructurePtr<ListableObj>::nextFromLastAcc() {
    if (LastAcc != NULL) {
        LastAcc = LastAcc->next;
    } else {
        LastAcc = Front;
    }
    return LastAcc;
}

template <class ListableObj> ListStructurePtr<ListableObj> * ListStructurePtr<ListableObj>::clone() {
    ListStructurePtr<ListableObj> * ret = new ListStructurePtr<ListableObj > (ORDEM_DECRESCENTE);
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            //ListableObj chave = aux->id;
            if (aux->element == NULL) {
                printf("alow");
            }
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
template <class ListableObj> void ListStructurePtr<ListableObj>::PrintLista() {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        int i = 1;
        while (aux != NULL) {
            cout << i << " -- " << aux->element->id << endl;
            //				printf("## %d ##\n",aux->Obj->getValue());
            i++;
            aux = aux->next;
        }
    }
}

/***********************************************************************
 * PESQUISA E ADIÇÃO
 ***********************************************************************/
template<class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::retrieveClosest(int Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            int firstDiff = abs(aux->element->id - Value);
            if (aux->next != NULL) {
                int secondDiff = abs(aux->next->element->id - Value);
                if (firstDiff < secondDiff) {
                    return aux->element->id;
                }
            } else {
                return aux->element->id;
            }
            aux = aux->next;

        }
    }
}

template<class ListableObj> inline void ListStructurePtr<ListableObj>::append(ListableObj novo) {
    node_list_struct<ListableObj> *aux = createNodeList(novo);

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

template <class ListableObj> inline void ListStructurePtr<ListableObj>::Add(ListStructurePtr<ListableObj>* list) {
    //cout<<list->getSize()<<endl;
    node_list_struct<ListableObj> * elem;
    while ((elem = list->nextFromLastAcc()) != NULL) {
        Add(elem->element);
    }
}

template <class ListableObj> inline node_list_struct<ListableObj> * ListStructurePtr<ListableObj>::Add(ListableObj novo) {
    node_list_struct<ListableObj> *aux = createNodeList(novo);
    //aux->element = novo;
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
    return aux;
}

template<class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::retrieveNode(int Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            if (aux->element->id != Value)
                aux = aux->next;
            else {
                return aux->element;
            }
        }
    }
    return NULL;
}

template<class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::retrieve_K_esimo(int Kesimo) {
    int cont = 0;
    node_list_struct<ListableObj> * aux = Front;
    if (Front != NULL) {
        while (aux != NULL) {
            if (cont == Kesimo)break;
            aux = aux->next;
            cont++;
        }
    }
    if(aux){
        return aux->element;
    }else{
        return NULL;
    }

}

template<class ListableObj> inline void ListStructurePtr<ListableObj>::ClearList() {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            node_list_struct<ListableObj> * temp = aux;
            aux = aux->next;
            //if (aux != NULL)
            delete temp;
        }
    }
    // delete Rear;
    Front = NULL;
    Rear = NULL;
    Size = 0;
}

template<class ListableObj> inline bool ListStructurePtr<ListableObj>::PesquisaNodo(ListableObj Value) {
    if (Front != NULL) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL && (aux->element->id != Value->id)) {
            aux = aux->next;
        }
        if (aux != NULL) {
            return true;
        }
    }
    return false;
}

template<class ListableObj> ListableObj * ListStructurePtr<ListableObj>::getVector() {
    ListableObj * ret;
    //NNEWS++;
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

template<class ListableObj> ListableObj ListStructurePtr<ListableObj>::peekFirst() {
    return Front->element;
}

template<class ListableObj> ListableObj ListStructurePtr<ListableObj>::peekLast() {
    return Rear->element;
}

/***********************************************************************
 * REMOÇÃO
 ***********************************************************************/
template <class ListableObj>ListableObj ListStructurePtr<ListableObj>::RemoveObject(node_list_struct<ListableObj>* node) {
    if (Front == Rear) {
        Front = Rear = NULL;
    } else if (node->prev == NULL) {
        Front = node->next;
        Front->prev = NULL;
    } else if (node->next == NULL) {
        Rear = node->prev;
        Rear->next = NULL;
    } else {
        node_list_struct<ListableObj> * prev = node->prev;
        node_list_struct<ListableObj> * next = node->next;
        prev->next = next;
        next->prev = prev;
    }
    Size--;
    ListableObj ret = node->element;
    delete node;
    return ret;
}

template <class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::RemoveFront() {
    if (Front == NULL)
        return NULL;
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

template <class ListableObj> inline node_list_struct<ListableObj>* ListStructurePtr<ListableObj>::RemoveRear() {
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
    Size = Size - 1;
    return aux;
}

template<class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::RemoveNodeList(node_list_struct<ListableObj> *aux) {
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
        return NULL;
    }
}

template<class ListableObj> inline ListableObj ListStructurePtr<ListableObj>::RemoveObject(ListableObj Value) {
    if (Front != NULL) {
        //mpz_class diff1=Front->element->id-Value->id;
        mpz_class diff2 = Rear->element->id - Value->id;
        //if(abs(diff1)<abs(diff2)){
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL && (aux->element->id != Value->id)) {
            aux = aux->next;
        }
        if (aux != NULL) {
            return RemoveNodeList(aux);
        }
    } else {
        node_list_struct<ListableObj> * aux = Rear;
        while (aux != NULL && (aux->element->id != Value->id)) {
            aux = aux->prev;
        }
        if (aux != NULL) {
            return RemoveNodeList(aux);
        }
    }
    return NULL;
}

/***********************************************************************
 * Destrutor
 ***********************************************************************/
template<class ListableObj> inline ListStructurePtr<ListableObj>::~ListStructurePtr() {
    if (Front != NULL && Size > 0) {
        node_list_struct<ListableObj> * aux = Front;
        while (aux != NULL) {
            node_list_struct<ListableObj> * temp = aux;
            aux = aux->next;
            //if (aux != NULL)
            //NDELS+=2;
            delete temp->element;
            *&temp->element = NULL;
            delete temp;
            temp = NULL;
            Size--;
        }
        //delete Rear;
        Front == NULL;
        Rear == NULL;
    }
}

#endif /* LISTSTRUCTUREPTR_H_ */
