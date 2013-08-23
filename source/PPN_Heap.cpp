/* 
 * File:   PPN_Heap.cpp
 * Author: fernando
 * 
 * Created on 13 de Maio de 2013, 16:09
 */

#include "PPN_Heap.h"
#include "BasicTypes.h"
#include "Hash.h"
#include "BFS.h"

PPN_Heap::PPN_Heap(char * filename) {
    problem_file = filename;
    lerArquivo(filename);
    chrono.set_resolution(Cronometro::SEGUNDOS);
    nodes_inspected = 0;
    nodes_pruned = 0;
    perfect = false;
    perfectVal = -1;
    finished = false;
    pertubationHistory = new bool*[nElementos];
    for (int i = 0; i < nElementos; i++) {
        pertubationHistory[i] = new bool[nElementos];
    }
    Cronometro::startIntern();
}

PPN_Heap::PPN_Heap() {
    problem_file = NULL;
    chrono.set_resolution(Cronometro::SEGUNDOS);
    nodes_inspected = 0;
    nodes_pruned = 0;
    perfect = false;
    perfectVal = -1;
    raiz = NULL;
    raiz_bfs = NULL;
    finished = false;
    Cronometro::startIntern();
}

void PPN_Heap::openNewProblem(char* filename) {
    problem_file = filename;
    if (raiz) {
        delete raiz;
        raiz = NULL;
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
    FILE * file = fopen(temp.c_str(), "r");

    char buff[1000];
    for (int i = 0; i < 100; i++) {
        buff[i] = '\0';
    }
    fgets(buff, 1000, file);
    tempo = atoi(buff);
    fgets(buff, 1000, file);
    fgets(buff, 1000, file);
    nElementos = atoi(buff);
    ; // = atoi(buff);
    fgets(buff, 1000, file);
    fgets(buff, 1000, file);
    nroParticoes = atoi(buff);
    raiz = new mpz_node();
    raiz->data().GetHeap().reserve(nElementos + 1);
    raiz_bfs = new mpz_node_bfs();
    raiz_bfs->data().GetHeap().reserve(nElementos + 1);

    fgets(buff, 1000, file);
    mpz_class * vectemp = new mpz_class[nElementos + 1];
    for (int i = 0; i < nElementos; i++) {
        fgets(buff, 1000, file);
        mpz_class temp(buff);
        vectemp[i + 1] = temp;
    }
    quicksort(vectemp, 1, nElementos);
    for (int i = 0; i < nElementos; i++) {
        numLookUpTable[vectemp[nElementos - i]] = i;
        invNumLookUpTable[i] = vectemp[nElementos - i];
        min += vectemp[nElementos - i];
        raiz->pushElem(vectemp[nElementos - i]);
        raiz_bfs->pushElem(new mpz_heap_elem(vectemp[nElementos - i]));
    }
    fclose(file);
    delete [] vectemp;
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
            res << log2_temp(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        return;
    } else if (node->size() == 1) {
        min = node->getSum();
        perfect = (min == perfectVal) ? true : false;
        res << log2_temp(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
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
        if (!finished) {
            runLDS(node, node->size(), i);
        } else {
            break;
        }
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
                res << log2_temp(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
            }
        } while (r);
        cout << i << "--" << chrono.elapsed() << endl;
    }
    //    }   ProfilerStop();

}

void PPN_Heap::runLDS(mpz_node * node, u_int32_t depth, u_int32_t disc) {
    if (finished) return;
    if ((chrono.elapsed() >= tempo || perfect)) {
        res << log2_temp(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << ";#" << endl;
        finished = true;
        return;
    } else if (node->size() == 1) {
        min = node->getSum();
        perfect = (min == perfectVal) ? true : false;
        res << log2_temp(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
    } else {
        bool chamada1 = false, chamada2 = false;
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
            res << log2_temp(node->getSum() + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
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
            res << log2_temp(result + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << endl;
        }
        mpz_heap_elem_ptr Last = node.getMax();
        delete Last;
    } else {
        mpz_heap_elem_ptr A, B, DIFF;
        A = node.getMax();
        B = node.getMax();
        nodes_inspected++;
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

SolutionObject * PPN_Heap::KKConstruct() {
    map<mpz_class, mpz_class> a1, a2;
    HeapStrctPtrMin temp;
    temp = raiz_bfs->data();
    KK(temp, a1, a2);
    map<mpz_class, mpz_class>::iterator begin, end;
    begin = a1.begin();
    end = a1.end();
    uint8_t * solv = new uint8_t[nElementos];
    for (int i = 0; i < nElementos; i++) {
        solv[i] = ZERO;
    }
    for (begin; begin != end; begin++) {
        uint16_t a = numLookUpTable[(*begin).first];
        solv[a] = ONE;
    }
    SolutionObject * a = new SolutionObject(invNumLookUpTable, solv, raiz->getSum());
    return a;
}

SolutionObject * PPN_Heap::GraspConstruct(double alpha) {
    uint8_t * solv = new uint8_t[nElementos];
    //    uint8_t * solv1 = new uint8_t[nElementos];
    mpz_class sum[2] = {0, 0};
    map<uint16_t, mpz_class> nonAssigned;
    gsl_rng * rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, Cronometro::elapsedIntern());
    nonAssigned = this->invNumLookUpTable;
    for (int i = 0; i < nElementos; i++) {
        solv[i] = ZERO;
        //        solv1[i]=ZERO;
    }
    for (int i = 0; i < nElementos; i++) {
        int menor = sum[0] < sum[1] ? 0 : 1;
        map<uint16_t, mpz_class> nonAssignedValues;
        map<uint16_t, mpz_class>::iterator beg = nonAssigned.begin(), end = nonAssigned.end();
        mpz_class maxVal = -raiz->getSum(), minVal = raiz->getSum();
        for (; beg != end; beg++) {
            sum[menor] += beg->second;
            mpz_class diff = sum[menor] - sum[(menor + 1) % 2];
            diff = (diff < 0) ? -diff : diff;
            if (maxVal < diff) {
                maxVal = diff;
            }
            if (minVal > diff) {
                minVal = diff;
            }
            nonAssignedValues[beg->first] = diff;
            sum[menor] -= beg->second;
        }
        mpz_class RCLLim = minVal + alpha * (maxVal - minVal);
        vector<uint16_t> RCL;
        beg = nonAssignedValues.begin();
        end = nonAssignedValues.end();
        for (; beg != end; beg++) {
            if (beg->second <= RCLLim) {
                RCL.push_back(beg->first);
            }
        }
        int chosen = gsl_rng_uniform_int(rng, RCL.size());
        sum[menor] += nonAssigned[RCL[chosen]];
        if (menor == 0) {
            solv[RCL[chosen]] = ONE;
        }
//        cout<<"0 "<<sum[0]<<" - "<<"1 "<<sum[1]<<endl;
        nonAssigned.erase(RCL[chosen]);
    }
    SolutionObject * ret = new SolutionObject(invNumLookUpTable, solv, raiz->getSum());
//    cout << log2(ret->getResult()) << endl;
//    mpz_class diff = sum[0] - sum[1];
//    diff = (diff < 0) ? -diff : diff;
//    cout << log2(diff) << endl;
//    exit(0);
    return ret;
}
void PPN_Heap::ILS_Grasp(double alpha){
    set<mpz_class> bacias;
    set<mpz_class> descidas;
    pair < set<mpz_class>::iterator, bool> exists;
    chrono.start();
    gsl_rng * rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, Cronometro::elapsedIntern());
    Cronometro c(Cronometro::SEGUNDOS);
    c.start();
    SolutionObject * init  = GraspConstruct(alpha);
    steepestDescent(init);
    SolutionObject temp;
    temp=*init;
    double j = 0, k = 0;
    int l=1;
    double weight = 1;
    for (int i = 0; i < 1000000; i++) {
        pertubation(&temp, rng, 1, 5, 10);
        exists = bacias.insert(temp.encode());
        if (exists.second) {
            steepestDescent(&temp);
            exists = descidas.insert(temp.encode());
            k++;
            if (exists.second) {
                if (temp.getResult() < init->getResult()) {
                    *init = temp;
                    cout << log2(temp.getResult()) << " Tempo: " << c.elapsed() << " Descidas:" << k << endl;
                    k = 0;
                    j = c.elapsed();
                    //                    weight=1;
                }
            } else {
                cout << "repetiu descida" << endl;
            }
        } else {
            cout << "repetiu perturbação" << endl;
        }
        if (c.elapsed() - j >= 50) {
            weight += 0.1;
            j = c.elapsed();
            l++;
            cout << weight << " Tempo:" << j << " Descidas:" << k << endl;
        }
        if((l%10)==0){
            weight=1;
            temp = *GraspConstruct(alpha);
            steepestDescent(&temp);
        }
    }   
}

void PPN_Heap::ILS_KK() {
    set<mpz_class> bacias;
    set<mpz_class> descidas;
    pair < set<mpz_class>::iterator, bool> exists;
    chrono.start();
    SolutionObject * init = KKConstruct();
    steepestDescent(init);
    gsl_rng * rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, Cronometro::elapsedIntern());
    SolutionObject temp;
    temp = *init;
    bacias.insert(temp.encode());
    Cronometro c(Cronometro::SEGUNDOS);
    c.start();
    double j = 0;int k = 0;
    double weight = 1;
    for (int i = 0; i < 1000000; i++) {
        pertubation(&temp, rng, 1, 5, 10);
//        exists = bacias.insert(temp.encode());
//        if (exists.second) {
            steepestDescent(&temp);
//            exists = descidas.insert(temp.encode());
            k++;
//            if (exists.second) {
                if (temp.getResult() < init->getResult()) {
                    *init = temp;
                    cout << log2(temp.getResult()) << " Tempo: " << c.elapsed() << " Descidas:" << k << endl;
                    k = 0;
                    weight=1;
                    //                    weight=1;
                }
//            } else {
//                cout << "repetiu descida" << endl;
//            }
//        } else {
//            cout << "repetiu perturbação" << endl;
//        }
        if ((k%5000)==0) {
            weight += 0.2;
            cout << weight << " Tempo:" << c.elapsed() << " Descidas:" << k << endl;
        }
    }
}

void PPN_Heap::pertubation(SolutionObject * sol, gsl_rng * rng, double strength, int Invertions, int Swaps) {
    int inv = strength*Invertions;
    int swp = strength*Swaps;
    set<uint16_t> historyInvert;
    set<swap> historySwap;
    pair < set<uint16_t>::iterator, bool> historyInvertRet;
    for (int i = 0; i < inv; i++) {
        uint16_t t = (uint16_t) gsl_rng_uniform_int(rng, nElementos);
        historyInvertRet = historyInvert.insert(t);
        if (historyInvertRet.second) {
            sol->makeMoveInvert((*historyInvertRet.first));
        } else {
            i--;
        }
    }
    for (int j = 0; j < swp; j++) {
        uint16_t a = gsl_rng_uniform_int(rng, nElementos);
        uint16_t b = gsl_rng_uniform_int(rng, nElementos);
        swap p1(a, b);
        swap p2(b, a);
        bool b1 = historySwap.insert(p1).second;
        bool b2 = historySwap.insert(p2).second;
        if (sol->testMoveSwap(p1) > 0 && (b1 && b2)) {
            if ((historyInvert.find(a) == historyInvert.end()) || (historyInvert.find(b) == historyInvert.end())) {
                sol->makeMoveSwap(p1);
            } else {
                j--;
            }
        } else {
            j--;
        }
    }
}

void PPN_Heap::pertubation1(SolutionObject * sol, gsl_rng * rng, double strength, int Invertions, int Swaps) {
    int inv = strength*Invertions;
    int swp = strength*Swaps;
    cleanHistory();
    //    set<uint16_t> historyInvert;
    //    set<swap> historySwap;
    //    pair < set<uint16_t>::iterator, bool> historyInvertRet;
    for (int i = 0; i < inv; i++) {
        uint16_t t = (uint16_t) gsl_rng_uniform_int(rng, nElementos);
        //        historyInvertRet = historyInvert.insert(t);
        if (!pertubationHistory[t][t]) {
            pertubationHistory[t][t] = true;
            sol->makeMoveInvert(t);
        } else {
            i--;
        }
    }
    for (int j = 0; j < swp; j++) {
        uint16_t a = gsl_rng_uniform_int(rng, nElementos);
        uint16_t b = gsl_rng_uniform_int(rng, nElementos);
        bool *b1 = &pertubationHistory[a][b];
        bool *b2 = &pertubationHistory[b][a];
        if (sol->testMoveSwap(swap(a, b)) > 0 && (!(*b1) && !(*b2))) {
            if ((!pertubationHistory[a][a]) || (!pertubationHistory[b][b])) {
                sol->makeMoveSwap(swap(a, b));
                *b1 = ~(*b1);
                *b2 = ~(*b2);
            } else {
                j--;
            }
        } else {
            j--;
        }
    }
}

void PPN_Heap::steepestDescent(SolutionObject * sobj) {
    int bestIndex = -1;
    swap bestSwap = swap(-1, -1);
    bool improved = false;
    do {
        improved = false;
        bestIndex = -1;
        mpz_class bestRes = sobj->getResult();
        for (uint16_t i = 0; i < nElementos; i++) {
            mpz_class temp = sobj->testMoveInvert(i);
            if (temp < bestRes) {
                bestIndex = i;
                bestRes = temp;
                improved = true;
            }
        }
        bestSwap = swap(-1, -1);
        mpz_class bestRes1 = sobj->getResult();
        for (uint16_t i = 0; i < nElementos; i++) {
            for (uint16_t j = i + 1; j < nElementos; j++) {
                mpz_class temp = sobj->testMoveSwap(swap(i, j));
                if ((temp >= 0)&&(temp < bestRes1)) {
                    bestSwap = swap(i, j);
                    bestRes1 = temp;
                    improved = true;
                }
            }
        }
        if (improved) {
            if (bestRes <= bestRes1) {
                sobj->makeMoveInvert(bestIndex);
            } else if (bestRes > bestRes1) {
                sobj->makeMoveSwap(bestSwap);
            }
        }
    } while (improved);
}

void PPN_Heap::KK(HeapStrctPtrMin & node, map<mpz_class, mpz_class> & A1, map<mpz_class, mpz_class> & A2) {
    if (node.size() == 1) {
        mpz_class result = node.pick_max()->getId();
        if (result < min) {
            min = result;
            perfect = (min == perfectVal) ? true : false;
            cout << log2_temp(result + 1) << endl;
        }
        node.getMax();
    } else {
        mpz_heap_elem_ptr A, B, DIFF;
        A = node.getMax();
        B = node.getMax();
        nodes_inspected++;
        DIFF = &(*A - *B);
        DIFF->Original(false);
        node.Insert(DIFF);
        KK(node, A1, A2);
        map<mpz_class, mpz_class>::iterator it;
        it = A1.find(DIFF->getId());
        if (it != A1.end()) {
            A1.erase(it);
            A1[A->getId()] = A->getId();
            A2[B->getId()] = B->getId();
        } else {
            it = A2.find(DIFF->getId());
            if (it != A2.end())
                A2.erase(it);
            A1[B->getId()] = B->getId();
            A2[A->getId()] = A->getId();
        }
        delete DIFF;
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
    raiz_bfs = NULL;
}

void PPN_Heap::runBFS(mpz_node_bfs * node) {
    HashExtended hash(nElementos + 1, 100000);
    hash.put(node);
    HeapStrctPtrMin hmin;
    hmin = node->data();
    KK(hmin);
    hash.nextCyle();
    char end = '#';
    while (chrono.elapsed() <= tempo && !perfect) {
        int nelem = hash.getNElem();
        int j = 0;
        mpz_node_bfs *left;
        ulong nh;
        while (nh = hash.getHeightCoun(j)) {
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
        if (hash.peekFirst()->size() == 1) {
            end = '$';
            break;
        }
        hash.nextCyle();
    }
    res << log2_temp(min + 1) << ";" << chrono.elapsed() << ";" << nodes_inspected << ";" << nodes_pruned << ";" << end << endl;
    chrono.setStoped(true);
    exit(0);
}