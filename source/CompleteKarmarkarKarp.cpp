/* 
 * File:   CompleteKarmarkarKarp.cpp
 * Author: fernando
 * 
 * Created on 5 de Setembro de 2011, 18:02
 */

#include "CompleteKarmarkarKarp.h"
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

CompleteKarmarkarKarp::CompleteKarmarkarKarp(ListStructure<number_element> * source, int nroParticoes) {
    nodesInspected = 0;
    nodesPruned = 0;
    raiz = new CKKnode();
    this->nroParticoes = nroParticoes;
    GenerateRaiz(source, nroParticoes);
    min = LONG_LONG_MAX;

    //    for (int k = 0; k < 10; k++) {
    //        cout << raiz.nodeList.List->retrieve_K_esimo(k)->element.List->retrieve_K_esimo(0)->element.List->retrieve_K_esimo(0)->element.id << endl;
    //    }
    // raiz.nodeList.List->resetLastAcc();
    // ListOfSums A = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // ListOfSums B = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // mergeListOfSums(A, B);
    c.set_resolution(Cronometro::SEGUNDOS);
    createChildren(raiz);

}

CompleteKarmarkarKarp::CompleteKarmarkarKarp(const CompleteKarmarkarKarp& orig) {
}

CompleteKarmarkarKarp::~CompleteKarmarkarKarp() {
}

void CompleteKarmarkarKarp::GenerateRaiz(ListStructure<number_element> * source, int nPart) {
    for (int i = 0; i < source->getSize(); i++) {
        BookKeeping * novo = new BookKeeping();
        novo->addElementToList(new number_element(source->nextFromLastAcc()->element.id));
        ListOfSums * list = new ListOfSums();
        list->addElementToList(novo);
        for (int j = 1; j < nPart; j++) {
            BookKeeping * zeroGroup = new BookKeeping();
            list->addElementToList(zeroGroup);
        }
        raiz->nodeList->addElementToList(list);
    }
    source->resetLastAcc();
}

BookKeeping * CompleteKarmarkarKarp::mergeBookKepings(BookKeeping * A, BookKeeping * B) {
    //    NNEWS++;
    //BookKeeping * ret = new BookKeeping();
    //  node_list_struct<number_element*> numbersFromA;                                                          = A->List->nextFromLastAcc();
    //    while (numbersFromA != NULL){
    //        ret->addElementToList(new number_element(numbersFromA->element->id));
    //        numbersFromA = A->List->nextFromLastAcc();
    //    }
    // int nb=0;// = B->List->getSize();
    // int na=0; //= A->List->getSize();
    bool boolA = false;
    bool boolB = false;
    if (A != NULL && A->List->getSize() > 0) {
        boolA = true;
    }
    if (B != NULL && B->List->getSize() > 0) {
        boolB = true;
    }
    if (boolA || boolB) {
        BookKeeping * ret = new BookKeeping();
        if (boolA) {
            node_list_struct<number_element*> * numbersFromA = A->List->nextFromLastAcc();
            while (numbersFromA != NULL) {
                //        NNEWS++;
                ret->addElementToList(new number_element(numbersFromA->element->id));
                numbersFromA = A->List->nextFromLastAcc();
            }
        }
        if (boolB) {
            node_list_struct<number_element*> * numbersFromB = B->List->nextFromLastAcc();
            while (numbersFromB != NULL) {
                //        NNEWS++;
                ret->addElementToList(new number_element(numbersFromB->element->id));
                numbersFromB = B->List->nextFromLastAcc();
            }
        }
        return ret;
    } else
        return NULL;
}

inline ListStructurePtr<ListOfSums*> * CompleteKarmarkarKarp::mergeListOfSums(ListOfSums * A, ListOfSums * B) {
    //    NNEWS++;
    ListStructurePtr<ListOfSums*>* ret = new ListStructurePtr<ListOfSums*>(ListStructurePtr<ListOfSums*>::ORDEM_CRESCENTE);
    bool notmerged[20];
    int nonZeroA = numberOfNonZeroElements(A);
    int nonZeroB = numberOfNonZeroElements(B);
    int An = A->List->getSize();
    int Bn = B->List->getSize();
    //    if(nonZeroA==3&&nonZeroB==3){
    //        cout<<endl;
    //    }
    //if (A->List->getSize() < nonZeroA + 1) {
    //        NNEWS--;
    //  A->List->Add(new BookKeeping());
    //}
    //if (B->List->getSize() < nonZeroB + 1) {
    //        NNEWS--;
    //  B->List->Add(new BookKeeping());
    //}
    //    if (nonZeroA == 3 && nonZeroB == 2) {
    //        cout << endl;
    //    } else if (nonZeroA == 2 && nonZeroB == 3) {
    //        cout << endl;
    //    }
    // BookKeeping ** vectorFromA = A->List->getVector();
    // cout<<"###"<<endl;
    // A->List->PrintLista();
    // BookKeeping ** vectorFromB = B->List->getVector();
    // cout<<"###"<<endl;
    // B->List->PrintLista();
    if (nonZeroA > nonZeroB) {
        Combinatorics comb(nonZeroA + 1, nonZeroB);
        comb.generateAllArranges();
        //comb.printArranges();
        int narr = comb.Arranjo(nonZeroA + 1, nonZeroB);
        for (int i = narr - 1; i >= 0; i--) {
            //            NNEWS++;
            ListOfSums * los = new ListOfSums();

            for (int j = 0; j < nonZeroB; j++) {
                BookKeeping* nodeA = A->List->retrieve_K_esimo(comb.getArrangePosition(i, j));
                BookKeeping*nodeB = B->List->retrieve_K_esimo(j);
                BookKeeping*bkpA;
                BookKeeping*bkpB;
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
                BookKeeping * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    los->addElementToList(bkp);
                }
            }
            //            NNEWS++;
            //bool * notmerged = new bool[nonZeroA + 1];
            for (int k = 0; k < nonZeroA + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroB; l++) {
                notmerged[comb.getArrangePosition(i, l)] = true;
            }

            for (int m = nonZeroB, n = 0; n < nonZeroA + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping* nodeA = A->List->retrieve_K_esimo(n);
                    BookKeeping*nodeB = B->List->retrieve_K_esimo(m);
                    BookKeeping*bkpA;
                    BookKeeping*bkpB;
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
                    BookKeeping * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        los->addElementToList(bkp);
                    }
                    //los->addElementToList(bkp);
                }
            }
            //cout<<"###"<<endl;
            //los->List->PrintLista();
            //            NDELS++;
            //delete [] notmerged;
            normalize(los);
            ret->Add(los);
        }
        //ret->PrintLista();
        //        if(nonZeroA+1<nroParticoes){
        //            for(int i=nonZeroA+1;i<nroParticoes;i++){
        //                ret->Add(new ListOfSums());
        //            }
        //        }
    } else {
        Combinatorics comb(nonZeroB + 1, nonZeroA);
        comb.generateAllArranges();
        int narr = comb.Arranjo(nonZeroB + 1, nonZeroA);
        //  int ** arr=comb.getArranges();
        // comb.printArranges();
        for (int i = narr - 1; i >= 0; i--) {
            //            NNEWS++;
            ListOfSums * los = new ListOfSums();
            for (int j = 0; j < nonZeroA; j++) {
                BookKeeping* nodeB = B->List->retrieve_K_esimo(comb.getArrangePosition(i, j));
                BookKeeping*nodeA = A->List->retrieve_K_esimo(j);
                BookKeeping*bkpA;
                BookKeeping*bkpB;
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
                BookKeeping * bkp = mergeBookKepings(bkpA, bkpB);
                if (bkp != NULL) {
                    los->addElementToList(bkp);
                }
            }
            //            NNEWS++;
            // bool * notmerged = new bool[nonZeroB + 1];
            for (int k = 0; k < nonZeroB + 1; k++) {
                notmerged[k] = false;
            }
            for (int l = 0; l < nonZeroA; l++) {
                notmerged[comb.getArrangePosition(i, l)] = true;
            }
            for (int m = nonZeroA, n = 0; n < nonZeroB + 1; n++) {
                if (!notmerged[n]) {
                    BookKeeping* nodeB = B->List->retrieve_K_esimo(n);
                    BookKeeping*nodeA = A->List->retrieve_K_esimo(m);
                    BookKeeping*bkpA;
                    BookKeeping*bkpB;
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
                    BookKeeping * bkp = mergeBookKepings(bkpA, bkpB);
                    if (bkp != NULL) {
                        los->addElementToList(bkp);
                    }
                }
            }
            //            int c=numberOfNonZeroElements(los);
            los = normalize(los);
            //cout<<"###"<<endl;
            // los->List->PrintLista();
            //            int c1=numberOfNonZeroElements(los);
            ret->Add(los);
            //            NDELS++;
            //delete [] notmerged;

        }
        //ret->PrintLista();
        //        if(nonZeroB+1<nroParticoes){
        //            for(int i=nonZeroB+1;i<nroParticoes;i++){
        //                ret->Add(new ListOfSums());
        //            }
        //        }
    }
    //    NDELS += 2;
    //delete [] vectorFromA; // = A->List->getVector();
    // delete [] vectorFromB; // = B->List->getVector();
    //  ret->PrintLista();
    //cout<<"Tamanho da Lista: "<<ret->getSize()<<endl;

    return ret;
}

void CompleteKarmarkarKarp::createChildren(CKKnode *Parent) {
    int nls = Parent->nodeList->List->getSize();
    // cout << nls << endl;

    pthread_mutex_lock(&mutex2);
    nodesInspected++;
    if (c.elapsed() > 5) {
        if (nls == 1) {
            long long temp = Parent->nodeList->List->peekFirst()->List->peekFirst()->id - Parent->nodeList->List->peekFirst()->List->peekLast()->id;
            cout << nodesInspected << " -- " << nodesPruned << " -- " << (double) nodesPruned / nodesInspected << " -- " << min << " -- " << temp << endl;
        } else {
            cout << nodesInspected << " -- " << nodesPruned << " -- " << (double) nodesPruned / nodesInspected << " -- " << min << " -- " << nls << endl;
        }
        c.end();
        c.start();
    }
    pthread_mutex_unlock(&mutex2);
    //cout<<nodesInspected<<" -- "<<min<<endl;

    //Parent->nodeList->List->PrintLista();
    //if(nls==4){
    // cout<<nls<<endl;
    //}
    if (nls == 1) {
        long long temp = Parent->nodeList->List->peekFirst()->List->peekFirst()->id - Parent->nodeList->List->peekFirst()->List->peekLast()->id;
        if (temp < min) {
            pthread_mutex_lock(&mutex1);
            min = temp;
            p->cloneSolutionToBest(Parent->nodeList->List->peekFirst());
            cout << temp << endl;
            pthread_mutex_unlock(&mutex1);
            // cout << nodesInspected << " -- " << min << endl;
        } else {
            Parent->cleanNode();
            Parent->cleanChildren();
        }
    } else {
        // ListStructure<ListOfSums>* cloneNodeList=Parent.nodeList.List->clone();

        ListOfSums* A = Parent->nodeList->List->RemoveFront();
        ListOfSums* B = Parent->nodeList->List->RemoveFront();
        //        NNEWS = 0;
        //        NDELS = 0;
        //        pthread_mutex_lock(&mutex3);
        ListStructurePtr<ListOfSums*>* childrenCandidates = mergeListOfSums(A, B);
        //        pthread_mutex_unlock(&mutex3);

        //cout<<NNEWS<<" -- "<<NDELS<<endl;
        //if (nls == 2) {
        //    cout << childrenCandidates->getSize() << endl;
        //}
        //NDELS=0;
        //NDELS+=2;
        delete A;
        delete B;
        // cout<<NDELS<<endl;
        node_list_struct<ListOfSums*>* los;
        while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
            CKKnode * nodetemp = new CKKnode();
            nodetemp->nodeList->addElementToList(los->element);
            nodetemp->nodeList->addListToList(cloneListOfListOfSums(Parent->nodeList->List));
            nodetemp->updateNodeId();
            if (prune(nodetemp)) {
                //cout<<"Prunned -- "<<nls<<" -- "<<Parent->children->getSize()<<endl;
                nodetemp->cleanNode();
                nodetemp->cleanChildren();
                delete nodetemp;
                pthread_mutex_lock(&mutex2);
                nodesPruned++;
                pthread_mutex_unlock(&mutex2);
            } else {
                Parent->children->Add(nodetemp);
            }
        }
        //        if(childrenCandidates->getSize()==24){
        //            cout<<endl;
        //        }

        //        NDELS = 1;
        // pthread_mutex_lock(&mutex3);
        childrenCandidates->ClearList();
        delete childrenCandidates;
        //  pthread_mutex_unlock(&mutex3);

        //  cout<<NDELS<<endl;
        Parent->cleanNode();
        node_list_struct<CKKnode*> * nodeit = Parent->children->nextFromLastAcc();
        //        if(Parent->children->getSize()==6){
        //            cout<<nls<<" -- ";
        //        }
        while (nodeit != NULL) {
            if (min != 0 && min != 1) {
                //nodeit->element->nodeList->List->PrintLista();
                createChildren(nodeit->element);
            }
            // nodeit->element.nodeList.List->peekFirst()->element.List->peekFirst()->element;
            nodeit = Parent->children->nextFromLastAcc();
        }
        Parent->cleanChildren();
    }


}

void CompleteKarmarkarKarp::run() {
    c.start();
    nodesInspected++;
    ListOfSums* A = raiz->nodeList->List->RemoveFront();
    ListOfSums* B = raiz->nodeList->List->RemoveFront();
    ListStructurePtr<ListOfSums*>* childrenCandidates = mergeListOfSums(A, B);
    delete A;
    delete B;
    node_list_struct<ListOfSums*>* los;
    while ((los = childrenCandidates->nextFromLastAcc()) != NULL) {
        CKKnode * nodetemp = new CKKnode();
        nodetemp->nodeList->addElementToList(cloneListOfSums(los->element));
        nodetemp->nodeList->addListToList(cloneListOfListOfSums(raiz->nodeList->List));
        //nodetemp->nodeList->List->PrintLista();
        raiz->children->Add(nodetemp);
    }
    delete childrenCandidates;
    raiz->cleanNode();
    node_list_struct<CKKnode*> * nodeit = raiz->children->nextFromLastAcc();
    pthread_t * threads = new pthread_t[2];
    int i = 0;
    while (nodeit != NULL) {
        nodeExplorer * nd = new nodeExplorer();
        nd->ckk = this;
        nd->nodeToExplore = nodeit->element;
        int a = pthread_create(&threads[i], NULL, explore, (void*) nd);
        //createChildren();
        // nodeit->element.nodeList.List->peekFirst()->element.List->peekFirst()->element;
        nodeit = raiz->children->nextFromLastAcc();
    }
    for (int i = 0; i < 2; i++) {

        pthread_join(threads[i], NULL);
    }
    raiz->cleanChildren();
}

long long CompleteKarmarkarKarp::GetMin() const {

    return min;
}

ListOfSums * CompleteKarmarkarKarp::cloneListOfSums(ListOfSums * los) {
    node_list_struct<BookKeeping*>*bkp;
    ListOfSums * l = new ListOfSums();
    while ((bkp = los->List->nextFromLastAcc()) != NULL) {
        BookKeeping * b = new BookKeeping();
        //delete b->List;
        node_list_struct<number_element*>*num;
        while ((num = bkp->element->List->nextFromLastAcc()) != NULL) {

            b->addElementToList(new number_element(num->element->id));
            //delete num->element;
            //        num->element=NULL;
        }
        b->id = bkp->element->id;
        //delete bkp->element->List;
        // bkp->element->List=NULL;
        // delete bkp->element;
        l->addElementToList(b);
    }
    // delete los;
    return l;
}

ListStructurePtr<ListOfSums*>* CompleteKarmarkarKarp::cloneListOfListOfSums(ListStructurePtr<ListOfSums*>* list) {
    node_list_struct<ListOfSums*> *los;
    ListStructurePtr<ListOfSums*>*ret = new ListStructurePtr<ListOfSums*>(ListStructurePtr<ListOfSums*>::ORDEM_DECRESCENTE);
    //cout<<list->getSize()<<endl;
    int i = 0;
    while ((los = list->nextFromLastAcc()) != NULL) {
        node_list_struct<BookKeeping*>*bkp;
        ListOfSums * l = new ListOfSums();
        i++;
        while ((bkp = los->element->List->nextFromLastAcc()) != NULL) {
            BookKeeping * b = new BookKeeping();
            //delete b->List;
            node_list_struct<number_element*>*num;
            while ((num = bkp->element->List->nextFromLastAcc()) != NULL) {

                b->addElementToList(new number_element(num->element->id));
            }

            b->id = bkp->element->id;
            l->addElementToList(b);

        }
        ret->Add(l);
    }
    return ret;
}

bool CompleteKarmarkarKarp::prune(CKKnode * node) {
    node_list_struct<BookKeeping*> * major = node->nodeList->List->nextFromLastAcc()->element->List->nextFromLastAcc();
    long long sum = 0;
    node_list_struct<BookKeeping*> *bkit;
    while ((bkit = node->nodeList->List->peekFirst()->List->nextFromLastAcc())) {
        sum += bkit->element->id;
    }
    node_list_struct<ListOfSums*> * it;
    while ((it = node->nodeList->List->nextFromLastAcc()) != NULL) {
        sum += it->element->id;
    }
    long long diff = major->element->id - sum / (nroParticoes - 1);
    if (diff > min) {

        return true;
    }
    return false;
}

ListOfSums * CompleteKarmarkarKarp::normalize(ListOfSums * A) {
    if (numberOfNonZeroElements(A) == nroParticoes) {
        long long normalizer = A->List->peekLast()->id;
        node_list_struct<BookKeeping*> * bkp = A->List->nextFromLastAcc();
        while (bkp != NULL) {
            bkp->element->id -= normalizer;
            bkp = A->List->nextFromLastAcc();
        }
        A->id -= normalizer * A->List->getSize();

        return A;
    }
    return A;
}

int CompleteKarmarkarKarp::numberOfNonZeroElements(ListOfSums * A) {
    int ret = 0;
    node_list_struct<BookKeeping*> * aux; // = A.List->nextFromLastAcc();
    while ((aux = A->List->nextFromLastAcc()) != NULL) {
        if (aux->element->id != 0) {

            ret++;
        }
    }
    return ret;
}

CompleteKarmarkarKarp::CompleteKarmarkarKarp(NumberPartitionProblem * npp, int nroParticoes) {

    nodesInspected = 0;
    nodesPruned = 0;
    raiz = new CKKnode();
    this->nroParticoes = nroParticoes;
    GenerateRaiz(npp->getNumberSource(), nroParticoes);
    min = LONG_LONG_MAX;
    this->p = npp;
    //    for (int k = 0; k < 10; k++) {
    //        cout << raiz.nodeList.List->retrieve_K_esimo(k)->element.List->retrieve_K_esimo(0)->element.List->retrieve_K_esimo(0)->element.id << endl;
    //    }
    // raiz.nodeList.List->resetLastAcc();
    // ListOfSums A = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // ListOfSums B = raiz.nodeList.List->nextFromLastAcc()->element; //.List->nextFromLastAcc()->element;
    // mergeListOfSums(A, B);
    // createChildren(raiz);
    c.set_resolution(Cronometro::SEGUNDOS);
    //createChildren(raiz);
}

void * explore(void*ptr) {
    nodeExplorer * exp = (nodeExplorer*) ptr;
    exp->ckk->createChildren(exp->nodeToExplore);
}