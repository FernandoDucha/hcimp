/* 
 * File:   CompleteKarmarkarKarp_MPZ.cpp
 * Author: fernando
 * 
 * Created on 5 de Setembro de 2011, 18:02
 */

#include "CompleteKarmarkarKarp_MPZ.h"
pthread_mutex_t mutex1_mpz = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2_mpz = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3_mpz = PTHREAD_MUTEX_INITIALIZER;

CompleteKarmarkarKarp_MPZ::CompleteKarmarkarKarp_MPZ(ListStructure<number_element_mpz> * source, int nroParticoes) {
    nodesInspected = 0;
    nodesPruned = 0;
    raiz = new CKKnode_mpz();
    this->nroParticoes = nroParticoes;
    GenerateRaiz(source);
    // mpz_pow_ui(min->get_mpz_t(), mpz_class(2).get_mpz_t(), source->getSize() + 1);

    //    for (int k = 0; k < 10; k++) {
    //        cout << raiz.nodeList.List->retrieve_K_esimo(k)->element.List->retrieve_K_esimo(0)->element.List->retrieve_K_esimo(0)->element.id << endl;
    //    }
    // raiz.nodeList.List->resetLastAcc();
    // ListOfSums_mpz A = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // ListOfSums_mpz B = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // mergeListOfSums_mpz(A, B);
    c.set_resolution(Cronometro::SEGUNDOS);
    depthFirst(raiz);

}

CompleteKarmarkarKarp_MPZ::CompleteKarmarkarKarp_MPZ(const CompleteKarmarkarKarp_MPZ& orig) {
}

CompleteKarmarkarKarp_MPZ::~CompleteKarmarkarKarp_MPZ() {
    delete comb;
}

void CompleteKarmarkarKarp_MPZ::GenerateRaizBFS(ListStructure<number_element_mpz> *source) {
    for (int i = 0; i < source->getSize(); i++) {
        bkp_bfs * novo = new bkp_bfs(0);
        novo->addElementToList(source->nextFromLastAcc()->element);
        // cout << "raiz:" << novo->id << endl;
        los_bfs * list = new los_bfs();
        list->addElementToList(novo);
        //cout<<list->getId()<<endl;
        raizBFS->nodeList->addElementToList(list);
    }
    // int a = raizBFS->nodeList->Check();
    //    int a=raiz->nodeList->List->Check();
    source->resetLastAcc();
}

void CompleteKarmarkarKarp_MPZ::GenerateRaizDFS(ListStructure<number_element_mpz> *source) {
    for (int i = 0; i < source->getSize(); i++) {
        raizDFS->nodeList.addElementToList(new number_element_mpz(source->nextFromLastAcc()->element.id));
    }
    // int a = raizBFS->nodeList->Check();
    //    int a=raiz->nodeList->List->Check();
    source->resetLastAcc();
}

void CompleteKarmarkarKarp_MPZ::GenerateRaizLDS(ListStructure<number_element_mpz> *source) {
    for (int i = 0; i < source->getSize(); i++) {
        raizLDS->nodeList.addElementToList(new number_element_mpz(source->nextFromLastAcc()->element.id));
    }
    // int a = raizBFS->nodeList->Check();
    //    int a=raiz->nodeList->List->Check();
    source->resetLastAcc();
}

void CompleteKarmarkarKarp_MPZ::GenerateRaizBFS_mpz(ListStructure<number_element_mpz> *source) {
    for (int i = 0; i < source->getSize(); i++) {
        raizBFS_mpz->nodeList.addElementToList(new number_element_mpz(source->nextFromLastAcc()->element.id));
    }
    // int a = raizBFS->nodeList->Check();
    //    int a=raiz->nodeList->List->Check();
    source->resetLastAcc();
}

void CompleteKarmarkarKarp_MPZ::GenerateRaiz(ListStructure<number_element_mpz> * source) {
    for (int i = 0; i < source->getSize(); i++) {
        BookKeeping_mpz * novo = new BookKeeping_mpz(0);
        novo->addElementToList(source->nextFromLastAcc()->element);
        // cout << "raiz:" << novo->id << endl;
        ListOfSums_mpz * list = new ListOfSums_mpz();
        list->addElementToList(novo);
        raiz->nodeList->addElementToList(list);
    }
    //    int a=raiz->nodeList->List->Check();
    source->resetLastAcc();
}

bkp_bfs * CompleteKarmarkarKarp_MPZ::mergeBookKepings(bkp_bfs*A, bkp_bfs*B) {
    bool boolA = false;
    bool boolB = false;
    int i = 0;
    if (A != NULL) {
        i++;
        boolA = true;
    }
    if (B != NULL) {
        i++;
        boolB = true;
    }
    if (boolA || boolB) {
        bkp_bfs * ret = new bkp_bfs(i);
        if (boolA) {
            //A->ref++;
            //A->upRef(A);
            ret->addElementToList(A);
        }
        if (boolB) {
            //B->upRef(B);
            ret->addElementToList(B);
        }
        return ret;
    } else
        return NULL;
}

BookKeeping_mpz * CompleteKarmarkarKarp_MPZ::mergeBookKepings(BookKeeping_mpz * A, BookKeeping_mpz * B) {
    bool boolA = false;
    bool boolB = false;
    int i = 0;
    if (A != NULL) {
        i++;
        boolA = true;
    }
    if (B != NULL) {
        i++;
        boolB = true;
    }
    if (boolA || boolB) {
        BookKeeping_mpz * ret = new BookKeeping_mpz(i);
        if (boolA) {
            //A->ref++;
            //A->upRef(A);
            ret->addElementToList(A);
        }
        if (boolB) {
            //B->upRef(B);
            ret->addElementToList(B);
        }
        return ret;
    } else
        return NULL;
}

inline ListStructurePtr<ListOfSums_mpz*> * CompleteKarmarkarKarp_MPZ::mergeListOfSums1(ListOfSums_mpz* A, ListOfSums_mpz* B) {
    ListStructurePtr<ListOfSums_mpz*>* ret = new ListStructurePtr<ListOfSums_mpz*>(ListStructurePtr<ListOfSums_mpz*>::ORDEM_CRESCENTE);
    bool notmerged[200];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    A->ref--;
    B->ref--;
    if (nonZeroA > nonZeroB) {
        Combinatorics com(nonZeroA + 1, nonZeroB);
        com.generateAllArranges();
        int narr = com.getTotalArranges();
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();

            for (int j = 0; j < nonZeroB; j++) {
                BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(com.getArrangePosition(i, j));
                BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    // bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    los->addElementToList(bkp);
                    //BookKeeping_mpz::upRef(bkp, los);
                }
            }
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[com.getArrangePosition(i, l)] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        // BookKeeping_mpz::upRef(bkp, los);
                        los->addElementToList(bkp);
                    }
                }
            }
            normalize(los);
            ret->Add(los);
        }
    } else {
        Combinatorics com(nonZeroB + 1, nonZeroA);
        com.generateAllArranges();
        //com.printArranges();
        int narr = com.getTotalArranges();
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();
            for (int j = 0; j < nonZeroA; j++) {
                BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(com.getArrangePosition(i, j));
                BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    //bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //                    if (bkp->id == 0) {
                    //                        cout << "merda" << endl;
                    //                    }
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    //BookKeeping_mpz::upRef(bkp, los);
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[com.getArrangePosition(i, l)] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //                        if (bkp->id == 0) {
                        //                            cout << "merda" << endl;
                        //                        }
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        // BookKeeping_mpz::upRef(bkp, los);
                        los->addElementToList(bkp);
                    }
                }
            }

            los = normalize(los);
            // cout << los->id << endl;
            ret->Add(los);
        }
    }
    return ret;
}

inline ListStructurePtr<los_bfs*>* CompleteKarmarkarKarp_MPZ::mergeListOfSums(los_bfs* A, los_bfs*B) {
    ListStructurePtr<los_bfs*>* ret = new ListStructurePtr<los_bfs*>(ListStructurePtr<los_bfs*>::ORDEM_CRESCENTE);
    bool notmerged[200];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    A->ref--;
    B->ref--;
    if (nonZeroA > nonZeroB) {
        int narr = comb->Arranjo(nonZeroA + 1, nonZeroB);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            los_bfs * los = new los_bfs();

            for (int j = 0; j < nonZeroB; j++) {
                bkp_bfs* nodeA = A->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                bkp_bfs*nodeB = B->List->retrieve_K_esimo(j);
                bkp_bfs*bkpA;
                bkp_bfs*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    // bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    los->addElementToList(bkp);
                    bkp_bfs::upRef(bkp);
                }
            }
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    bkp_bfs * nodeA = A->List->retrieve_K_esimo(n);
                    bkp_bfs*nodeB = B->List->retrieve_K_esimo(m);
                    bkp_bfs*bkpA;
                    bkp_bfs*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        bkp_bfs::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            normalize(los);
            ret->Add(los);
        }
    } else {
        int narr = comb->Arranjo(nonZeroB + 1, nonZeroA);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            los_bfs * los = new los_bfs();
            for (int j = 0; j < nonZeroA; j++) {
                bkp_bfs* nodeB = B->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                bkp_bfs*nodeA = A->List->retrieve_K_esimo(j);
                bkp_bfs*bkpA;
                bkp_bfs*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    //bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //                    if (bkp->id == 0) {
                    //                        cout << "merda" << endl;
                    //                    }
                    //bkp->upRef(bkp, los);
                    bkp_bfs::upRef(bkp);
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    bkp_bfs* nodeB = B->List->retrieve_K_esimo(n);
                    bkp_bfs*nodeA = A->List->retrieve_K_esimo(m);
                    bkp_bfs*bkpA;
                    bkp_bfs*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //                        if (bkp->id == 0) {
                        //                            cout << "merda" << endl;
                        //                        }
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        bkp_bfs::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            los = normalize(los);
            ret->Add(los);
        }
    }
    return ret;
}

node_lst_tree * CompleteKarmarkarKarp_MPZ::createTree(node_lst_bfs * A) {
    node_lst_tree * ret = new node_lst_tree();
    for (int i = A->First; i <= A->nElem; i++) {
        ret->addElementToList(A->List[i]);
    }
    return ret;
}

inline ListStructurePtr<los_bfs*>* CompleteKarmarkarKarp_MPZ::mergeListOfSums1(los_bfs* A, los_bfs*B) {
    ListStructurePtr<los_bfs*>* ret = new ListStructurePtr<los_bfs*>(ListStructurePtr<los_bfs*>::ORDEM_CRESCENTE);
    bool notmerged[200];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    A->ref--;
    B->ref--;
    if (nonZeroA > nonZeroB) {
        int narr = comb->Arranjo(nonZeroA + 1, nonZeroB);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            los_bfs * los = new los_bfs();

            for (int j = 0; j < nonZeroB; j++) {
                bkp_bfs* nodeA = A->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                bkp_bfs*nodeB = B->List->retrieve_K_esimo(j);
                bkp_bfs*bkpA;
                bkp_bfs*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    // bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    los->addElementToList(bkp);
                    //bkp_bfs::upRef(bkp);
                }
            }
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    bkp_bfs* nodeA = A->List->retrieve_K_esimo(n);
                    bkp_bfs*nodeB = B->List->retrieve_K_esimo(m);
                    bkp_bfs*bkpA;
                    bkp_bfs*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        //bkp_bfs::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            normalize(los);
            ret->Add(los);
        }
    } else {
        int narr = comb->Arranjo(nonZeroB + 1, nonZeroA);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            los_bfs * los = new los_bfs();
            for (int j = 0; j < nonZeroA; j++) {
                bkp_bfs* nodeB = B->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                bkp_bfs*nodeA = A->List->retrieve_K_esimo(j);
                bkp_bfs*bkpA;
                bkp_bfs*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    //bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //                    if (bkp->id == 0) {
                    //                        cout << "merda" << endl;
                    //                    }
                    //bkp->upRef(bkp, los);
                    //bkp_bfs::upRef(bkp);
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    bkp_bfs* nodeB = B->List->retrieve_K_esimo(n);
                    bkp_bfs*nodeA = A->List->retrieve_K_esimo(m);
                    bkp_bfs*bkpA;
                    bkp_bfs*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    bkp_bfs * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //                        if (bkp->id == 0) {
                        //                            cout << "merda" << endl;
                        //                        }
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        //bkp_bfs::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            los = normalize(los);
            ret->Add(los);
        }
    }
    return ret;
}

inline ListStructurePtr<ListOfSums_mpz*> * CompleteKarmarkarKarp_MPZ::mergeListOfSums(ListOfSums_mpz * A, ListOfSums_mpz * B) {
    ListStructurePtr<ListOfSums_mpz*>* ret = new ListStructurePtr<ListOfSums_mpz*>(ListStructurePtr<ListOfSums_mpz*>::ORDEM_CRESCENTE);
    bool notmerged[200];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    A->ref--;
    B->ref--;
    if (nonZeroA > nonZeroB) {
        int narr = comb->Arranjo(nonZeroA + 1, nonZeroB);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();

            for (int j = 0; j < nonZeroB; j++) {
                BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    // bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    los->addElementToList(bkp);
                    BookKeeping_mpz::upRef(bkp);
                }
            }
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        BookKeeping_mpz::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            normalize(los);
            ret->Add(los);
        }
    } else {
        int narr = comb->Arranjo(nonZeroB + 1, nonZeroA);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();
            for (int j = 0; j < nonZeroA; j++) {
                BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    //bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    //                    if (bkp->id == 0) {
                    //                        cout << "merda" << endl;
                    //                    }
                    //bkp->upRef(bkp, los);
                    //                    bkp->parent->append(los);
                    BookKeeping_mpz::upRef(bkp);
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA; //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        //                        if (bkp->id == 0) {
                        //                            cout << "merda" << endl;
                        //                        }
                        //bkp->upRef(bkp, los);
                        //                        bkp->parent->append(los);
                        BookKeeping_mpz::upRef(bkp);
                        los->addElementToList(bkp);
                    }
                }
            }
            los = normalize(los);
            ret->Add(los);
        }
    }
    return ret;
}

inline ListStructurePtr<ListOfSums_mpz*> * CompleteKarmarkarKarp_MPZ::mergeListOfSums(ListOfSums_mpz* A, ListOfSums_mpz* B, int k) {
    ListStructurePtr<ListOfSums_mpz*>* ret = new ListStructurePtr<ListOfSums_mpz*>(ListStructurePtr<ListOfSums_mpz*>::ORDEM_CRESCENTE);
    bool notmerged[200];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    if (nonZeroA > nonZeroB) {
        //Combinatorics comb(nonZeroA + 1, nonZeroB);
        //comb.generateAllArranges();
        int narr = comb->Arranjo(nonZeroA + 1, nonZeroB);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();
label1:
            for (int j = 0; j < nonZeroB; j++) {
                BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    // bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                if (bkpB != NULL && bkpA != NULL) {
                    int t = 0;
                    if (bkpB->id != 0) {
                        t++;
                    }
                    if (bkpA->id != 0) {
                        t++;
                    }
                    if (k == 0 && t == 2) {
                        i--;
                        if (i < 0) {
                            delete los;
                            return ret;
                        }
                        goto label1;
                    } else if (k == 1 && t == 1) {
                        i--;
                        if (i < 0) {
                            delete los;
                            return ret;
                        }
                        goto label1;
                    }
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeA = A->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }

                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        los->addElementToList(bkp);
                    }
                }
            }
            normalize(los);
            ret->Add(los);
        }
    } else {
        int narr = comb->Arranjo(nonZeroB + 1, nonZeroA);
        comb->setJump(comb->getNFact() / narr);
        for (int i = narr - 1; i >= 0; i--) {
            ListOfSums_mpz * los = new ListOfSums_mpz();
label2:
            for (int j = 0; j < nonZeroA; j++) {
                BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(comb->getArrangePosition(i, j, comb->getJump()));
                BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(j);
                BookKeeping_mpz*bkpA;
                BookKeeping_mpz*bkpB;
                if (nodeA != NULL) {
                    bkpA = nodeA;
                    //bkpA->upRef(bkpA);
                } else {
                    bkpA = NULL;
                }
                if (nodeB != NULL) {
                    bkpB = nodeB;
                    //bkpB->upRef(bkpB);
                } else {
                    bkpB = NULL;
                }
                if (bkpB != NULL && bkpA != NULL) {
                    int t = 0;
                    if (bkpB->id != 0) {
                        t++;
                    }
                    if (bkpA->id != 0) {
                        t++;
                    }
                    if (k == 0 && t == 2) {
                        j = 0;
                        i--;
                        if (i < 0) {
                            delete los;
                            return ret;
                        }
                        goto label2;
                    } else if (k == 1 && t == 1) {
                        j = 0;
                        i--;
                        if (i < 0) {
                            delete los;
                            return ret;
                        }
                        goto label2;
                    }
                }
                BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    los->addElementToList(bkp);
                }
            }
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[comb->getArrangePosition(i, l, comb->getJump())] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(n);
                    BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(m);
                    BookKeeping_mpz*bkpA;
                    BookKeeping_mpz*bkpB;
                    if (nodeA != NULL) {
                        bkpA = nodeA;
                        //bkpA->upRef(bkpA);
                    } else {
                        bkpA = NULL;
                    }
                    if (nodeB != NULL) {
                        bkpB = nodeB;
                        //bkpB->upRef(bkpB);
                    } else {
                        bkpB = NULL;
                    }
                    BookKeeping_mpz * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        los->addElementToList(bkp);
                    }
                }
            }
            los = normalize(los);
            ret->Add(los);
        }
    }
    return ret;
}

//inline void CompleteKarmarkarKarp_MPZ::destroyParent(CKKnode_mpz * Parent) {
//    if (Parent->Parent != NULL) {
//        node_list_struct<CKKnode_mpz*>* childs;
//        bool flag = false;
//        while ((childs = Parent->Parent->children->nextFromLastAcc()) != NULL) {
//            if (childs->element->sondado) {
//                flag = true;
//            } else {
//                flag = false;
//            }
//        }
//        if (flag) {
//            delete Parent->Parent;
//            Parent->Parent = NULL;
//        }
//
//    }
//}

//inline void CompleteKarmarkarKarp_MPZ::subCreateChildrenLDS(CKKnode_mpz * Parent) {
//    int nls = Parent->nodeList->List->getSize();
//
//    nodesInspected[0]++;
//    if (c.elapsed() > 0) {
//        cout << hashSearch->getNElementos() << endl;
//        cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2(mpz_class((char*) min, 10)) << " -- " << getppid() << " -- " << nls << endl;
//        c.end();
//        c.start();
//    }
//    if (nls == 1) {
//        mpz_class temp = Parent->nodeList->List->peekFirst()->element->List->peekFirst()->element->id - Parent->nodeList->List->peekFirst()->element->List->peekLast()->element->id;
//        mpz_class m((char*) min, 10);
//        if (temp < m) {
//            cout << log2(temp + 1) << " -- " << getpid() << endl;
//            strcpy((char*) min, temp.get_str(10).c_str());
//            p->cloneSolutionToBest(Parent->nodeList->List->peekFirst()->element);
//        } else {
//            Parent->cleanNode();
//            Parent->cleanChildren();
//            delete Parent;
//        }
//    } else {
//        ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = NULL;
//        if (!Parent->children_created) {
//            node_list_struct<ListOfSums_mpz*>* A = Parent->nodeList->List->RemoveFront();
//            node_list_struct<ListOfSums_mpz*>* B = Parent->nodeList->List->RemoveFront();
//            childrenCandidates = mergeListOfSums(A->element, B->element);
//            delete A->element;
//            delete B->element;
//            delete A;
//            delete B;
//            node_list_struct<ListOfSums_mpz*>* los;
//
//            while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
//                CKKnode_mpz * nodetemp = new CKKnode_mpz();
//                //los->element->List->PrintLista();
//                nodetemp->nodeList->addElementToList(los->element);
//                nodetemp->nodeList->addListToList(cloneListOfListOfSums(Parent->nodeList->List));
//                nodetemp->Parent = Parent;
//                nodetemp->updateNodeId();
//                Parent->children_created = true;
//                Parent->sondado = true;
//                if (prune(nodetemp)) {
//                    nodetemp->cleanNode();
//                    nodetemp->cleanChildren();
//                    delete nodetemp;
//                    nodesPruned[0]++;
//                } else {
//                    Parent->children->Add(nodetemp);
//                }
//            }
//            node_list_struct<CKKnode_mpz*>*nodetemp; // = Parent->children->nextFromLastAcc();
//            int i = 0;
//            while ((nodetemp = Parent->children->nextFromLastAcc()) != NULL) {
//                if (i % 2 == 0) {
//                    nodetemp->element->left = Parent->left + 1;
//                    nodetemp->element->right = Parent->right;
//                    i++;
//                    subCreateChildrenLDS(nodetemp->element);
//                } else {
//                    nodetemp->element->left = Parent->left;
//                    nodetemp->element->right = Parent->right + 1;
//                    if (!hashSearch->put(nodetemp->element->left, new ToBeSearhed(nodetemp->element, nodetemp->element->right))) {
//                        CKKnode_mpz * n = Parent->children->RemoveObject(nodetemp);
//                        delete n;
//                    }
//                }
//            }
//        }
//        if ((Parent->left == Parent->right) && (Parent->right > 0)) {
//            int a = hashSearch->checkForId(Parent->right);
//            if (a < 0) {
//                hashSearch->setIdMin(Parent->right + 1);
//            } else {
//                hashSearch->setKeyMin(a);
//            }
//        }
//        delete Parent;
//        childrenCandidates->ClearList();
//        delete childrenCandidates;
//    }
//
//}

inline void CompleteKarmarkarKarp_MPZ::LDS(CKKnode_lds*Parent, int initDisc) {
    for (int i = initDisc; i <= Parent->nodeList.getSize(); i++) {
        cout << "Discrepância: " << i << endl;
        subLDS(Parent, Parent->nodeList.getSize(), i);
    }
}

inline void CompleteKarmarkarKarp_MPZ::subLDS(CKKnode_lds * Parent, int depth, int k) {
    nodesInspected[0]++;
    nls = Parent->nodeList.getSize();
    double a;
    if ((a = c.elapsed()) > 5) {
        NodesPersecond += a;
        cout << "Minutes: " << NodesPersecond / 60 << endl;
        mpz_class res((char*) min, 10);
        res+=1;
        cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2_temp(res) << " -- " << getpid() << " -- " << nls << " -- " << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
        NIActual = nodesInspected[0];
        c.end();
        c.start();
    }
    if (nls == 1) {
        mpz_class temp = Parent->getId(); //Parent->nodeList->List->peekFirst()->List->peekFirst()->id - Parent->nodeList->List->peekFirst()->List->peekLast()->id;
        sem->getLock();
        mpz_t m1;
        mpz_init(m1);
        mpz_set_str(m1, (char*) min, 10);
        mpz_class m(m1);
        if (temp < m) {
            mpz_class res(temp+1);
            cout << log2_temp(res) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            //p->cloneSolutionToBest(Parent->nodeList->peekFirst());
        }
        sem->ReleaseLock();
        return;
    } else {
        if (depth > k) {
            number_element_mpz* A = Parent->nodeList.removeFirst();
            number_element_mpz* B = Parent->nodeList.removeFirst();
            number_element_mpz * diff = &(*A - *B);
            Parent->nodeList.addElementToList(diff);
            if (prune(Parent)) {
                Parent->nodeList.removeElement(diff);
                nodesPruned[0]++;
            } else {
                subLDS(Parent, depth - 1, k);
                Parent->nodeList.removeElement(diff);
            }
            Parent->nodeList.addElementToList(B);
            Parent->nodeList.addElementToList(A);
            delete diff;
        }
        if (k > 0) {
            number_element_mpz* A = Parent->nodeList.removeFirst();
            number_element_mpz* B = Parent->nodeList.removeFirst();
            number_element_mpz* add = &(*A + *B);
            Parent->nodeList.addElementToList(add);
            if (prune(Parent)) {
                Parent->nodeList.removeElement(add);
                nodesPruned[0]++;
            } else {
                subLDS(Parent, depth - 1, k - 1);
                Parent->nodeList.removeElement(add);
            }
            Parent->nodeList.addElementToList(B);
            Parent->nodeList.addElementToList(A);
            delete add;
        }
    }
}

inline void CompleteKarmarkarKarp_MPZ::LDS(CKKnode_mpz*Parent, int initDisc) {
    for (int i = initDisc; i <= Parent->nodeList->List->getSize(); i++) {
        cout << "Discrepância: " << i << endl;
        subLDS(Parent, Parent->nodeList->List->getSize(), i);

    }
}

inline void CompleteKarmarkarKarp_MPZ::subLDS(CKKnode_mpz * Parent, int depth, int k) {
    int nls = Parent->nodeList->List->getSize();
    nodesInspected[0]++;
    double a;
    if ((a = c.elapsed()) > 5) {
        NodesPersecond += a;
        mpz_class res((char*) min, 10);
        res+=1;
        cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2_temp(res) << " -- " << getpid() << " -- " << nls << " -- " << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
        NIActual = nodesInspected[0];
        c.end();
        c.start();
    }
    if (nls == 1) {
        mpz_class temp = Parent->nodeList->List->peekFirst()->List->peekFirst()->id - Parent->nodeList->List->peekFirst()->List->peekLast()->id;
        sem->getLock();
        mpz_t m1;
        mpz_init(m1);
        mpz_set_str(m1, (char*) min, 10);
        mpz_class m(m1);
        if (temp < m) {
            mpz_class res(temp+1);
            cout << log2_temp(res) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            p->cloneSolutionToBest(Parent->nodeList->List->peekFirst());
        }
        sem->ReleaseLock();
        return;
    } else {
        if (depth > k) {
            ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = NULL;
            ListOfSums_mpz* A = Parent->nodeList->removeFirst();
            ListOfSums_mpz* B = Parent->nodeList->removeFirst();
            //cout<<A->id<<endl;
            //cout<<B->id<<endl;
            childrenCandidates = mergeListOfSums(A, B, 0);
            node_list_struct<ListOfSums_mpz*>* los;

            while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
                Parent->nodeList->addElementToList(los->element);
                if (prune(Parent)) {
                    Parent->nodeList->removeElement(los->element);
                    nodesPruned[0]++;
                } else {
                    subLDS(Parent, depth - 1, k);
                    Parent->nodeList->removeElement(los->element);
                }
            }
            Parent->nodeList->addElementToList(B);
            Parent->nodeList->addElementToList(A);
            delete childrenCandidates;
        }
        if (k > 0) {
            ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = NULL;
            ListOfSums_mpz* A = Parent->nodeList->removeFirst();
            ListOfSums_mpz* B = Parent->nodeList->removeFirst();
            childrenCandidates = mergeListOfSums(A, B, 1);
            node_list_struct<ListOfSums_mpz*>* los;
            while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
                Parent->nodeList->addElementToList(los->element);
                if (prune(Parent)) {
                    Parent->nodeList->removeElement(los->element);
                    nodesPruned[0]++;
                } else {
                    subLDS(Parent, depth - 1, k - 1);
                    Parent->nodeList->removeElement(los->element);
                }
            }
            Parent->nodeList->addElementToList(B);
            Parent->nodeList->addElementToList(A);
            delete childrenCandidates;
        }
    }
}

inline bool CompleteKarmarkarKarp_MPZ::prune1(CKKnode_mpz * node) {
    BookKeeping_mpz * major = node->nodeList->List->peekFirst()->List->peekFirst();
    mpz_class diff = major->id - (node->nodeList->getId() - major->id) / (nroParticoes - 1);
    mpz_class m((char*) min, 10);
    //cout<<diff<<"--"<<sum<<endl;
    if (diff > m) {
        return true;
    } else if (diff >= 0) {
        strcpy((char*) min, diff.get_str(10).c_str());
        return true;
    }
    return false;
}

inline bool CompleteKarmarkarKarp_MPZ::prune1(CKKnode_bfs_mpz * node) {
    mpz_class major = node->nodeList.List[1]->id;
    mpz_class diff = major - (node->nodeList.getId() - major) / (nroParticoes - 1);
    mpz_class m((char*) min, 10);
    //cout<<diff<<"--"<<sum<<endl;
    if (diff > m) {
        return true;
    } else if (diff >= 0) {
        strcpy((char*) min, diff.get_str(10).c_str());
        return true;
    }
    return false;
}

inline bool CompleteKarmarkarKarp_MPZ::prune1(CKKnode_bfs * node) {
    bkp_bfs * major = node->nodeList->peekFirst()->List->peekFirst();
    mpz_class diff = major->id - (node->nodeList->getId() - major->id) / (nroParticoes - 1);
    mpz_class m((char*) min, 10);
    //cout<<diff<<"--"<<sum<<endl;
    if (diff > m) {
        return true;
    } else if (diff >= 0) {
        strcpy((char*) min, diff.get_str(10).c_str());
        return true;
    }
    return false;
}

inline void CompleteKarmarkarKarp_MPZ::breadthFirst(CKKnode_bfs * Parent, int alpha) {
    //Parent->nodeList->print();
    //KK(Parent, 0, Parent->nodeList->nElem);
    KK(createVector(Parent->nodeList));
    //ToBeSearched *d=new ToBeSearched(Parent,0);
    bfslist->Add(Parent);
    ListStructurePtr<los_bfs*>* childrenCandidates = NULL;
    while (bfslist->getSize() > 0) {
        nls = bfslist->peekLast()->nodeList->getSize();
        // CKKnode_mpz * temp;
        while (bfslist->getSize() > 0) {
            nodesInspected[0]++;
            double a;
            if ((a = c.elapsed()) > 5) {
                NodesPersecond += a;
                mpz_class res((char*) min, 10);res+=1;
                cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2_temp(res) << " -- " << getpid() << " -- " << nls << " -- " << bfslist->getSize() << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
                NIActual = nodesInspected[0];
                c.end();
                c.start();
            }
            //temp = bfslist->RemoveFront();
            CKKnode_bfs * nodeInAction = bfslist->RemoveFront();
            int j = 0;
            //CKKnode_bfs * novonodo = new CKKnode_bfs(nodeInAction->nodeList->getSize() + 1);
            los_bfs* A = nodeInAction->nodeList->removeFirst();
            los_bfs* B = nodeInAction->nodeList->removeFirst();
            childrenCandidates = mergeListOfSums(A, B);
            if (A->ref == 0) {
                bkp_bfs*bkp1;
                while ((bkp1 = A->List->RemoveFront()) != NULL) {
                    bkp_bfs::downRef(bkp1);
                }
                delete A;
            }
            if (B->ref == 0) {
                bkp_bfs*bkp1;
                while ((bkp1 = B->List->RemoveFront()) != NULL) {
                    bkp_bfs::downRef(bkp1);
                }
                delete B;
            }
            los_bfs* los;
            int i = 0;
            while ((los = childrenCandidates->RemoveFront()) != NULL) {
                if (i % 2 == 0) {
                    CKKnode_bfs * novonodo = new CKKnode_bfs(nodeInAction->nodeList->getSize() + 1);
                    novonodo->nodeList->addListToListWOSort(nodeInAction->nodeList->List, nodeInAction->nodeList->First, nodeInAction->nodeList->nElem);
                    novonodo->nodeList->addElementToList(los);
                    if (prune1(novonodo)) {
                        novonodo->nodeList->cleanList();
                        // delete novonodo;
                        nodesPruned[0]++;
                    } else {
                        novonodo->left = nodeInAction->left + 1;
                        novonodo->right = nodeInAction->right;
                        hashSearch->put(novonodo->right, novonodo);
                        //novonodo->nodeList=NULL;
                    }
                } else {
                    //CKKnode_bfs * novonodo = new CKKnode_bfs(nodeInAction->nodeList->getSize() + 1);
                    //novonodo->nodeList->addListToListWOSort(nodeInAction->nodeList->List, nodeInAction->nodeList->First, nodeInAction->nodeList->nElem);
                    nodeInAction->nodeList->addElementToList(los);
                    //nodeInAction->nodeList->addElementToList(los->element);
                    //novonodo->nodeList->addListToListWOSort(nodeInAction->nodeList->List, nodeInAction->nodeList->First, nodeInAction->nodeList->nElem);
                    //novonodo->nodeList->print();
                    if (prune1(nodeInAction)) {
                        nodeInAction->nodeList->cleanList();
                        delete nodeInAction;
                        nodesPruned[0]++;
                    } else {
                        nodeInAction->left = nodeInAction->left;
                        nodeInAction->right = nodeInAction->right + 1;
                        hashSearch->put(nodeInAction->right, nodeInAction);
                        //nodeInAction->nodeList=NULL;
                        KK(createVector(nodeInAction->nodeList));
                    }
                }
                i++;
            }
            delete childrenCandidates;
            //delete nodeInAction;
        }
        CKKnode_bfs * sub;
        bool flag = false;
        for (int i = 0; i < p->getNumberSource()->getSize(); i++) {
            while ((sub = hashSearch->getFirst(i)) != NULL) {
                bfslist->append(sub);
                //sub-nodeList=NULL;
                if (bfslist->getSize() == alpha) {
                    flag = true;
                    hashSearch->setKeyMin(i);
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        hashSearch->cleanTable();
    }
}

inline void CompleteKarmarkarKarp_MPZ::breadthFirst(CKKnode_mpz * Parent, int alpha) {
    KK(Parent, 0);
    //ToBeSearched * d= new ToBeSearched(Parent,0);
    bfslist_mpz->Add(Parent);
    ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = NULL;
    while (bfslist_mpz->getSize() > 0) {
        nls = bfslist_mpz->peekLast()->nodeList->List->getSize();
        while (bfslist_mpz->getSize() > 0) {
            nodesInspected[0]++;
            double a;
            if ((a = c.elapsed()) > 5) {
                NodesPersecond += a;
                mpz_class res((char*) min, 10);res+=1;
                cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2_temp(res) << " -- " << getpid() << " -- " << nls << " -- " << bfslist->getSize() << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << endl;
                c.end();
                c.start();
            }
            //  temp = bfslist->RemoveFront();
            CKKnode_mpz * nodeInAction = bfslist_mpz->RemoveFront();
            int j = 0;
            ListOfSums_mpz* A = nodeInAction->nodeList->removeFirst();
            ListOfSums_mpz* B = nodeInAction->nodeList->removeFirst();
            childrenCandidates = mergeListOfSums(A, B);
            //cout<<novonodo->nodeList->List->getSize()<<endl;
            if (A->ref == 0) {
                BookKeeping_mpz*bkp1;
                while ((bkp1 = A->List->RemoveFront()) != NULL) {
                    BookKeeping_mpz::downRef(bkp1);
                }
                delete A;
            }
            if (B->ref == 0) {
                BookKeeping_mpz*bkp1;
                while ((bkp1 = B->List->RemoveFront()) != NULL) {
                    BookKeeping_mpz::downRef(bkp1);
                }
                delete B;
            }
            //delete A;
            //delete B;
            node_list_struct<ListOfSums_mpz*>* los;
            int i = 0;
            while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
                if (i % 2 == 0) {
                    CKKnode_mpz * novonodo = new CKKnode_mpz;
                    novonodo->nodeList->addElementToList(los->element);
                    novonodo->nodeList->addListToList(nodeInAction->nodeList->List);
                    if (prune1(novonodo)) {
                        novonodo->nodeList->cleanList();
                        delete novonodo;
                        nodesPruned[0]++;
                    } else {
                        novonodo->left = nodeInAction->left + 1;
                        novonodo->right = nodeInAction->right;
                        //ToBeSearched * a= new ToBeSearched(novonodo,novonodo->right);
                        hashSearch_mpz->put(novonodo->right, novonodo);

                    }
                } else {
                    CKKnode_mpz * novonodo = new CKKnode_mpz();
                    novonodo->nodeList->addElementToList(los->element);
                    novonodo->nodeList->addListToList(nodeInAction->nodeList->List);
                    if (prune1(novonodo)) {
                        novonodo->nodeList->cleanList();
                        delete novonodo;
                        nodesPruned[0]++;
                    } else {
                        novonodo->left = nodeInAction->left;
                        novonodo->right = nodeInAction->right + 1;
                        //ToBeSearched * a=new ToBeSearched(novonodo,novonodo->right);
                        hashSearch_mpz->put(novonodo->right, novonodo);
                        KK(novonodo, 0);
                    }
                }
                i++;
            }
            childrenCandidates->ClearList();
            delete childrenCandidates;
            nodeInAction->clean();
            delete nodeInAction;
            //temp.clean();
        }
        CKKnode_mpz * sub;
        bool flag = false;
        for (int i = 0; i < p->getNumberSource()->getSize(); i++) {
            while ((sub = hashSearch_mpz->getFirst(i)) != NULL) {
                bfslist_mpz->append(sub);
                if (bfslist_mpz->getSize() == alpha) {
                    flag = true;
                    hashSearch->setKeyMin(i);
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        hashSearch_mpz->cleanTable();
    }
}

inline void CompleteKarmarkarKarp_MPZ::KK(CKKnode_mpz * node, int d) {
    int nls = node->nodeList->List->getSize();
    ListOfSums_mpz * nova = NULL;
    if (nls == 1) {
        mpz_class temp = node->nodeList->List->peekFirst()->List->peekFirst()->id - node->nodeList->List->peekFirst()->List->peekLast()->id;
        mpz_class m((char*) min, 10);
        if (temp < m) {
            mpz_class res(temp+1);
            cout << log2_temp(res) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            // node->nodeList->List->peekFirst()->element->List->peekFirst()->element->print();
            //node->nodeList->List->peekFirst()->element->List->peekLast()->element->print();
            p->cloneSolutionToBest(node->nodeList->List->peekFirst());
        }
        return;
    }
    ListOfSums_mpz* A = node->nodeList->removeFirst();
    ListOfSums_mpz* B = node->nodeList->removeFirst();
    //cout << A->id << endl;
    //cout << B->id << endl;
    nova = new ListOfSums_mpz();
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    if (nonZeroA > nonZeroB) {
        int j, i;
        for (i = 0, j = nonZeroA; i < nonZeroB; i++, j--) {
            BookKeeping_mpz*nodeB = B->List->retrieve_K_esimo(i);
            BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(j);
            BookKeeping_mpz*bkpA;
            BookKeeping_mpz*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            nova->addElementToList(mergeBookKepings(A->List->retrieve_K_esimo(j), A->List->retrieve_K_esimo(i)));
        }
        normalize(nova);
    } else {
        int j, i;
        for (i = 0, j = nonZeroB; i < nonZeroA; i++, j--) {
            BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(j);
            BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(i);
            BookKeeping_mpz*bkpA;
            BookKeeping_mpz*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            BookKeeping_mpz* nodeB = B->List->retrieve_K_esimo(j);
            BookKeeping_mpz*nodeA = A->List->retrieve_K_esimo(i);
            BookKeeping_mpz*bkpA;
            BookKeeping_mpz*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpB, bkpA));
        }
        normalize(nova);
    }
    node->nodeList->addElementToList(nova);
    //novonodo->nodeList->List->Add(node->nodeList->List);
    KK(node, d + 1);
    if (d != 0) {
        node->nodeList->removeElement(nova);
        node->nodeList->addElementToList(A);
        node->nodeList->addElementToList(B);
        // delete A;
        // delete B;
        delete nova;
    } else {
        node->nodeList->removeElement(nova);
        node->nodeList->addElementToList(A);
        node->nodeList->addElementToList(B);
        // delete A;
        // delete B;
        delete nova;
    }
}

void CompleteKarmarkarKarp_MPZ::KK(node_lst_tree * node, int d) {
    int nls = node->List->getSize();
    los_bfs * nova = NULL;
    if (nls == 1) {
        mpz_class temp = node->List->peekFirst()->List->peekFirst()->id - node->List->peekFirst()->List->peekLast()->id;
        mpz_class m((char*) min, 10);
        if (temp < m) {
            mpz_class res(temp+1);
            cout << log2_temp(res) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            // node->nodeList->List->peekFirst()->element->List->peekFirst()->element->print();
            //node->nodeList->List->peekFirst()->element->List->peekLast()->element->print();
            //p->cloneSolutionToBest(node->nodeList->List->peekFirst());
            node->List->RemoveMax();
        }
        return;
    }
    los_bfs* A = node->removeFirst();
    los_bfs* B = node->removeFirst();
    //cout << A->id << endl;
    //cout << B->id << endl;
    nova = new los_bfs();
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    if (nonZeroA > nonZeroB) {
        int j, i;
        for (i = 0, j = nonZeroA; i < nonZeroB; i++, j--) {
            bkp_bfs*nodeB = B->List->retrieve_K_esimo(i);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(j);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            nova->addElementToList(mergeBookKepings(A->List->retrieve_K_esimo(j), B->List->retrieve_K_esimo(i)));
        }
        normalize(nova);
    } else {
        int j, i;
        for (i = 0, j = nonZeroB; i < nonZeroA; i++, j--) {
            bkp_bfs* nodeB = B->List->retrieve_K_esimo(j);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(i);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            bkp_bfs* nodeB = B->List->retrieve_K_esimo(j);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(i);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpB, bkpA));
        }
        normalize(nova);
    }
    //cout<<nova->getId()<<endl;
    node->addElementToList(nova);
    //novonodo->nodeList->List->Add(node->nodeList->List);
    KK(node, d + 1);
    if (d != 0) {
        delete nova;
    } else {
        delete nova;
        delete node;
    }
}

void CompleteKarmarkarKarp_MPZ::breadthFirst(CKKnode_bfs_mpz * Parent, int alpha) {
    KK(Parent);
    //ToBeSearched *d=new ToBeSearched(Parent,0);
    bfslist1->Add(Parent);
    //ListStructurePtr<los_bfs*>* childrenCandidates = NULL;
    while (bfslist1->getSize() > 0) {
        nls = bfslist1->peekLast()->nodeList.getSize();
        // CKKnode_mpz * temp;
        while (bfslist1->getSize() > 0) {
            nodesInspected[0]++;
            double a;
            if ((a = c.elapsed()) > 5) {
                NodesPersecond += a;
                cout << "Minutes: " << NodesPersecond / 60 << endl;
                mpz_class res((char*) min, 10);res+=1;
                cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2_temp(res) << " -- " << getpid() << " -- " << nls << " -- " << bfslist1->getSize() << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
                NIActual = nodesInspected[0];
                c.end();
                c.start();
            }
            //temp = bfslist->RemoveFront();
            CKKnode_bfs_mpz * nodeInAction = bfslist1->RemoveFront();
            int j = 0;
            //CKKnode_bfs * novonodo = new CKKnode_bfs(nodeInAction->nodeList->getSize() + 1);
            number_element_mpz * A = nodeInAction->nodeList.removeFirst();
            number_element_mpz * B = nodeInAction->nodeList.removeFirst();
            //childrenCandidates = mergeListOfSums(A, B);
            A->ref--;
            B->ref--;
            //los_bfs* los;
            CKKnode_bfs_mpz * novonodo = new CKKnode_bfs_mpz(nodeInAction->nodeList.getSize() + 1);
            novonodo->nodeList.addListToListWOSort(nodeInAction->nodeList.List, nodeInAction->nodeList.First, nodeInAction->nodeList.nElem);
            novonodo->nodeList.addElementToList(&(*A - *B));
            if (prune1(novonodo)) {
                delete novonodo;
                // delete novonodo;
                nodesPruned[0]++;
            } else {
                novonodo->left = nodeInAction->left + 1;
                novonodo->right = nodeInAction->right;
                hashSearch1->put(novonodo->right, novonodo);
                //novonodo->nodeList=NULL;
            }
            //CKKnode_bfs * novonodo = new CKKnode_bfs(nodeInAction->nodeList->getSize() + 1);
            //novonodo->nodeList->addListToListWOSort(nodeInAction->nodeList->List, nodeInAction->nodeList->First, nodeInAction->nodeList->nElem);
            //CKKnode_bfs_mpz * novonodo1 = new CKKnode_bfs_mpz(nodeInAction->nodeList.getSize() + 1);
            //novonodo1->nodeList.addListToListWOSort(nodeInAction->nodeList.List, nodeInAction->nodeList.First, nodeInAction->nodeList.nElem);
            nodeInAction->nodeList.addElementToList(&(*A + *B));
            if (prune1(nodeInAction)) {
                delete nodeInAction;
                // delete novonodo;
                nodesPruned[0]++;
            } else {
                nodeInAction->left = nodeInAction->left;
                nodeInAction->right = nodeInAction->right + 1;
                KK(nodeInAction);
                hashSearch1->put(nodeInAction->right, nodeInAction);
                //novonodo->nodeList=NULL;
            }
            if (A->ref == 0) {
                delete A;
            }
            if (B->ref == 0) {
                delete B;
            }
            // delete nodeInAction;
        }
        CKKnode_bfs_mpz * sub;
        bool flag = false;
        for (int i = 0; i < p->getNumberSource()->getSize(); i++) {
            while ((sub = hashSearch1->getFirst(i)) != NULL) {
                bfslist1->append(sub);
                //sub-nodeList=NULL;
                if (bfslist1->getSize() == alpha) {
                    flag = true;
                    hashSearch1->setKeyMin(i);
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        hashSearch1->cleanTable();
    }
}

//node_lst_vector * CompleteKarmarkarKarp_MPZ::createVector(node_lst_bfs_mpz * A) {
//    node_lst_vector * ret = new node_lst_vector(A->nElem);
//    for (int i = 1; i <= A->nElem; i++) {
//        ret->List[i] = A->List[i];
//        ret->id += A->List[i];
//
//    }
//    ret->nElem = A->nElem;
//    return ret;
//}

inline void CompleteKarmarkarKarp_MPZ::KK(CKKnode_bfs_mpz * node) {
    node_lst_bfs_mpz v(node->nodeList.nElem);
    for (int i = 1; i <= node->nodeList.nElem; i++)
        v.List[i] = node->nodeList.List[i];
    v.id = node->nodeList.id;
    v.nElem = node->nodeList.nElem;
    int i = 1;
    //memcpy(&v, &node, sizeof(node_lst_bfs_mpz));
    //memcpy(&v,node,sizeof(node_lst_bfs_mpz));
    while (v.nElem > 1) {
        number_element_mpz * A = v.removeMax();
        number_element_mpz * B = v.removeMax();
        //cout<<A<<endl;
        // cout<<B<<endl;
        number_element_mpz * temp = &(*A - *B);
        temp->fromMerge = 1;
        v.addElementToList(temp);
        if (A->fromMerge) {
            delete A;
        }
        if (B->fromMerge) {
            delete B;
        }
    }

    mpz_class m((char*) min, 10);
    if (v.id < m) {
        mpz_class res(v.id+1);
        cout << log2_temp(res) << " -- " << getpid() << "Discrepância: " << (int) node->right << endl;
        strcpy((char*) min, v.id.get_str(10).c_str());
        //p->cloneSolutionToBest(v->List[1]);
    }
}

inline void CompleteKarmarkarKarp_MPZ::KK(node_lst_vector * v) {
    //los_bfs * lista = new los_bfs[v->nElem];
    //ListStructurePtr<los_bfs*> * l = new ListStructurePtr<los_bfs*>(ListStructurePtr<los_bfs*>::ORDEM_CRESCENTE);
    while (v->nElem > 1) {
        mpz_class A = v->removeMax();
        mpz_class B = v->removeMax();
        v->addElementToList(A - B);
    }
    mpz_class m((char*) min, 10);
    if (v->id < m) {
        cout << log2_temp(v->id + 1) << " -- " << getpid() << endl;
        strcpy((char*) min, v->id.get_str(10).c_str());
        //p->cloneSolutionToBest(v->List[1]);
    }
    //delete v;
}

inline node_lst_vector * CompleteKarmarkarKarp_MPZ::createVector(node_lst_bfs * A) {
    node_lst_vector * ret = new node_lst_vector(A->nElem);
    for (int i = 1; i <= A->nElem; i++) {
        ret->List[i] = A->List[i]->id;
        ret->id += A->List[i]->id;

    }
    ret->nElem = A->nElem;
    return ret;
}

inline void CompleteKarmarkarKarp_MPZ::KK(CKKnode_bfs * node, int d, int n) {
    int nls = node->nodeList->getSize();
    los_bfs * nova = NULL;
    if (nls == 1) {
        mpz_class temp = node->nodeList->peekFirst()->List->peekFirst()->id - node->nodeList->peekFirst()->List->peekLast()->id;
        mpz_class m((char*) min, 10);
        if (temp < m) {
            cout << log2_temp(temp + 1) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            // node->nodeList->List->peekFirst()->element->List->peekFirst()->element->print();
            //node->nodeList->List->peekFirst()->element->List->peekLast()->element->print();
            //p->cloneSolutionToBest(node->nodeList->List->peekFirst());
        }
        node->nodeList->nElem = node->nodeList->size - n;
        return;
    }
    los_bfs* A = node->nodeList->removeFirst();
    los_bfs* B = node->nodeList->removeFirst();
    nova = new los_bfs();
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    if (nonZeroA > nonZeroB) {
        int j, i;
        for (i = 0, j = nonZeroA; i < nonZeroB; i++, j--) {
            bkp_bfs*nodeB = B->List->retrieve_K_esimo(i);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(j);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            nova->addElementToList(mergeBookKepings(A->List->retrieve_K_esimo(j), B->List->retrieve_K_esimo(i)));
        }
        normalize(nova);
    } else {
        int j, i;
        for (i = 0, j = nonZeroB; i < nonZeroA; i++, j--) {
            bkp_bfs* nodeB = B->List->retrieve_K_esimo(j);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(i);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpA, bkpB));
        }
        for (; j >= 0; j--) {
            bkp_bfs* nodeB = B->List->retrieve_K_esimo(j);
            bkp_bfs*nodeA = A->List->retrieve_K_esimo(i);
            bkp_bfs*bkpA;
            bkp_bfs*bkpB;
            if (nodeA != NULL) {
                bkpA = nodeA;
            } else {
                bkpA = NULL;
            }
            if (nodeB != NULL) {
                bkpB = nodeB;
            } else {
                bkpB = NULL;
            }
            nova->addElementToList(mergeBookKepings(bkpB, bkpA));
        }
        normalize(nova);
    }
    nova->FromMerge = 1;
    //cout<<nova->getId()<<endl;
    //cout<<nova->getId()<<endl;
    node->nodeList->addElementToList(nova);
    //novonodo->nodeList->List->Add(node->nodeList->List);
    // cout << node->nodeList->Check() << endl;
    KK(node, d + 1, n);
    if (d != 0) {
        node->nodeList->removeElement(nova);
        if (!B->FromMerge) {
            //cout<<B->id<<endl;
            node->nodeList->addElementToList1(B);
        } else {
            node->nodeList->id += B->getId();
        }
        if (!A->FromMerge) {
            //cout<<A->id<<endl;
            node->nodeList->addElementToList1(A);
        } else {
            node->nodeList->id += A->getId();
        }

        //cout << node->nodeList->Check() << endl;
        // delete A;
        // delete B;
        delete nova;
    } else {
        node->nodeList->removeElement(nova);
        node->nodeList->addElementToList1(B);
        node->nodeList->addElementToList1(A);
        node->nodeList->nElem = n;
        //node->nodeList->sort();
        // delete A;
        // delete B;
        //        for(int i=0;i<node->nodeList->getSize();i++){
        //            cout<<i<<" : "<<node->nodeList->List[i]->getId()<<endl;
        //            cout<<i<<" : "<<node->nodeList->List[i]->getId()<<endl;
        //        }
        //node->nodeList->print();
        delete nova;
    }
}

inline void CompleteKarmarkarKarp_MPZ::depthFirst(CKKnode_dfs *Parent) {
    int nls = Parent->nodeList.List->getSize();
    nodesInspected[0]++;
    double a;
    if ((a = c.elapsed()) > 5) {
        NodesPersecond += a;
        cout << "Minutes: " << NodesPersecond / 60 << endl;
        cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2(mpz_class((char*) min, 10) + 1) << " -- " << getpid() << " -- " << nls << " -- " << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
        NIActual = nodesInspected[0];
        c.end();
        c.start();
    }
    if (nls == 1) {
        mpz_class temp = Parent->nodeList.getId();
        mpz_class m((char*) min, 10);
        if (temp < m) {
            cout << log2_temp(temp + 1) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            //p->cloneSolutionToBest(Parent->nodeList->List->peekFirst());
        }
        return;
    } else {
        number_element_mpz* A = Parent->nodeList.removeFirst();
        number_element_mpz* B = Parent->nodeList.removeFirst();
        number_element_mpz * diff = &(*A - *B);
        Parent->nodeList.addElementToList(diff);
        if (prune(Parent)) {
            Parent->nodeList.removeElement(diff);
            nodesPruned[0]++;

        } else {
            depthFirst(Parent);
            Parent->nodeList.removeElement(diff);
        }
        delete diff;
        number_element_mpz * add = &(*A + *B);
        Parent->nodeList.addElementToList(add);
        if (prune(Parent)) {
            Parent->nodeList.removeElement(add);
            nodesPruned[0]++;
        } else {
            depthFirst(Parent);
            Parent->nodeList.removeElement(add);
        }
        delete add;
        Parent->nodeList.addElementToList(A);
        Parent->nodeList.addElementToList(B);
    }
}

inline void CompleteKarmarkarKarp_MPZ::depthFirst(CKKnode_mpz * Parent) {
    int nls = Parent->nodeList->List->getSize();
    nodesInspected[0]++;
    double a;
    if ((a = c.elapsed()) > 5) {
        NodesPersecond += a;
        cout << nodesInspected[0] << " -- " << nodesPruned[0] << " -- " << (double) nodesPruned[0] / (nodesInspected[0]) << " -- " << log2(mpz_class((char*) min, 10) + 1) << " -- " << getpid() << " -- " << nls << " -- " << " Nodes p/ sec.: " << nodesInspected[0] / NodesPersecond << ":" << (nodesInspected[0] - NIActual) / a << endl;
        NIActual = nodesInspected[0];
        c.end();
        c.start();
    }
    if (nls == 1) {
        mpz_class temp = Parent->nodeList->List->peekFirst()->List->peekFirst()->id - Parent->nodeList->List->peekFirst()->List->peekLast()->id;
        mpz_class m((char*) min, 10);
        if (temp < m) {
            cout << log2_temp(temp + 1) << " -- " << getpid() << endl;
            strcpy((char*) min, temp.get_str(10).c_str());
            p->cloneSolutionToBest(Parent->nodeList->List->peekFirst());
        }
        return;
    } else {
        ListOfSums_mpz* A = Parent->nodeList->removeFirst();
        ListOfSums_mpz* B = Parent->nodeList->removeFirst();
        ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = mergeListOfSums1(A, B);
        node_list_struct<ListOfSums_mpz*>* los;
        while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
            //CKKnode_mpz * nodetemp = new CKKnode_mpz();
            //cout << log2(los->element->id+1) << endl;
            Parent->nodeList->addElementToList(los->element);
            //nodetemp->nodeList->addListToList(Parent->nodeList->List);
            if (prune(Parent)) {
                //nodetemp->nodeList->List->ClearList();
                //delete nodetemp;
                Parent->nodeList->removeElement(los->element);
                nodesPruned[0]++;
            } else {
                //Parent->children->Add(nodetemp);
                depthFirst(Parent);
                Parent->nodeList->removeElement(los->element);
            }
        }
        delete childrenCandidates;
        Parent->nodeList->addElementToList(A);
        Parent->nodeList->addElementToList(B);
        //Parent->nodeList->List->ClearList();
        //delete Parent;
    }
}

void CompleteKarmarkarKarp_MPZ::runDFS1() {
    number_element_mpz* A = raizDFS->nodeList.removeFirst();
    number_element_mpz* B = raizDFS->nodeList.removeFirst();
    CKKnode_dfs ** temp = new CKKnode_dfs*[2];
    temp[0] = new CKKnode_dfs();
    temp[0]->nodeList.addElementToList(&(*A + *B));
    temp[0]->nodeList.addListToList(raizDFS->nodeList.List);
    temp[1] = new CKKnode_dfs();
    temp[1]->nodeList.addElementToList(&(*A - *B));
    temp[1]->nodeList.addListToList(raizDFS->nodeList.List);
    nodesInspected[0]++;
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    // cout << a << endl;
    a.get_str(10);
    strcpy((char*) min, a.get_str(10).c_str());
    //cout << (char*) min << endl;
    c.start();
    cout << getpid() << endl;
    int pid = fork();
    if (pid == 0) {
        cout << "1:" << getpid() << endl;
        depthFirst(temp[0]);
    } else {
        cout << "2:" << getpid() << endl;
        depthFirst(temp[1]);
    }
}

void CompleteKarmarkarKarp_MPZ::runLDS1(int InitDisc1, int InitDisc2) {
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    CKKnode_lds ** temp = new CKKnode_lds*[2];
    number_element_mpz* A = raizLDS->nodeList.removeFirst();
    number_element_mpz* B = raizLDS->nodeList.removeFirst();
    temp[0] = new CKKnode_lds();
    temp[0]->nodeList.addElementToList(&(*A - *B));
    temp[0]->nodeList.addListToList(raizLDS->nodeList.List);
    temp[1] = new CKKnode_lds();
    temp[1]->nodeList.addElementToList(&(*A + *B));
    temp[1]->nodeList.addListToList(raizLDS->nodeList.List);
    nodesInspected[0]++;
    a.get_str(10);
    strcpy((char*) min, a.get_str(10).c_str());
    //cout << (char*) min << endl;
    c.start();
    cout << getpid() << endl;
    int pid = fork();
    if (pid == 0) {
        cout << "1:" << getpid() << endl;
        LDS(temp[0], InitDisc1);
    } else {
        cout << "2:" << getpid() << endl;
        LDS(temp[1], InitDisc2);
    }
    //raiz->cleanChildren();
}

void CompleteKarmarkarKarp_MPZ::runLDS() {
    c.start();

    ListOfSums_mpz* A = raiz->nodeList->removeFirst();
    ListOfSums_mpz* B = raiz->nodeList->removeFirst();
    ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = mergeListOfSums(A, B);
    //delete A->element;
    //delete B->element;
    // delete A;
    // delete B;
    node_list_struct<ListOfSums_mpz*>* los;
    CKKnode_mpz ** temp = new CKKnode_mpz*[2];
    int i = 0;
    while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
        CKKnode_mpz * nodetemp = new CKKnode_mpz();
        //los->element->List->PrintLista();
        nodetemp->nodeList->addElementToList(los->element);
        nodetemp->nodeList->addListToList(cloneListOfListOfSums(raiz->nodeList->List));
        //nodetemp->nodeList->List->PrintLista();
        //cout<<"###"<<endl;
        temp[i] = nodetemp;
        i++;
        //        raiz->children->Add(nodetemp);
        //nodetemp->nodeList->List->PrintLista();
    }
    childrenCandidates->ClearList();
    delete childrenCandidates;
    //raiz->cleanNode();
    CKKnode_mpz * nodeit = temp[0];
    CKKnode_mpz * nodeit1 = temp[1];
    //pthread_t * threads = new pthread_t[2];
    //    int i = 0;

    nodesInspected[0]++;
    if (min == (char*) - 1) {
        perror("merda\n");
    }
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    // cout << a << endl;
    a.get_str(10);
    strcpy((char*) min, a.get_str(10).c_str());
    //cout << (char*) min << endl;
    cout << getpid() << endl;
    int pid = fork();
    if (pid == 0) {
        cout << "1:" << getpid() << endl;
        LDS(raiz, 0);
    } else {
        cout << "2:" << getpid() << endl;
        LDS(raiz, 4);
    }
}

void CompleteKarmarkarKarp_MPZ::runDFS() {
    c.start();

    ListOfSums_mpz* A = raiz->nodeList->removeFirst();
    ListOfSums_mpz* B = raiz->nodeList->removeFirst();
    ListStructurePtr<ListOfSums_mpz*>* childrenCandidates = mergeListOfSums(A, B);
    //delete A->element;
    //delete B->element;
    // delete A;
    // delete B;
    node_list_struct<ListOfSums_mpz*>* los;
    CKKnode_mpz ** temp = new CKKnode_mpz*[2];
    int i = 0;
    while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
        CKKnode_mpz * nodetemp = new CKKnode_mpz();
        //los->element->List->PrintLista();
        nodetemp->nodeList->addElementToList(los->element);
        nodetemp->nodeList->addListToList(cloneListOfListOfSums(raiz->nodeList->List));
        //nodetemp->nodeList->List->PrintLista();
        //cout<<"###"<<endl;
        temp[i] = nodetemp;
        i++;
        //        raiz->children->Add(nodetemp);
        //nodetemp->nodeList->List->PrintLista();
    }
    childrenCandidates->ClearList();
    delete childrenCandidates;
    //raiz->cleanNode();
    CKKnode_mpz * nodeit = temp[0];
    CKKnode_mpz * nodeit1 = temp[1];
    //pthread_t * threads = new pthread_t[2];
    //    int i = 0;

    nodesInspected[0]++;
    if (min == (char*) - 1) {
        perror("merda\n");
    }
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    // cout << a << endl;
    a.get_str(10);
    strcpy((char*) min, a.get_str(10).c_str());
    //cout << (char*) min << endl;
    cout << getpid() << endl;
    int pid = fork();
    if (pid == 0) {
        cout << "1:" << getpid() << endl;
        depthFirst(nodeit);
    } else {
        cout << "2:" << getpid() << endl;
        depthFirst(nodeit1);
    }
    // raiz->cleanChildren();
}

void CompleteKarmarkarKarp_MPZ::runBFS1(int alpha) {
    hashSearch1 = new Hash<int, CKKnode_bfs_mpz*>(p->getNumberSource()->getSize(), alpha);
    bfslist1 = new ListStructurePtr<CKKnode_bfs_mpz*>(ListStructurePtr<CKKnode_bfs_mpz*>::ORDEM_CRESCENTE);
    number_element_mpz* A = raizBFS_mpz->nodeList.removeFirst();
    number_element_mpz* B = raizBFS_mpz->nodeList.removeFirst();
    CKKnode_bfs_mpz ** temp = new CKKnode_bfs_mpz*[2];
    temp[0] = new CKKnode_bfs_mpz(raizBFS_mpz->nodeList.getSize() + 1);
    temp[0]->nodeList.addListToListWOSort(raizBFS_mpz->nodeList.List, 1, raizBFS_mpz->nodeList.nElem);
    temp[0]->nodeList.addElementToList(&(*A + *B));
    temp[0]->right = 1;
    temp[1] = new CKKnode_bfs_mpz(raizBFS_mpz->nodeList.getSize() + 1);
    temp[1]->nodeList.addListToListWOSort(raizBFS_mpz->nodeList.List, 1, raizBFS_mpz->nodeList.nElem);
    temp[1]->nodeList.addElementToList(&(*A - *B));
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    strcpy((char*) min, a.get_str(10).c_str());
    c.start();
    int pid = fork();
    if (pid == 0) {
        breadthFirst(temp[1], alpha);
    } else {
        breadthFirst(temp[0], alpha);
    }
}

void CompleteKarmarkarKarp_MPZ::runBFS(int alpha) {
    c.start();

    los_bfs* A = raizBFS->nodeList->removeFirst();
    los_bfs* B = raizBFS->nodeList->removeFirst();
    ListStructurePtr<los_bfs*>* childrenCandidates = mergeListOfSums(A, B);
    // delete A->element;
    // delete B->element;
    node_list_struct<los_bfs*>* los;
    //ListStructurePtr<CKKnode_mpz*>temp(ListStructurePtr<CKKnode_mpz*>::ORDEM_CRESCENTE);
    CKKnode_bfs ** temp = new CKKnode_bfs*[2];
    int i = 0;
    while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
        CKKnode_bfs * nodetemp = new CKKnode_bfs(raizBFS->nodeList->getSize() + 1);
        //los->element->List->PrintLista();
        nodetemp->nodeList->addElementToList(los->element);
        nodetemp->nodeList->addListToList(raizBFS->nodeList->List, raizBFS->nodeList->First, raizBFS->nodeList->nElem);
        //nodetemp->nodeList->List->PrintLista();
        //cout<<"###"<<endl;
        temp[i] = nodetemp;
        i++;
        //        raiz->children->Add(nodetemp);
        //nodetemp->nodeList->List->PrintLista();
    }
    childrenCandidates->ClearList();
    delete childrenCandidates;
    //raiz->cleanNode();
    CKKnode_bfs * nodeit = temp[0];
    CKKnode_bfs * nodeit1 = temp[1];
    //pthread_t * threads = new pthread_t[2];
    //   int i = 0;

    nodesInspected[0]++;
    if (min == (char*) - 1) {
        perror("merda\n");
    }
    mpz_class a = mpz_class();
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), p->getQuantidade() + 1);
    cout << a << endl;
    a.get_str(10);
    strcpy((char*) min, a.get_str(10).c_str());
    cout << (char*) min << endl;
    int pid = fork();
    if (pid == 0) {
        breadthFirst(nodeit, alpha);
    } else {
        breadthFirst(nodeit1, alpha);
    }
    // raiz->cleanChildren();
}

mpz_class CompleteKarmarkarKarp_MPZ::GetMin() const {

    return mpz_class((char*) min, 10);
}

inline ListOfSums_mpz * CompleteKarmarkarKarp_MPZ::cloneListOfSums(ListOfSums_mpz * los) {
    node_list_struct<BookKeeping_mpz*>*bkp;
    ListOfSums_mpz * l = new ListOfSums_mpz();
    while ((bkp = los->List->nextFromLastAcc()) != NULL) {
        BookKeeping_mpz * b = new BookKeeping_mpz(bkp->element->nElem);
        //delete b->List;
        for (int i = 0; i < bkp->element->nElem; i++) {
            b->List[i] = bkp->element->List[i];
        }
        //memcpy(&b->List[0],&bkp->element->List[0],bkp->element->nElem);
        b->nElem = bkp->element->nElem;
        b->id = bkp->element->id;
        //delete bkp->element->List;
        // bkp->element->List=NULL;
        // delete bkp->element;
        l->addElementToList(b);
    }
    // delete los;
    return l;
}

inline AvlTree<los_bfs*>* CompleteKarmarkarKarp_MPZ::cloneListOfListOfSums(AvlTree<los_bfs*>* list) {
    return list->clone();
}

inline AvlTree<ListOfSums_mpz*>* CompleteKarmarkarKarp_MPZ::cloneListOfListOfSums(AvlTree<ListOfSums_mpz*>* list) {
    return list->clone();
}

ListStructurePtr<ListOfSums_mpz*>* CompleteKarmarkarKarp_MPZ::cloneListOfListOfSums(ListStructurePtr<ListOfSums_mpz*>* list) {
    ListStructurePtr<ListOfSums_mpz*>* ret = new ListStructurePtr<ListOfSums_mpz*>(ListStructurePtr<ListOfSums_mpz*>::ORDEM_CRESCENTE);
    node_list_struct<ListOfSums_mpz*>* los;
    while ((los = list->nextFromLastAcc()) != NULL) {
        ret->Add(los->element->clone());
    }
    return ret;
}

inline bool CompleteKarmarkarKarp_MPZ::prune(CKKnode_lds * node) {
    number_element_mpz * major = node->nodeList.List->peekFirst();
    mpz_class diff = major->id - (node->nodeList.getId() - major->id) / (nroParticoes - 1);
    mpz_class m((char*) min, 10);
    //cout<<log2(diff+1)<<"--"<<log2(m+1)<<endl;
    if (diff > m) {
        return true;
    }
    return false;
}

inline bool CompleteKarmarkarKarp_MPZ::prune(CKKnode_dfs * node) {
    number_element_mpz * major = node->nodeList.List->peekFirst();
    //cout<<log2(node->nodeList->getId()+1)<<endl;
    mpz_class diff = major->id - (node->nodeList.getId() - major->id) / (nroParticoes - 1);
    //cout<<diff<<endl;
    mpz_class m((char*) min, 10);
    //cout << log2(diff + 1) << "--" << log2(m + 1) << endl;

    if (diff > m) {
        return true;
    }
    return false;
}

inline bool CompleteKarmarkarKarp_MPZ::prune(CKKnode_mpz * node) {
    BookKeeping_mpz * major = node->nodeList->List->peekFirst()->List->peekFirst();
    //cout<<log2(node->nodeList->getId()+1)<<endl;
    mpz_class diff = major->id - (node->nodeList->getId() - major->id) / (nroParticoes - 1);
    //cout<<diff<<endl;
    mpz_class m((char*) min, 10);
    // cout << log2(diff + 1) << "--" << log2(m + 1) << endl;

    if (diff > m) {
        return true;
    }
    return false;
}

inline los_bfs * CompleteKarmarkarKarp_MPZ::normalize(los_bfs * A) {
    if (numberOfNonZeroElements(A) == nroParticoes) {
        mpz_class normalizer = A->List->peekLast()->id;
        node_list_struct<bkp_bfs*> * bkp = A->List->nextFromLastAcc();
        while (bkp != NULL) {
            bkp->element->id -= normalizer;
            bkp = A->List->nextFromLastAcc();
        }
        A->id -= nroParticoes*normalizer;
        return A;
    }
    return A;
}

inline ListOfSums_mpz * CompleteKarmarkarKarp_MPZ::normalize(ListOfSums_mpz * A) {
    if (numberOfNonZeroElements(A) == nroParticoes) {
        mpz_class normalizer = A->List->peekLast()->id;
        node_list_struct<BookKeeping_mpz*> * bkp = A->List->nextFromLastAcc();
        while (bkp != NULL) {
            bkp->element->id -= normalizer;
            bkp = A->List->nextFromLastAcc();
        }
        A->id -= normalizer * A->List->getSize();

        return A;
    }
    return A;
}

inline int CompleteKarmarkarKarp_MPZ::numberOfNonZeroElements(ListOfSums_mpz * A) {
    int ret = 0;
    node_list_struct<BookKeeping_mpz*> * aux; // = A.List->nextFromLastAcc();
    while ((aux = A->List->nextFromLastAcc()) != NULL) {
        if (aux->element->id != 0) {

            ret++;
        }
    }
    return ret;
}

inline int CompleteKarmarkarKarp_MPZ::numberOfNonZeroElements(los_bfs * A) {
    int ret = 0;
    node_list_struct<bkp_bfs*> * aux; // = A.List->nextFromLastAcc();
    while ((aux = A->List->nextFromLastAcc()) != NULL) {
        if (aux->element->id != 0) {

            ret++;
        }
    }
    return ret;
}

CompleteKarmarkarKarp_MPZ::CompleteKarmarkarKarp_MPZ(NumberPartitionProblem_MPZ * npp, int nroParticoes) {
    this->p = npp;
    nls = 0;
    nodesInspected = 0;
    nodesPruned = 0;
    raiz = new CKKnode_mpz();
    raizBFS = new CKKnode_bfs(p->getNumberSource()->getSize());
    raizBFS_mpz = new CKKnode_bfs_mpz(p->getNumberSource()->getSize());
    raizLDS = new CKKnode_lds();
    raizDFS = new CKKnode_dfs();
    this->nroParticoes = nroParticoes;
    GenerateRaiz(npp->getNumberSource());
    GenerateRaizBFS(npp->getNumberSource());
    GenerateRaizBFS_mpz(p->getNumberSource());
    GenerateRaizLDS(npp->getNumberSource());
    GenerateRaizDFS(p->getNumberSource());
    //mpz_pow_ui(min->get_mpz_t(), mpz_class(2).get_mpz_t(), npp->getQuantidade() + 1);
    //cout<<min<<endl;

    //    for (int k = 0; k < 10; k++) {
    //        cout << raiz.nodeList.List->retrieve_K_esimo(k)->element.List->retrieve_K_esimo(0)->element.List->retrieve_K_esimo(0)->element.id << endl;
    //    }
    // raiz.nodeList.List->resetLastAcc();
    // ListOfSums_mpz A = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // ListOfSums_mpz B = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // mergeListOfSums_mpz(A, B);
    // createChildren(raiz);
    c.set_resolution(Cronometro::SEGUNDOS);
    // sb.sem_num = 0;
    // sb.sem_op = 1; /* set to allocate resource */
    // sb.sem_flg = 0;
    if ((key_s = ftok("CompleteKarmarkarKarp_MPZ.h", 'J')) == -1) {

        perror("ftok");
        exit(1);
    }
    // semid_s = semget(key_s, 1, 0666);
    // cout<<semid_s<<endl;
    key = ftok("CompleteKarmarkarKarp_MPZ.cpp", 'R');
    key = rand();
    //cout<<key<<endl;

    shmid = shmget(key, sizeof (char) *1000, IPC_CREAT | 0666);
    //cout<<shmid<<endl;
    min = shmat(shmid, (void *) 0, 0);
    mpz_class a;
    mpz_pow_ui(a.get_mpz_t(), mpz_class(2).get_mpz_t(), npp->getQuantidade() + 1);
    strcpy((char*) min, a.get_str(10).c_str());
    int key1 = rand();
    int shmida = shmget(key1, sizeof (long long), 0666 | IPC_CREAT);
    nodesPruned = (long long*) shmat(shmida, (void*) 0, 0);
    nodesPruned[0] = 0;
    int key2 = rand();
    int shmidb = shmget(key2, sizeof (long long), 0666 | IPC_CREAT);
    nodesInspected = (long long*) shmat(shmidb, (void*) 0, 0);
    nodesInspected[0] = 0;
    // if ((semid_s = initsem(key_s, 1)) == -1) {
    //     perror("initsem");
    //     exit(1);
    // }
    // nodesToSearch = new ListStructurePtr<ToBeSearhed*>(ListStructure<ToBeSearhed*>::ORDEM_CRESCENTE);

    //min=new mpz_class();
    c.start();
    int k = 0;
    bfslist1 = new ListStructurePtr<CKKnode_bfs_mpz*>(ListStructurePtr<CKKnode_bfs_mpz*>::ORDEM_CRESCENTE);
    //comb = new Combinatorics(2, 2);
    //comb->generateAllArranges();
    // comb->printArranges();
    sem = new Semaphore(1);
    NodesPersecond = 0;
    //NumberVector = p->getNumberSource()->getVector();
    //(raiz, 0);
    //depthFirst(raiz);
    //LDS(raiz);
    int alpha = 100000;
    hashSearch1 = new Hash<int, CKKnode_bfs_mpz*>(p->getNumberSource()->getSize(), alpha);
    //depthFirst(raizDFS);
    //depthFirst(raizDFS);
}//

void * explore_mpz(void*ptr) {
    nodeExplorer_mpz * exp = (nodeExplorer_mpz*) ptr;
    //cout<<pthread_self()<<endl;
    exp->ckk->depthFirst(exp->nodeToExplore);

}
static ToBeSearched NULO;

ToBeSearched ToBeSearched::returnNULL() {
    return NULO;
}
//int initsem(key_t key, int nsems) /* key from ftok() */ {
//    int i;
//    union semun arg;
//    struct semid_ds buf;
//    struct sembuf sb;
//    int semid;
//    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);
//    if (semid >= 0) { /* we got it first */
//        sb.sem_op = 1;
//        sb.sem_flg = 0;
//        arg.val = 1;
//        printf("press return\n");
//        getchar();
//        for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
//            /* do a semop() to "free" the semaphores. */
//            /* this sets the sem_otime field, as needed below. */
//            if (semop(semid, &sb, 1) == -1) {
//                int e = errno;
//                semctl(semid, 0, IPC_RMID); /* clean up */
//                errno = e;
//                return -1; /* error, check errno */
//            }
//        }
//    } else if (errno == EEXIST) { /* someone else got it first */
//        int ready = 0;
//        semid = semget(key, nsems, 0); /* get the id */
//        if (semid < 0) return semid; /* error, check errno */
//        /* wait for other process to initialize the semaphore: */
//        arg.buf = &buf;
//        for (i = 0; i < MAX_RETRIES && !ready; i++) {
//            semctl(semid, nsems - 1, IPC_STAT, arg);
//            if (arg.buf->sem_otime != 0) {
//                ready = 1;
//            } else {
//                sleep(1);
//            }
//        }
//        if (!ready) {
//            errno = ETIME;
//            return -1;
//        }
//    } else {
//        return semid; /* error, check errno */
//    }
//    return semid;
//}
