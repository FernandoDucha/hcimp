/* 
 * File:   Hash.h
 * Author: fernando
 *
 * Created on 1 de Novembro de 2011, 14:42
 */

#ifndef HASH_H
#define	HASH_H
#include "BasicTypes.h"
#include "ListStructurePtr.h"

template <class Key, class ListableObj>class Hash {
public:
    Hash(int size, int a);
    Hash(const Hash& orig);
    virtual ~Hash();
    bool put(Key k, ListableObj obj);
    ListableObj  getFirst(Key k);
    int checkForId(int id);
    ListableObj  putIndirect(Key k);
    int getNElementos() const;
    void cleanTable();

    void setIdMin(int idMin) {
        this->idMin = idMin;
        keyMin = checkForId(idMin);
    }

    int getIdMin() const {
        return idMin;
    }

    void setKeyMin(int keyMin) {
        this->keyMin = keyMin;
    }

    int getKeyMin() const {
        return keyMin;
    }
private:

    int size;
    int nElementos;
    ListableObj**table;
    int * elementsPos;
    int * retrievalPos;
    int idMin;
    int keyMin;
};

template<class Key, class ListableObj> inline Hash<Key, ListableObj>::Hash(int size, int a) {
    table = new ListableObj*[size];
    elementsPos = new int[size];
    retrievalPos = new int[size];
    for (int i = 0; i < 30; i++) {
        table[i] = new ListableObj[2*a];
        elementsPos[i] = 0;
        retrievalPos[i] = 0;
    }
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 2*a; j++) {
            table[i][j] = NULL;
        }
    }
    nElementos = 0;
    this->size = size;
    keyMin = size - 1;
    idMin = 1;
}
template<class Key, class ListableObj> inline ListableObj   Hash<Key, ListableObj>::putIndirect(Key k){
    elementsPos[k]++;
    nElementos++;
    return table[k][elementsPos[k]];
}
template<class Key, class ListableObj> inline bool Hash<Key, ListableObj>::put(Key k, ListableObj  obj) {
    table[k][elementsPos[k]] = obj;
    elementsPos[k]++;
    nElementos++;
    //obj.setNULL();
    return true;
}

template<class Key, class ListableObj> inline ListableObj  Hash<Key, ListableObj>::getFirst(Key k) {
    if (retrievalPos[k] == elementsPos[k]) {
        retrievalPos[k] = elementsPos[k] = 0;
        return NULL;
    }
    ListableObj  node = table[k][retrievalPos[k]];
    retrievalPos[k]++;
    nElementos--;
    return node;
}

template<class Key, class ListableObj> inline void Hash<Key, ListableObj>::cleanTable() {
    for (int i = keyMin; i < size; i++) {
        while (elementsPos[i] != 0) {
            if (retrievalPos[i] == elementsPos[i]) {
                retrievalPos[i] = elementsPos[i] = 0;
                break;
            } else {
                //table[i][retrievalPos[i]]->clean();
                delete table[i][retrievalPos[i]];
                retrievalPos[i]++;
                nElementos--;
            }
        }
    }
}

template<class Key, class ListableObj> inline int Hash<Key, ListableObj>::checkForId(int id) {
    //    int ret = -1;
    //    for (int i = size - 1; i >= 0; i--) {
    //        if (table[i]->peekFirst() != NULL) {
    //            if (table[i]->peekFirst()->element->id == id) {
    //                ret = i;
    //                break;
    //            }
    //        }
    //    }
    //    return ret;
}

template<class Key, class ListableObj> int Hash<Key, ListableObj>::getNElementos() const {
    return nElementos;
}

template<class Key, class ListableObj> Hash<Key, ListableObj>::~Hash() {
    for (int i = 0; i < size; i++) {
        delete [] table[i];
    }
    delete [] table;
}
#endif	/* HASH_H */

