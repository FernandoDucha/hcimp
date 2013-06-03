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
PPN_Heap::PPN_Heap(){
    problem_file = NULL;
    chrono.set_resolution(Cronometro::SEGUNDOS);
    nodes_inspected = 0;
    nodes_pruned = 0;
    perfect = false;
    perfectVal = -1;
    raiz=NULL;
    raiz_bfs=NULL;
}
void PPN_Heap::openNewProblem(char* filename){
    problem_file=filename;
    if(raiz){
        delete raiz;
        raiz=NULL;
    }
    lerArquivo(filename);
}
PPN_Heap::~PPN_Heap() {
    delete raiz;
    //delete raiz_bfs;
}

void PPN_Heap::lerArquivo(char * problemFile) {
    //cout<<4<<endl;
    string temp = "instances/";
    temp += problem_file;
    FILE * file = fopen(temp.c_str(),"r");
    
    char buff[1000];
    for (int i = 0; i < 100; i++) {
        buff[i] = '\0';
    }
    fgets(buff,1000,file);
    tempo=atoi(buff);
    fgets(buff,1000,file);
    fgets(buff,1000,file);    
    nElementos=atoi(buff);; // = atoi(buff);
    fgets(buff,1000,file);    
    fgets(buff,1000,file);    
    nroParticoes=atoi(buff); 
    raiz = new mpz_node();
    raiz->data().GetHeap().reserve(nElementos+1);
    raiz_bfs = new mpz_node_bfs();
    raiz_bfs->data().GetHeap().reserve(nElementos+1);
    
    fgets(buff,1000,file);    
    for (int i = 0; i < nElementos; i++) {
        fgets(buff,1000,file);
        mpz_class temp(buff);
        min += temp;
        raiz->pushElem(temp);
        raiz_bfs->pushElem(new mpz_heap_elem(temp));
    }
    fclose(file);
}

void PPN_Heap::runDFS() {
    string file = problem_file;
    file += ".dfs";
    file = "results/" + file;

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
        mpz_class A, B;
        A = temp.removeLargest();
        B = temp.removeLargest();
        temp.pushElem(A - B);
        temp.setParent(node);
        temp.setNodeId(nodes_inspected);
        if (!temp.prune(min, nroParticoes)) {
            runDFS(&temp);
        } else {
            nodes_pruned++;
        }
        temp1 = *node;
        A = temp1.removeLargest();
        B = temp1.removeLargest();
        temp1.pushElem(A + B);
        temp1.setParent(node);
        temp1.setNodeId(nodes_inspected);
        if (!temp1.prune(min, nroParticoes)) {
            runDFS(&temp1);
        } else {
            nodes_pruned++;
        }
    }
}

void PPN_Heap::runLDS() {
    string file = problem_file;
    file += ".lds";
    file = "results/" + file;
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    runLDS(raiz);
    res.close();
}

void PPN_Heap::_runLDS() {
    string file = problem_file;
    file += ".res";
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    chrono.start();
    _runLDS(raiz);
    res.close();
}

void PPN_Heap::runLDS(mpz_node * node) {
    chrono.start();
    for (int i = 0; i <= node->size(); i++) {
        runLDS(node, node->size(), i);
    }
}

void PPN_Heap::_runLDS(mpz_node* node) {
    //    ProfilerStart("Teste");
    //    {
    mpz_node aux = *node;
    KK(&aux);
    for (int i = 1; i <= node->size(); i++) {
        gsl_combination * temp = gsl_combination_calloc(node->size(), i);
        bool r;
        do {
            aux = *node;
            r = combs.getNext(temp, i);
            int k = 0;
            mpz_class A, B;
            for (int j = 0; j < node->size() - 1; j++) {
                A = aux.removeLargest();
                B = aux.removeLargest();
                if (k < temp->k && temp->data[k] == j) {
                    aux.pushElem(A + B);
                    k++;
                } else {
                    aux.pushElem(A - B);
                }
                if (aux.prune(min, 2)) {
                    break;
                }
            }
            if (aux.size() == 1) {
                min = aux.getSum();
                perfect = (min == perfectVal) ? true : false;
                res << log2(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
            }
        } while (r);
        cout << i << "--" << chrono.elapsed() << endl;
    }
    //    }   ProfilerStop();

}

void PPN_Heap::runLDS(mpz_node * node, u_int32_t depth, u_int32_t disc) {
    if (chrono.elapsed() >= tempo || perfect) {
        res << log2(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        chrono.setStoped(true);
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

void PPN_Heap::KK(HeapStrctPtrMin & node) {
    if (node.size() == 1) {
        mpz_class result = node.pick_max()->getId();
        if (result < min) {
            min = result;
            perfect = (min == perfectVal) ? true : false;
            res << log2(result + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        }
        mpz_heap_elem_ptr Last = node.getMax();
        delete Last;
    } else {
        mpz_heap_elem_ptr A, B, DIFF;
        A = node.getMax();
        B = node.getMax();
        DIFF = &(*A - *B);
        DIFF->Original(false);
        node.Insert(DIFF);
        KK(node);
        if (!A->isOrig()) {
            delete A;
        }
        if (!B->isOrig()) {
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

mpz_node* PPN_Heap::getRaiz() const {
    return raiz;
}

void PPN_Heap::runBFS() {
    string file = problem_file;
    file += ".bfs";
    file = "results/" + file;
    res.open(file.c_str(), ios::out);
    perfectVal = (raiz->getSum() % 2 == 0) ? 0 : 1;
    chrono.start();
    raiz->setNodeId(0);
    runBFS(raiz_bfs);
    res.close();
    raiz_bfs=NULL;
}

void PPN_Heap::runBFS(mpz_node_bfs * node) {
    HashExtended hash(nElementos + 1, 100000);
    hash.put(node);
    HeapStrctPtrMin hmin;
    hmin = node->data();
    KK(hmin);
    hash.nextCyle();
    while (chrono.elapsed() <= tempo && !perfect) {
        int nelem = hash.getNElem();
        int j = 0;
        mpz_node_bfs *left;
        ulong nh;
        while(nh= hash.getHeightCoun(j)){
            mpz_node_bfs ** line = hash.getHeightVector(j);
            for (int k = 0; k < nh; k++) {
                left = line[k];
                mpz_heap_elem_ptr A = left->removeLargest();
                mpz_heap_elem_ptr B = left->removeLargest();
                mpz_node_bfs * right = new mpz_node_bfs(*left);
                left->pushElem(&(*A - *B));
                right->pushElem(&(*A + *B));
                nodes_inspected++;
                right->setNodeId(left->getNodeId() + 1);
                hmin = right->data();
                KK(hmin);
                hash.put(right);
                mpz_heap_elem::tryDeleting(A);
                mpz_heap_elem::tryDeleting(B);
            }
            j++;
        }
        j=0;
        if (hash.peekFirst()->size() == 1) {
            break;
        }
        hash.nextCyle();
    }
    res<< log2(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned <<" #"<< endl;
    chrono.setStoped(true);
}