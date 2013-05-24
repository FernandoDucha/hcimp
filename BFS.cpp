//// <plaintext>
//#include <stdlib.h>
#include "BFS.h"
//
//void los_bfs::clear(los_bfs*root) {
//    if (root == NULL) {
//        return;
//    } else if (root->mySubtree[LEFT] == NULL && root->mySubtree[RIGHT] == NULL) {
//        //Dest->Insert(root->myData);
//        root->clean();
//        delete root;
//
//    } else if (root->mySubtree[LEFT] == NULL && root->mySubtree[RIGHT] != NULL) {
//        clear(root->mySubtree[RIGHT]);
//        root->clean();
//        root->mySubtree[RIGHT] = NULL;
//        delete root;
//    } else if (root->mySubtree[LEFT] != NULL && root->mySubtree[RIGHT] == NULL) {
//        clear(root->mySubtree[LEFT]);
//        root->clean();
//        root->mySubtree[LEFT] = NULL;
//        delete root;
//    } else {
//        clear(root->mySubtree[RIGHT]);
//        clear(root->mySubtree[LEFT]);
//        root->clean();
//        root->mySubtree[RIGHT] = root->mySubtree[LEFT] = NULL;
//        delete root;
//    }
//}
//
//void los_bfs::clone(los_bfs*root, node_lst_bfs*Dest) {
//    ListStructurePtr<los_bfs*> * list = new ListStructurePtr<los_bfs*>(ListStructurePtr<los_bfs*>::ORDEM_CRESCENTE);
//    list->append(root);
//    while (list->getSize() > 0) {
//        los_bfs*n = list->RemoveFront();
//        if (n->mySubtree[LEFT] == NULL && n->mySubtree[RIGHT] == NULL) {
//            Dest->Insert(n->clone());
//        } else if (n->mySubtree[LEFT] == NULL && n->mySubtree[RIGHT] != NULL) {
//            //InsertTreeOnTree(root->mySubtree[RIGHT], Dest);
//            list->append(n->mySubtree[RIGHT]);
//            Dest->Insert(n->clone());
//            //Dest->Insert(root->myData);
//        } else if (n->mySubtree[LEFT] != NULL && n->mySubtree[RIGHT] == NULL) {
//            list->append(n->mySubtree[LEFT]);
//            Dest->Insert(n->clone());
//            //InsertTreeOnTree(root->mySubtree[LEFT], Dest);
//            //Dest->Insert(root->myData);
//        } else {
//            list->append(n->mySubtree[LEFT]);
//            list->append(n->mySubtree[RIGHT]);
//            Dest->Insert(n->clone());
//            //InsertTreeOnTree(root->mySubtree[RIGHT], Dest);
//            //InsertTreeOnTree(root->mySubtree[LEFT], Dest);
//            //Dest->Insert(root->myData);
//        }
//    }
//}
//
//void los_bfs::InsertTreeOnTree(los_bfs*&root, node_lst_bfs*Dest) {
//    if (root == NULL) {
//        return;
//    } else if (root->mySubtree[LEFT] == NULL && root->mySubtree[RIGHT] == NULL) {
//        los_bfs * t = root->copy();
//        t->ref[0]++;
//        Dest->Insert(t);
//    } else if (root->mySubtree[LEFT] == NULL && root->mySubtree[RIGHT] != NULL) {
//        InsertTreeOnTree(root->mySubtree[RIGHT], Dest);
//        los_bfs * t = root->copy();
//        t->ref[0]++;
//        Dest->Insert(t);
//    } else if (root->mySubtree[LEFT] != NULL && root->mySubtree[RIGHT] == NULL) {
//        InsertTreeOnTree(root->mySubtree[LEFT], Dest);
//        los_bfs * t = root->copy();
//        t->ref[0]++;
//        Dest->Insert(t);
//    } else {
//        los_bfs * t = root->copy();
//        t->ref[0]++;
//        Dest->Insert(t);
//        InsertTreeOnTree(root->mySubtree[RIGHT], Dest);
//        InsertTreeOnTree(root->mySubtree[LEFT], Dest);
//
//    }
//}
//
//los_bfs * los_bfs::peekFirst(los_bfs*&root) {
//    if (root->mySubtree[LEFT] == NULL && root->mySubtree[RIGHT] == NULL) {
//        return root;
//    } else if (root->mySubtree[RIGHT] == NULL && root->mySubtree[LEFT] != NULL) {
//        return root;
//    } else {
//        return peekFirst(root->mySubtree[RIGHT]);
//    }
//}
//
//los_bfs * los_bfs::Insert(los_bfs* item, los_bfs * & root) {
//    int change;
//    return Insert(item, root, change);
//}
//
//los_bfs * los_bfs::Delete(los_bfs * key, los_bfs * & root, cmp_t cmp) {
//    int change;
//    return Delete(key, root, change, cmp);
//}
//
//los_bfs * los_bfs::Insert(los_bfs* item, los_bfs * & root, int & change) {
//    // See if the tree is empty
//    if (root == NULL) {
//        // Insert new node here 
//        root = item;
//        change = HEIGHT_CHANGE;
//        return NULL;
//    }
//
//    // Initialize
//    los_bfs * found = NULL;
//    int increase = 0;
//
//    // Compare items and determine which direction to search
//    cmp_t result = root->Compare(item);
//    dir_t dir = (result == MIN_CMP) ? LEFT : RIGHT;
//
//    if (result != EQ_CMP) {
//        // Insert into "dir" subtree 
//        found = Insert(item, root->mySubtree[dir], change);
//        if (found)
//            return found; // already here - dont insert
//        increase = result * change; // set balance factor increment
//    } else { // key already in tree at this node
//        increase = HEIGHT_NOCHANGE;
//        return root;
//    }
//
//    root->myBal += increase; // update balance factor 
//
//    // ----------------------------------------------------------------------
//    // re-balance if needed -- height of current tree increases only if its
//    // subtree height increases and the current tree needs no rotation.
//    // ----------------------------------------------------------------------
//
//    change = (increase && root->myBal)
//            ? (1 - ReBalance(root))
//            : HEIGHT_NOCHANGE;
//    return NULL;
//}
//
//los_bfs * los_bfs::Delete(los_bfs * key, los_bfs * & root, int & change, cmp_t cmp) {
//    // See if the tree is empty
//    if (root == NULL) {
//        // Key not found
//        change = HEIGHT_NOCHANGE;
//        return NULL;
//    }
//
//    // Initialize
//    los_bfs* found = NULL;
//    int decrease = 0;
//
//    // Compare items and determine which direction to search
//    cmp_t result = root->Compare(key, cmp);
//    dir_t dir = (result == MIN_CMP) ? LEFT : RIGHT;
//
//    if (result != EQ_CMP) {
//        // Delete from "dir" subtree 
//        found = Delete(key, root->mySubtree[dir], change, cmp);
//        if (!found) return found; // not found - can't delete
//        decrease = result * change; // set balance factor decrement
//    } else { // Found key at this node
//        // set return value
//
//        // ---------------------------------------------------------------------
//        // At this point we know "result" is zero and "root" points to
//        // the node that we need to delete.  There are three cases:
//        //
//        //    1) The node is a leaf.  Remove it and return.
//        //
//        //    2) The node is a branch (has only 1 child). Make "root"
//        //       (the pointer to this node) point to the child.
//        //
//        //    3) The node has two children. We swap items with the successor
//        //       of "root" (the smallest item in its right subtree) and delete
//        //       the successor from the right subtree of "root".  The
//        //       identifier "decrease" should be reset if the subtree height
//        //       decreased due to the deletion of the successor of "root".
//        // ---------------------------------------------------------------------
//
//        if ((root->mySubtree[LEFT] == NULL) &&
//                (root->mySubtree[RIGHT] == NULL)) {
//            found = root;
//            // We have a leaf -- remove it
//            root = NULL;
//            change = HEIGHT_CHANGE; // height changed from 1 to 0
//            return found;
//        } else if ((root->mySubtree[LEFT] == NULL) ||
//                (root->mySubtree[RIGHT] == NULL)) {
//            // We have one child -- only child becomes new root 
//            los_bfs * toDelete = root;
//            root = root->mySubtree[(root->mySubtree[RIGHT]) ? RIGHT : LEFT];
//            change = HEIGHT_CHANGE; // We just shortened the subtree
//            // Null-out the subtree pointers so we dont recursively delete
//            toDelete->mySubtree[LEFT] = toDelete->mySubtree[RIGHT] = NULL;
//            return toDelete;
//        } else {
//            // We have two children -- find successor and replace our current
//            // data item with that of the successor
//            found = root->copy();
//            los_bfs * f = Delete(key, root->mySubtree[RIGHT], decrease, MIN_CMP);
//            root->List = f->List;
//            root->ref = f->ref;
//            f->List = NULL;
//            f->ref = NULL;
//            //delete f;
//        }
//    }
//
//    root->myBal -= decrease; // update balance factor 
//
//    // ------------------------------------------------------------------------
//    // Rebalance if necessary -- the height of current tree changes if one
//    // of two things happens: (1) a rotation was performed which changed
//    // the height of the subtree (2) the subtree height decreased and now
//    // matches the height of its other subtree (so the current tree now
//    // has a zero balance when it previously did not).
//    // ------------------------------------------------------------------------
//    //change = (decrease) ? ((root->myBal) ? balance(root) : HEIGHT_CHANGE)
//    //                    : HEIGHT_NOCHANGE ;
//    if (decrease) {
//        if (root->myBal) {
//            change = ReBalance(root); // rebalance and see if height changed
//        } else {
//            change = HEIGHT_CHANGE; // balanced because subtree decreased
//        }
//    } else {
//        change = HEIGHT_NOCHANGE;
//    }
//
//    return found;
//}
//
//los_bfs* los_bfs::RemoveMax(los_bfs*&root, int & change) {
//    // See if the tree is empty
//    if (root == NULL) {
//        // Key not found
//        change = HEIGHT_NOCHANGE;
//        return NULL;
//    }
//
//    // Initialize
//    los_bfs* found = NULL;
//    int decrease = 0;
//
//    // Compare items and determine which direction to search
//    cmp_t result = MAX_CMP; // root->Compare(key, cmp);
//    //dir_t dir = (result == MIN_CMP) ? LEFT : RIGHT;
//
//
//    // Delete from "dir" subtree 
//
//    found = root; // set return value
//
//    // ---------------------------------------------------------------------
//    // At this point we know "result" is zero and "root" points to
//    // the node that we need to delete.  There are three cases:
//    //
//    //    1) The node is a leaf.  Remove it and return.
//    //
//    //    2) The node is a branch (has only 1 child). Make "root"
//    //       (the pointer to this node) point to the child.
//    //
//    //    3) The node has two children. We swap items with the successor
//    //       of "root" (the smallest item in its right subtree) and delete
//    //       the successor from the right subtree of "root".  The
//    //       identifier "decrease" should be reset if the subtree height
//    //       decreased due to the deletion of the successor of "root".
//    // ---------------------------------------------------------------------
//
//    if ((root->mySubtree[LEFT] == NULL) &&
//            (root->mySubtree[RIGHT] == NULL)) {
//        // We have a leaf -- remove it
//        //delete root;
//        root = NULL;
//        change = HEIGHT_CHANGE; // height changed from 1 to 0
//        return found;
//    } else if ((root->mySubtree[LEFT] == NULL) && (root->mySubtree[RIGHT] != NULL)) {
//        found = RemoveMax(root->mySubtree[RIGHT], change);
//        if (!found) return found; // not found - can't delete
//        decrease = result * change; // set balance factor decrement
//    } else if ((root->mySubtree[LEFT] != NULL) && (root->mySubtree[RIGHT] == NULL)) {
//        // We have one child -- only child becomes new root 
//        //los_bfs * toDelete = root;
//        root = root->mySubtree[(root->mySubtree[RIGHT]) ? RIGHT : LEFT];
//        change = HEIGHT_CHANGE; // We just shortened the subtree
//        // Null-out the subtree pointers so we dont recursively delete
//        found->mySubtree[LEFT] = found->mySubtree[RIGHT] = NULL;
//        //delete toDelete;
//        return found;
//    } else {
//        // We have two children -- find successor and replace our current
//        // data item with that of the successor
//        found = RemoveMax(root->mySubtree[RIGHT], change);
//        if (!found) return found; // not found - can't delete
//        decrease = result * change; // set balance factor decrement
//    }
//
//
//    root->myBal -= decrease; // update balance factor 
//
//    // ------------------------------------------------------------------------
//    // Rebalance if necessary -- the height of current tree changes if one
//    // of two things happens: (1) a rotation was performed which changed
//    // the height of the subtree (2) the subtree height decreased and now
//    // matches the height of its other subtree (so the current tree now
//    // has a zero balance when it previously did not).
//    // ------------------------------------------------------------------------
//    //change = (decrease) ? ((root->myBal) ? balance(root) : HEIGHT_CHANGE)
//    //                    : HEIGHT_NOCHANGE ;
//    if (decrease) {
//        if (root->myBal) {
//            change = ReBalance(root); // rebalance and see if height changed
//        } else {
//            change = HEIGHT_CHANGE; // balanced because subtree decreased
//        }
//    } else {
//        change = HEIGHT_NOCHANGE;
//    }
//
//    return found;
//}
//
//los_bfs::los_bfs(ListStructurePtr<bkp_bfs*>*l, int * r) {
//    List = l;
//    ref = r;
//    fromMerge = 0;
//    Reset();
//}
//
//los_bfs::los_bfs() {
//    // id = 0;
//    List = new ListStructurePtr<bkp_bfs*>(ListStructurePtr<bkp_bfs*>::ORDEM_DECRESCENTE);
//    ref = new int[1];
//    ref[0] = 1;
//    fromMerge = 0;
//    Reset();
//}
//
//los_bfs::~los_bfs(void) {
//    if (mySubtree[LEFT]) delete mySubtree[LEFT];
//    if (mySubtree[RIGHT]) delete mySubtree[RIGHT];
//    delete List;
//    delete [] ref;
//}
//
//// ------------------------------------------------- Rotating and Re-Balancing
//
//int
//los_bfs::RotateOnce(los_bfs * & root, dir_t dir) {
//    dir_t otherDir = Opposite(dir);
//    los_bfs * oldRoot = root;
//
//    // See if otherDir subtree is balanced. If it is, then this
//    // rotation will *not* change the overall tree height.
//    // Otherwise, this rotation will shorten the tree height.
//    int heightChange = (root->mySubtree[otherDir]->myBal == 0)
//            ? HEIGHT_NOCHANGE
//            : HEIGHT_CHANGE;
//
//    // assign new root
//    root = oldRoot->mySubtree[otherDir];
//
//    // new-root exchanges it's "dir" mySubtree for it's parent
//    oldRoot->mySubtree[otherDir] = root->mySubtree[dir];
//    root->mySubtree[dir] = oldRoot;
//
//    // update balances
//    oldRoot->myBal = -((dir == LEFT) ? --(root->myBal) : ++(root->myBal));
//
//    return heightChange;
//}
//
//int los_bfs::RotateTwice(los_bfs * & root, dir_t dir) {
//    dir_t otherDir = Opposite(dir);
//    los_bfs * oldRoot = root;
//    los_bfs * oldOtherDirSubtree = root->mySubtree[otherDir];
//
//    // assign new root
//    root = oldRoot->mySubtree[otherDir]->mySubtree[dir];
//
//    // new-root exchanges it's "dir" mySubtree for it's grandparent
//    oldRoot->mySubtree[otherDir] = root->mySubtree[dir];
//    root->mySubtree[dir] = oldRoot;
//
//    // new-root exchanges it's "other-dir" mySubtree for it's parent
//    oldOtherDirSubtree->mySubtree[dir] = root->mySubtree[otherDir];
//    root->mySubtree[otherDir] = oldOtherDirSubtree;
//
//    // update balances
//    root->mySubtree[LEFT]->myBal = -MAX(root->myBal, 0);
//    root->mySubtree[RIGHT]->myBal = -MIN(root->myBal, 0);
//    root->myBal = 0;
//
//    // A double rotation always shortens the overall height of the tree
//    return HEIGHT_CHANGE;
//}
//
//int
//los_bfs::ReBalance(los_bfs * & root) {
//    int heightChange = HEIGHT_NOCHANGE;
//
//    if (LEFT_IMBALANCE(root->myBal)) {
//        // Need a right rotation
//        if (root->mySubtree[LEFT]->myBal == RIGHT_HEAVY) {
//            // RL rotation needed
//            heightChange = RotateTwice(root, RIGHT);
//        } else {
//            // RR rotation needed
//            heightChange = RotateOnce(root, RIGHT);
//        }
//    } else if (RIGHT_IMBALANCE(root->myBal)) {
//        // Need a left rotation
//        if (root->mySubtree[RIGHT]->myBal == LEFT_HEAVY) {
//            // LR rotation needed
//            heightChange = RotateTwice(root, LEFT);
//        } else {
//            // LL rotation needed
//            heightChange = RotateOnce(root, LEFT);
//        }
//    }
//
//    return heightChange;
//}
//
//// ------------------------------------------------------- Comparisons
//
//cmp_t
//los_bfs::Compare(los_bfs * key, cmp_t cmp) const {
//    switch (cmp) {
//        case EQ_CMP: // Standard comparison
//            return (key->getId() == getId()) ? EQ_CMP
//                    : ((key->getId() < getId()) ? MIN_CMP : MAX_CMP);
//        case MIN_CMP: // Find the minimal element in this tree
//            return (mySubtree[LEFT] == NULL) ? EQ_CMP : MIN_CMP;
//
//        case MAX_CMP: // Find the maximal element in this tree
//            return (mySubtree[RIGHT] == NULL) ? EQ_CMP : MAX_CMP;
//    }
//}
//
//cmp_t
//los_bfs::Compare(const los_bfs * key, cmp_t cmp) const {
//    switch (cmp) {
//        case EQ_CMP: // Standard comparison
//            return (key->getId() == getId()) ? EQ_CMP
//                    : ((key->getId() < getId()) ? MIN_CMP : MAX_CMP);
//        case MIN_CMP: // Find the minimal element in this tree
//            return (mySubtree[LEFT] == NULL) ? EQ_CMP : MIN_CMP;
//
//        case MAX_CMP: // Find the maximal element in this tree
//            return (mySubtree[RIGHT] == NULL) ? EQ_CMP : MAX_CMP;
//    }
//}
//// ------------------------------------------------------- Search/Insert/Delete
//
//los_bfs*
//los_bfs::Search(los_bfs* key, los_bfs * root, cmp_t cmp) {
//    cmp_t result;
//    while (root && (result = root->Compare(key, cmp))) {
//        root = root->mySubtree[(result < 0) ? LEFT : RIGHT];
//    }
//    return (root) ? root : NULL;
//}
//
//
//// --------------------------------------------------------------- Verification
//
//int
//los_bfs::Height() const {
//    int leftHeight = (mySubtree[LEFT]) ? mySubtree[LEFT]->Height() : 0;
//    int rightHeight = (mySubtree[RIGHT]) ? mySubtree[RIGHT]->Height() : 0;
//    return (1 + MAX(leftHeight, rightHeight));
//}
//
//int los_bfs::Check() const {
//    int valid = 1;
//
//    // First verify that subtrees are correct
//    if (mySubtree[LEFT]) valid *= mySubtree[LEFT]->Check();
//    if (mySubtree[RIGHT]) valid *= mySubtree[RIGHT]->Check();
//
//    // Now get the height of each subtree
//    int leftHeight = (mySubtree[LEFT]) ? mySubtree[LEFT]->Height() : 0;
//    int rightHeight = (mySubtree[RIGHT]) ? mySubtree[RIGHT]->Height() : 0;
//
//    // Verify that AVL tree property is satisfied
//    int diffHeight = rightHeight - leftHeight;
//    if (LEFT_IMBALANCE(diffHeight) || RIGHT_IMBALANCE(diffHeight)) {
//        valid = 0;
//        cerr << "Height difference is " << diffHeight
//                << " at node " << Key() << endl;
//    }
//
//    // Verify that balance-factor is correct
//    if (diffHeight != myBal) {
//        valid = 0;
//        cerr << "Height difference " << diffHeight
//                << " doesnt match balance-factor of " << myBal
//                << " at node " << Key() << endl;
//    }
//
//    // Verify that search-tree property is satisfied
//    if ((mySubtree[LEFT])
//            &&
//            (mySubtree[LEFT]->Compare(Key()) == MIN_CMP)) {
//        valid = 0;
//        cerr << "Node " << Key() << " is *smaller* than left subtree"
//                << mySubtree[LEFT]->Key() << endl;
//    }
//    if ((mySubtree[RIGHT])
//            &&
//            (mySubtree[RIGHT]->Compare(Key()) == MAX_CMP)) {
//        valid = 0;
//        cerr << "Node " << Key() << " is *greater* than right subtree"
//                << mySubtree[RIGHT]->Key() << endl;
//    }
//
//    return valid;
//}
//
////----------------------------------------------- Routines for dumping the tree
//
////static inline ostream &
////Indent(ostream & os, int len) {
////    for (int i = 0; i < len; i++) {
////        os << ' ';
////    }
////    return os;
////}
//
//static void
//Dump(ostream & os,
//        TraversalOrder order,
//        const los_bfs * node,
//        int level = 0) {
//    unsigned len = (level * 5) + 1;
//    if ((order == LTREE) && (node->Subtree(LEFT) == NULL)) {
//        Indent(os, len) << "     **NULL**" << endl;
//    }
//    if (order == KEY) {
//        Indent(os, len) << node->Key() << ":" << node->Bal() << endl;
//    }
//    if ((order == RTREE) && (node->Subtree(RIGHT) == NULL)) {
//        Indent(os, len) << "     **NULL**" << endl;
//    }
//}
//
//static void
//Dump(ostream & os, const los_bfs * node, int level = 0) {
//    if (node == NULL) {
//        os << "***EMPTY TREE***" << endl;
//    } else {
//        Dump(os, RTREE, node, level);
//        if (node->Subtree(RIGHT) != NULL) {
//            Dump(os, node->Subtree(RIGHT), level + 1);
//        }
//        Dump(os, KEY, node, level);
//        if (node->Subtree(LEFT) != NULL) {
//            Dump(os, node->Subtree(LEFT), level + 1);
//        }
//        Dump(os, LTREE, node, level);
//    }// if non-empty tree
//}
//
//void
//node_lst_bfs::DumpTree(ostream & os) const {
//    Dump(os, myRoot);
//}
//
void Particao(int Esq, int Dir, int & i, int & j, los_bfs ** A) {
    los_bfs *x, *w;
    i = Esq;
    j = Dir;
    x = A[(i + j) / 2];
    do {
        while (x->getId() < A[i]->getId()) {
            i++;
        }
        while (x->getId() > A[j]->getId()) {
            j--;
        }
        if (i <= j) {
            w = A[i];
            A[i] = A[j];
            A[j] = w;
            i++;
            j--;
        }
    } while (i <= j);
}

void Ordena(int Esq, int Dir, los_bfs ** A) {
    int i, j;
    Particao(Esq, Dir, i, j, A);
    if (Esq < j) {
        Ordena(Esq, j, A);
    }
    if (i < Dir) {
        Ordena(i, Dir, A);
    }
}

void QuickSort(los_bfs ** A, int start, int final) {
    Ordena(start, final, A);
}

int PesqBinaria(los_bfs * p, los_bfs ** A, int start, int fim) {
    int media = (fim + start) / 2;
    if (A[media]->getId() == p->getId()) {
        return media;
    } else if (A[media]->getId() > p->getId()) {
        return PesqBinaria(p, A, media + 1, fim);
    } else {
        return PesqBinaria(p, A, start, media);
    }
}
//// ---------------------------------------------------------------- Definitions
//
//// Return the minumum of two numbers
//
//
//
//// ----------------------------------------------- Constructors and Destructors
//
//
//
