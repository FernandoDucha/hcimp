/* 
 * File:   PPN_Heap.cpp
 * Author: fernando
 * 
 * Created on 13 de Maio de 2013, 16:09
 */

#include "PPN_Heap.h"
#include "BasicTypes.h"
#include "Hash.h"

PPN_Heap::PPN_Heap(char * filename) {
    problem_file = filename;
    lerArquivo(filename);
    chrono.set_resolution(Cronometro::SEGUNDOS);
    nodes_inspected = 0;
    nodes_pruned = 0;
    perfect = false;
    perfectVal = -1;
}

PPN_Heap::~PPN_Heap() {
    delete raiz;
    delete raiz_bfs;
}

void PPN_Heap::lerArquivo(char * problemFile) {
    //cout<<4<<endl;
    ifstream filestr;
    char buff[10000];
    for (int i = 0; i < 100; i++)
        buff[i] = '\0';
    filestr.open(problemFile);
    filestr >> tempo; // = atoi(buff);

    //filestr.getline(buff, 100);
    filestr >> buff;

    //filestr.getline(buff, 100);
    filestr >> nElementos; // = atoi(buff);
    filestr >> buff;
    filestr >> nroParticoes;
    raiz = new mpz_node();
    raiz_bfs = new mpz_node_bfs();
    filestr >> buff;
    //mpz_heap_elem ** list = new mpz_heap_elem*[nElementos];
    for (int i = 0; i < nElementos; i++) {
        mpz_class temp;
        filestr >> temp;
        //cout<<temp<<endl;
        min += temp;
        raiz->pushElem(temp);
        raiz_bfs->pushElem(new mpz_heap_elem(temp));
    }
    //raiz_bfs->print();
    filestr.close();
}

void PPN_Heap::runDFS() {
    string file = problem_file;
    file += ".res";
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    this->chrono.start();
    runDFS(raiz);
    res.close();
}

void PPN_Heap::runDFS(mpz_node * node) {
    if (chrono.elapsed() >= tempo || perfect) {
        if (node->size() == nElementos - 1)
            res << log2(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        return;
    } else if (node->size() == 1) {
        min = node->getSum();
        perfect = (min == perfectVal) ? true : false;
        res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
    } else {
         mpz_node temp, temp1;
        temp = *node;
        nodes_inspected++;
        mpz_class A, B; // *Diff,*Sum;
//        temp.print();
        A = temp.removeLargest();
        //cout<<log2(A)<<endl;
        //temp.print();
        B = temp.removeLargest();
//        temp.print();
        //cout<<log2(B)<<endl;
        //        Diff = new mpz_class(A-B);
        //temp.print();
        temp.pushElem(A - B);
        //temp.print();
        temp.setParent(node);
        temp.setNodeId(nodes_inspected);
        if (!temp.prune(min, nroParticoes)) {
            runDFS(&temp);
        } else {
            nodes_pruned++;
        }
        temp1 = *node;
//        node->print();
        A = temp1.removeLargest();
        B = temp1.removeLargest();
        //Sum = new mpz_class(A+B);
        temp1.pushElem(A + B);
//        temp1.print();
        temp1.setParent(node);
        temp1.setNodeId(nodes_inspected);
        if (!temp1.prune(min, nroParticoes)) {
            runDFS(&temp1);
        } else {
            nodes_pruned++;
        }
        //delete Diff;
        //delete Sum;
    }
}

void PPN_Heap::runLDS() {
    string file = problem_file;
    file += ".res";
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    runLDS(raiz);
    res.close();
}

void PPN_Heap::runLDS(mpz_node * node) {
    chrono.start();
    for (int i = 0; i <= node->size(); i++) {
        runLDS(node, node->size(), i);
    }
}

void PPN_Heap::runLDS(mpz_node * node, u_int32_t depth, u_int32_t disc) {
    if (chrono.elapsed() >= tempo || perfect) {
        res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        return;
    } else if (node->size() == 1) {
        min = node->getSum();
        perfect = (min == perfectVal) ? true : false;
        res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
    } else {
        nodes_inspected++;
        if (depth > disc) {
            mpz_node temp;
            temp = *node;
            temp.setParent(node);
            mpz_class A = temp.removeLargest();
            mpz_class B = temp.removeLargest();
            mpz_class Diff = A - B;
            temp.pushElem(Diff);
            if (temp.prune(min, nroParticoes)) {
                nodes_pruned++;
            } else {
                runLDS(&temp, depth - 1, disc);
            }
        }
        if (disc > 0) {
            mpz_node temp;
            temp = *node;
            temp.setParent(node);
            mpz_class A = temp.removeLargest();
            mpz_class B = temp.removeLargest();
            mpz_class Sum = A + B;
            temp.pushElem(Sum);
            if (temp.prune(min, nroParticoes)) {
                nodes_pruned++;
            } else {
                runLDS(&temp, depth - 1, disc - 1);
            }
        }
    }
}

void PPN_Heap::KK(mpz_node * node) {
    if (node->size() == 1) {
        if (node->getSum() < min) {
            min = node->getSum();
            perfect = (min == perfectVal) ? true : false;
            res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        }
    } else {
        mpz_class A, B, DIFF;
        //cout<<node->getSum()<<endl;
        A = node->removeLargest();
        B = node->removeLargest();
        //cout<<node->getSum()<<endl;
        DIFF = A - B;
        node->pushElem(DIFF);
        KK(node);
    }
}
void PPN_Heap::KK(mpz_node_bfs * node){
    if (node->size() == 1) {
        if (node->getSum() < min) {
            min = node->getSum();
            perfect = (min == perfectVal) ? true : false;
            res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        }
        mpz_heap_elem_ptr Last=node->removeLargest();
        delete Last;
//        cout<<"soma final kk: "<< node->getSum()<<endl;
    } else {
        mpz_heap_elem_ptr A, B, DIFF;
        A = node->removeLargest();
        B = node->removeLargest();
        DIFF = &(*A-*B);
        DIFF->Original(false);        
        node->pushElem(DIFF);
        KK(node);
        if(A->isOrig()){
            node->pushElem(A);
        }else{
            delete A;
        }
        if(B->isOrig()){
            node->pushElem(B);
        }else{
            delete B;
        }
    }
}

void PPN_Heap::KK() {
    string file = problem_file;
    file += ".res";
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    chrono.start();
    KK(raiz);
    res.close();
}

void PPN_Heap::runBFS() {
    string file = problem_file;
    file += ".res";
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    chrono.start();
    raiz->setNodeId(0);
    runBFS(raiz_bfs);
    res.close();
}

void PPN_Heap::runBFS(mpz_node_bfs * node) {
    HashExtended hash(nElementos + 1, 10);
    hash.put(node);
    KK(node);
    hash.nextCyle();
    while (chrono.elapsed() <= tempo || !perfect) {
        int nelem = hash.getNElem();
        int j = 0;
        int i = 0;
        while (i < nelem) {
            mpz_node_bfs *left;
            ulong nh = hash.getHeightCoun(j);
            if (nh) {
                
                mpz_node_bfs ** line = hash.getHeightVector(j);
                for (int k = 0; k < nh; k++) {
                    left = line[k];
                    mpz_heap_elem_ptr A = left->removeLargest();
                    mpz_heap_elem_ptr B = left->removeLargest();
                    mpz_node_bfs * right = new mpz_node_bfs(*left);
                    left->pushElem(&(*A-*B));
                    nodes_inspected++;
                    right->pushElem(&(*A+*B));
                    nodes_inspected++;
                    right->setNodeId(left->getNodeId() + 1);
                    KK(right);
                    if (right->prune(min, nroParticoes)) {
                        nodes_pruned++;
                        delete right;
                    } else {
                        hash.put(right);
                    }
                    mpz_heap_elem::tryDeleting(A);
                    mpz_heap_elem::tryDeleting(B);
                    i++;
                }
                j++;
            } else {
                break;
            }
        }
        if (hash.peekFirst()->size() == 1) {
            break;
        }
        hash.nextCyle();
    }
}