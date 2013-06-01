// <plaintext>
#ifndef BFS_H
#define BFS_H

#include <stddef.h>
#include <iostream>
#include <gmpxx.h>
#include "BasicTypes.h"
#include "ListStructurePtr.h"
#include "enums.h"
using namespace std;
struct node_lst_bfs;
struct los_bfs;
void Particao(int Esq, int Dir, int & i, int & j, los_bfs ** A);
void Ordena(int Esq, int Dir, los_bfs ** A);
void QuickSort(los_bfs ** A, int start, int fim);
int PesqBinaria(los_bfs * p, los_bfs ** A, int start, int fim);

struct bkp_bfs {
    mpz_class id;
    bkp_bfs ** List;
    short nElem;
    long long ref;

    bkp_bfs(int s) {
        if (s > 0) {
            List = new bkp_bfs*[s];
        } else {
            List = NULL;
        }
        nElem = 0;
        ref = 0;
    }

    void addElementToList(bkp_bfs * novo) {
        id += novo->id;
        List[nElem] = novo;
        nElem++;
    }

    void addElementToList(number_element_mpz novo) {
        id = novo.id;
    }

    ~bkp_bfs() {
        delete [] List;
        List = NULL;
    }

    mpz_class getId() const {
        return id;
    }

    static void upRef(bkp_bfs * bkp) {
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

    static void downRef(bkp_bfs * bkp) {
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
};

struct los_bfs {
    char FromMerge;
    //char del;
    mpz_class id;
    long long ref;
    ListStructurePtr<bkp_bfs*>*List;

    los_bfs() {
        // id = 0;
        ref = 1;
        // del = d;
        FromMerge = 0;
        List = new ListStructurePtr<bkp_bfs*> (ListStructurePtr<bkp_bfs*>::ORDEM_DECRESCENTE);

    }

    void addElementToList(bkp_bfs * novo) {
        if (novo) {
            List->Add(novo);
            id += novo->id;
        }
    }

    ~los_bfs() {
        //NDELS++;
        //mpz_clear(id.get_mpz_t());
        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
        delete List;
        List = NULL;
    }

    los_bfs * clone() {
        los_bfs*ret = new los_bfs();
        node_list_struct<bkp_bfs*>* iter;
        while ((iter = List->nextFromLastAcc()) != NULL) {
            ret->addElementToList(iter->element);
        }
        return ret;
    }

    mpz_class getId() const {
        //        node_list_struct<bkp_bfs*>* iter;
        //        mpz_class soma;
        //        if (List->getSize() == 1) {
        //            return List->peekFirst()->id;
        //        } else {
        //            while ((iter = List->nextFromLastAcc()) != NULL) {
        //                soma += iter->element->id;
        //            }
        //            return soma;
        //        }
        return id;
    }

    bool clean() {
        ref--;
        if (ref == 0) {
            bkp_bfs * bkp;
            while ((bkp = List->RemoveFront()) != NULL) {
                bkp_bfs::downRef(bkp);
            }
            return true;
        }
        return false;
    }
};

struct node_lst_vector {
    mpz_class * List;
    int nElem;
    int size;
    mpz_class id;

    node_lst_vector(int s) {
        //id = 0;
        // del = d;
        List = new mpz_class[s + 1];

        nElem = 0;
        size = s;
    }

    void addElementToList(mpz_class novo) {
        nElem++;
        List[nElem] = novo;
        id += novo;
        AumentaChave();
    }

    void AumentaChave() {
        int i = nElem;
        while ((i > 1) && List[i / 2] < List[i]) {
            mpz_class x = List[i / 2];
            List[i / 2] = List[i];
            List[i] = x;
            i = i / 2;
        }
    }

    mpz_class removeMax() {
        mpz_class max = List[1];
        List[1] = List[nElem];
        nElem--;
        id -= max;
        RefazHeap(1, nElem);
        return max;
    }

    void RefazHeap(int Esq, int Dir) {
        int i = Esq;
        int j = i * 2;
        mpz_class x = List[i];
        while (j <= Dir) {
            if (j < Dir) {
                if (List[j] < List[j + 1]) {
                    j++;
                }
            }
            if (x >= List[j])goto l998;
            List[i] = List[j];
            i = j;
            j = i * 2;
        }
l998:
        List[i] = x;
    }

    ~node_lst_vector() {
        delete [] List;
    }
};

struct node_lst_bfs {
    mpz_class id;
    los_bfs ** List;
    short nElem;
    short First;
    short size;

    node_lst_bfs(int s) {
        //id = 0;
        // del = d;
        List = new los_bfs*[s + 1];
        First = 1;
        nElem = 0;
        size = s;
    }

    void addElementToList(los_bfs * novo) {
        nElem++;
        List[nElem] = novo;
        id += novo->getId();
        AumentaChave();
    }

    void AumentaChave() {
        int i = nElem;
        while ((i > 1) && List[i / 2]->id < List[i]->id) {
            los_bfs*x = List[i / 2];
            List[i / 2] = List[i];
            List[i] = x;
            i = i / 2;
        }
    }

    void addElementToList1(los_bfs * novo) {
        List[size - nElem] = novo;
        nElem++;
        id += novo->getId();
    }

    void addElementToListKK(los_bfs * novo) {
        id += novo->getId();
        List[First - 1] = novo;
        First--;
        // QuickSort(List, First, nElem - 1);
        //        for(int i=First;i<nElem;i++){
        //            cout<<i<<" : "<<List[i]->getId()<<endl;
        //                    
        //        }
    }

    void addListToList(los_bfs**list, int f, int n) {
        for (int i = f; i < n; i++) {
            List[nElem] = list[i];
            List[nElem]->ref++;
            id += list[i]->getId();
            nElem++;
        }
        QuickSort(List, First, nElem - 1);
    }

    void addListToListWOSort(los_bfs**list, int f, int n) {
        for (int i = f; i <= n; i++) {
            nElem++;
            List[nElem] = list[i];
            List[nElem]->ref++;
            id += List[nElem]->getId();

        }
    }

    void cleanList() {
        for (int i = First; i <= nElem; i++) {
            if (List[i]->clean()) {
                delete List[i];
            }
        }
    }

    node_lst_bfs * clone() {
        node_lst_bfs* ret = new node_lst_bfs(size - First);
        for (int i = First, j = 0; i < size; i++, j++) {
            ret->List[j] = List[i]->clone();
        }
        //ret->id=ret->List->GetId();
        return ret;
    }

    void removeElement(los_bfs * elem) {
        id -= elem->getId();
    }

    void sort() {
        QuickSort(List, First, nElem - 1);
    }

    los_bfs * removeFirst() {
        return removeMax();
    }

    los_bfs * removeMax() {
        los_bfs * max = List[First];
        List[First] = List[nElem];
        nElem--;
        id -= max->id;
        RefazHeap(First, nElem, List);
        return max;
    }

    void RefazHeap(int Esq, int Dir, los_bfs**l) {
        int i = Esq;
        int j = i * 2;
        los_bfs * x = l[i];
        while (j <= Dir) {
            if (j < Dir) {
                if (l[j]->id < l[j + 1]->id) {
                    j++;
                }
            }
            if (x->id >= l[j]->id)goto l999;
            l[i] = l[j];
            i = j;
            j = i * 2;
        }
l999:
        l[i] = x;
    }

    ~node_lst_bfs() {
        //NDELS++;
        //mpz_clear(id.get_mpz_t());
        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
        delete [] List;
        List = NULL;
    }

    mpz_class getId() const {
        return id;
    }

    int getSize() {
        return nElem;
    }

    los_bfs * peekFirst() {
        return List[First];
    }

    void print() {
        for (int i = First; i <= nElem; i++) {
            cout << i << " : " << List[i]->id << endl;
        }
    }
};

struct node_lst_bfs_mpz {
    mpz_class id;
    number_element_mpz ** List;
    short nElem;
    short First;
    short size;

    node_lst_bfs_mpz() {
        //id = 0;
        // del = d;
        //List = new mpz_class[s + 1];
        //List=NULL;
        First = 1;
        nElem = 0;
    }

    node_lst_bfs_mpz(int s) {
        //id = 0;
        // del = d;
        List = new number_element_mpz*[s + 1];
        First = 1;
        nElem = 0;
        size = s;
    }

    void addElementToList(number_element_mpz * novo) {
        nElem++;
        List[nElem] = novo;
        id += novo->id;
       // cout<<novo->id<<endl;
        AumentaChave();
    }

    void AumentaChave() {
        int i = nElem;
        while ((i > 1) && List[i / 2]->id < List[i]->id) {
            number_element_mpz * x = List[i / 2];
            List[i / 2] = List[i];
            List[i] = x;
            i = i / 2;
        }
    }

    void addElementToList1(number_element_mpz * novo) {
        List[size - nElem] = novo;
        nElem++;
        id += novo->id;
    }

    void addElementToListKK(number_element_mpz * novo) {
        id += novo->id;
        List[First - 1] = novo;
        First--;
        // QuickSort(List, First, nElem - 1);
        //        for(int i=First;i<nElem;i++){
        //            cout<<i<<" : "<<List[i]->getId()<<endl;
        //                    
        //        }
    }

    void addListToList(number_element_mpz ** list, int f, int n) {
        for (int i = f; i < n; i++) {
            List[nElem] = list[i];
            id += list[i]->id;
            nElem++;
        }
        // QuickSort(List, First, nElem - 1);
    }

    void addListToListWOSort(number_element_mpz ** list, int f, int n) {
        for (int i = f; i <= n; i++) {
            nElem++;
            List[nElem] = list[i];
            List[nElem]->ref++;
            id += List[nElem]->id;

        }
    }

    //    void cleanList() {
    //       delete [] List;
    //       List=NULL;
    //    }

    number_element_mpz *removeFirst() {
        return removeMax();
    }

    number_element_mpz * removeMax() {
        number_element_mpz * max = List[First];
        List[First] = List[nElem];
        List[nElem]=NULL;
        nElem--;
        id -= max->id;
        RefazHeap(First, nElem);
        return max;
    }

    void RefazHeap(int Esq, int Dir) {
        int i = Esq;
        int j = i * 2;
        number_element_mpz * x = List[i];
        while (j <= Dir) {
            if (j < Dir) {
                if (List[j]->id < List[j + 1]->id) {
                    j++;
                }
            }
            if (x->id >= List[j]->id)goto l999;
            List[i] = List[j];
            i = j;
            j = i * 2;
        }
l999:
        List[i] = x;
    }
    void clean(){
        for(int i=1;i<=nElem;i++){
            List[i]->ref--;
            if(List[i]->ref==0){
                delete List[i];
            }
        }
        delete [] List;
    }
    ~node_lst_bfs_mpz() {
        //NDELS++;
        //mpz_clear(id.get_mpz_t());
        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
        for(int i=1;i<=nElem;i++){
            List[i]->ref--;
            if(List[i]->ref==0){
                delete List[i];
            }
        }
        delete [] List;
        //List = NULL;
    }

    mpz_class getId() const {
        return id;
    }

    int getSize() {
        return nElem;
    }

    mpz_class peekFirst() {
        return List[First]->id;
    }

    void print() {
        for (int i = First; i <= nElem; i++) {
            cout << i << " : " << List[i]->id << endl;
        }
    }
};
// Indices into a subtree array
//     NOTE: I would place this inside the AvlNode class but 
//           when I do, g++ complains when I use dir_t. Even
//           when I prefix it with AvlNode:: or AvlNode<KeyType>::
//           (If you can get this working please let me know)
//




// AvlNode -- Class to implement an AVL Tree
//

//class los_bfs {
//public:
//    // Max number of subtrees per node
//    ListStructurePtr<bkp_bfs*>*List;
//    int * ref;
//    char fromMerge;
//    enum {
//        MAX_SUBTREES = 2
//    };
//
//    // Return the opposite direction of the given index
//
//    static dir_t
//    Opposite(dir_t dir) {
//        return dir_t(1 - int(dir));
//    }
//    // ----- Constructors and destructors: 
//
//    los_bfs();
//    los_bfs(ListStructurePtr<bkp_bfs*>*l, int * r);
//    virtual ~los_bfs(void);
//
//    void addElementToList(bkp_bfs * novo) {
//        List->Add(novo);
//    }
//
//    //    ~los_bfs() {
//    //        //NDELS++;
//    //        //mpz_clear(id.get_mpz_t());
//    //        //number_element_mpz * nelm = static_cast<number_element_mpz*> (List->peekFirst()->element);
//    //        delete List;
//    //        List = NULL;
//    //    }
//
//    los_bfs * clone() {
//        los_bfs*ret = new los_bfs();
//        node_list_struct<bkp_bfs*>* iter;
//        while ((iter = List->nextFromLastAcc()) != NULL) {
//            bkp_bfs::upRef(iter->element);
//            ret->addElementToList(iter->element);
//        }
//        return ret;
//    }
//
//    los_bfs * copy() {
//        los_bfs*ret = new los_bfs(List, ref);
//        return ret;
//    }
//
//    mpz_class getId() const {
//        node_list_struct<bkp_bfs*>* iter;
//        mpz_class soma;
//        if (List->getSize() == 1) {
//            return List->peekFirst()->id;
//        } else {
//            while ((iter = List->nextFromLastAcc()) != NULL) {
//                soma += iter->element->id;
//            }
//            return soma;
//        }
//
//    }
//
//    bool clean() {
//        ref[0]--;
//        if (ref[0] == 0) {
//            bkp_bfs * bkp;
//            while ((bkp = List->RemoveFront()) != NULL) {
//                bkp_bfs::downRef(bkp);
//            }
//            return true;
//        } else {
//            ref = NULL;
//            List = NULL;
//        }
//        return false;
//    }
//    // ----- Query attributes:
//
//    // Get this node's data
//
//    // Get this node's key field
//
//    const los_bfs *
//    Key() const {
//        return this;
//    }
//    // Query the balance factor, it will be a value between -1 .. 1
//    // where:
//    //     -1 => left subtree is taller than right subtree
//    //      0 => left and right subtree are equal in height
//    //      1 => right subtree is taller than left subtree
//
//    short
//    Bal(void) const {
//        return myBal;
//    }
//
//    // Get the item at the top of the left/right subtree of this
//    // item (the result may be NULL if there is no such item).
//    //
//
//    los_bfs *
//    Subtree(dir_t dir) const {
//        return mySubtree[dir];
//    }
//
//    // ----- Search/Insert/Delete
//    //
//    //   NOTE: These are all static functions instead of member functions
//    //         because most of them need to modify the given tree root
//    //         pointer. If these were instance member functions than
//    //         that would correspond to having to modify the 'this'
//    //         pointer, which is not allowed in C++. Most of the 
//    //         functions that are static and which take an AVL tree
//    //         pointer as a parameter are static for this reason.
//
//    // Look for the given key, return NULL if not found,
//    // otherwise return the item's address.
//    static los_bfs *
//    Search(los_bfs * key, los_bfs * root, cmp_t cmp = EQ_CMP);
//
//    // Insert the given key, return NULL if it was inserted,
//    // otherwise return the existing item with the same key.
//    static los_bfs *
//    Insert(los_bfs* item, los_bfs * & root);
//
//    // Delete the given key from the tree. Return the corresponding
//    // node, or return NULL if it was not found.
//    static los_bfs *
//    Delete(los_bfs * key, los_bfs * & root, cmp_t cmp = EQ_CMP);
//    static los_bfs* RemoveMax(los_bfs*&root, int & change);
//    static los_bfs* peekFirst(los_bfs*&root);
//    static void InsertTreeOnTree(los_bfs*&root, node_lst_bfs*Dest);
//    static void clone(los_bfs*root, node_lst_bfs*Dest);
//    static void clear(los_bfs*root);
//    // Verification 
//
//    // Return the height of this tree
//    int
//    Height() const;
//
//    // Verify this tree is a valid AVL tree, return TRUE if it is,
//    // return FALSE otherwise
//    int
//    Check() const;
//
//    void SetMyBal(short myBal) {
//        this->myBal = myBal;
//    }
//
//    // If you want to provide your own allocation scheme than simply
//    // #define the preprocessor manifest constant named CUSTOM_ALLOCATE
//    // and make sure you provide and link with your own overloaded
//    // versions of operators "new" and "delete" for this class.
//#ifdef CUSTOM_ALLOCATE
//    void *
//    operator new(size_t);
//
//    void
//    operator delete(void *);
//#endif  /* CUSTOM_ALLOCATE */
//
//
//private:
//
//    // ----- Private data
//    los_bfs * mySubtree[MAX_SUBTREES]; // Pointers to subtrees
//    short myBal; // Balance factor
//
//    // Reset all subtrees to null and clear the balance factor
//
//    void
//    Reset(void) {
//        myBal = 0;
//        mySubtree[LEFT] = mySubtree[RIGHT] = NULL;
//    }
//
//    // ----- Routines that do the *real* insertion/deletion
//
//    // Insert the given key into the given tree. Return the node if
//    // it already exists. Otherwise return NULL to indicate that
//    // the key was successfully inserted.  Upon return, the "change"
//    // parameter will be '1' if the tree height changed as a result
//    // of the insertion (otherwise "change" will be 0).
//    static los_bfs*
//    Insert(los_bfs* item,
//            los_bfs * & root,
//            int & change);
//
//    // Delete the given key from the given tree. Return NULL if the
//    // key is not found in the tree. Otherwise return a pointer to the
//    // node that was removed from the tree.  Upon return, the "change"
//    // parameter will be '1' if the tree height changed as a result
//    // of the deletion (otherwise "change" will be 0).
//    static los_bfs*
//    Delete(los_bfs* key,
//            los_bfs * & root,
//            int & change,
//            cmp_t cmp = EQ_CMP);
//    // Routines for rebalancing and rotating subtrees
//
//    // Perform an XX rotation for the given direction 'X'.
//    // Return 1 if the tree height changes due to rotation,
//    // otherwise return 0.
//    static int
//    RotateOnce(los_bfs * & root, dir_t dir);
//
//    // Perform an XY rotation for the given direction 'X'
//    // Return 1 if the tree height changes due to rotation,
//    // otherwise return 0.
//    static int
//    RotateTwice(los_bfs * & root, dir_t dir);
//
//    // Rebalance a (sub)tree if it has become imbalanced
//    static int
//    ReBalance(los_bfs * & root);
//
//    // Perform a comparison of the given key against the given
//    // item using the given criteria (min, max, or equivalence
//    // comparison). Returns:
//    //   EQ_CMP if the keys are equivalent
//    //   MIN_CMP if this key is less than the item's key
//    //   MAX_CMP if this key is greater than item's key
//    cmp_t
//    Compare(los_bfs* key, cmp_t cmp = EQ_CMP) const;
//    cmp_t
//    Compare(const los_bfs* key, cmp_t cmp = EQ_CMP) const;
//
//private:
//    // Disallow copying and assignment
//    los_bfs(const los_bfs &);
//    los_bfs & operator=(const los_bfs &);
//
//};
//
//
//// Class AvlTree is a simple container object to "house" an AvlNode
//// that represents the root-node of and AvlTree. Most of the member
//// functions simply delegate to the root AvlNode.
//
//struct node_lst_bfs {
//private:
//    // Disallow copying and assingment
//    node_lst_bfs(const node_lst_bfs &);
//    node_lst_bfs & operator=(const node_lst_bfs &);
//
//    // Member data
//    los_bfs * myRoot; // The root of the tree
//    int Size;
//    mpz_class id;
//public:
//    // Constructor and destructor
//
//    node_lst_bfs() : myRoot(NULL) {
//        Size = 0;
//        id = 0;
//    };
//
//    ~node_lst_bfs() {
//        if (myRoot) delete myRoot;
//    }
//
//    // Dump the tree to the given output stream
//    void
//    DumpTree(ostream & os) const;
//
//    // See if the tree is empty
//
//    int
//    IsEmpty() const {
//        return (myRoot == NULL);
//    }
//    void setRootToNULL(){
//        myRoot=NULL;
//    }
//    // Search, Insert, Delete, and Check
//
//    los_bfs *
//            Search(los_bfs * key, cmp_t cmp = EQ_CMP) {
//        return los_bfs::Search(key, myRoot, cmp);
//    }
//
//    los_bfs *
//            Insert(los_bfs * item) {
//        Size++;
//        id += item->getId();
//        return los_bfs::Insert(item, myRoot);
//    }
//
//    los_bfs *
//            Delete(los_bfs* key, cmp_t cmp = EQ_CMP) {
//        los_bfs* a = los_bfs::Delete(key, myRoot, cmp);
//        if (a != NULL) {
//            Size--;
//        }
//        return a;
//    }
//
//    los_bfs * RemoveMax() {
//        int change;
//        Size--;
//        los_bfs* t = los_bfs::RemoveMax(myRoot, change);
//        id -= t->getId();
//        return t;
//    }
//
//    los_bfs * peekFirst() {
//        return los_bfs::peekFirst(myRoot);
//    }
//
//    void InsertTreeOnTree(node_lst_bfs * Dest) {
//        los_bfs::InsertTreeOnTree(myRoot, Dest);
//    }
//
//    node_lst_bfs * clone() {
//        node_lst_bfs*ret = new node_lst_bfs();
//        los_bfs::clone(myRoot, ret);
//        return ret;
//    }
//
//    void cleanList() {
//        los_bfs::clear(myRoot);
//        myRoot = NULL;
//    }
//
//    int
//    Check() const {
//        return (myRoot) ? myRoot->Check() : 1;
//    }
//
//    void setSize(int Size) {
//        this->Size = Size;
//    }
//
//    int getSize() const {
//        return Size;
//    }
//
//    los_bfs * GetMyRoot() const {
//        return myRoot;
//    }
//
//    mpz_class GetId() const {
//        return id;
//    }
//
//    void addElementToList(los_bfs * novo) {
//        Insert(novo);
//        //id += novo->getId();
//    }
//
//    void addListToList(node_lst_bfs*list) {
//        list->InsertTreeOnTree(this);
//    }
//
//    void removeElement(los_bfs * elem) {
//        Delete(elem);
//    }
//
//    los_bfs * removeFirst() {
//        return RemoveMax();
//    }
//
//    mpz_class getId() const {
//        return id;
//    }
//
//};


#endif  /* AVL_H */
