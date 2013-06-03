/* 
 * File:   HashExtended.cpp
 * Author: fernando
 * 
 * Created on 21 de Maio de 2013, 07:54
 */


#include "HashExtended.h"

HashExtended::HashExtended(int maxDepth, int maxElements) {
    hash = new heap_node_p*[maxDepth];
    for (int i = 0; i < maxDepth; i++) {
        hash[i] = new heap_node_p[maxElements];
        for(int j=0;j<maxElements;j++){
            hash[i][j]=NULL;
        }
    }
    count = new ulong[maxDepth];
    auxcount = new ulong[maxDepth];
    for (int i = 0; i < maxDepth; i++) {
        auxcount[i] = count[i] = 0;
    }
    searchSpace = maxSize = maxDepth;
    nElem = 0;
    maxElem = maxElements;
}

HashExtended::~HashExtended() {
    vector<mpz_heap_elem*> vec;
    for (int i = 0;i<maxSize ; i++) {
        for(int j=0;j<maxElem;j++){
            if(hash[i][j]){
//                int s =hash[i][j]->data().GetHeap().size();
//                for(int k=s-1;k>=0;k--){
//                    mpz_heap_elem * elem=hash[i][j]->data().GetHeap()[k];
//                    hash[i][j]->data().GetHeap().pop_back();
//                    (*elem)--;
//                    if(!contains(vec,elem)){
//                        vec.push_back(elem);
//                    }
//                }
                delete hash[i][j];
            }else{
                break;
            }
        }
        delete [] hash[i];
    }
//    int size= vec.size();
//    for(int i=size-1;i>=0;i--){
//       mpz_heap_elem* b = vec[i];
//       vec.pop_back();
//       delete b;
//    }
    delete [] hash;
    delete [] count;
    delete [] auxcount;
}
bool HashExtended::contains(vector<mpz_heap_elem*> v, mpz_heap_elem* elem){
    for(int i=0;i<v.size();i++){
        if(v[i]==elem){
            return true;
        }
    }
    return false;
}
void HashExtended::put(mpz_node_bfs * novo) {
    ulong id = novo->getNodeId().get_ui();
    hash[id][count[id]]=novo;
    count[id]++;
    nElem++;
}

void HashExtended::nextCyle() {
    if (nElem >= maxElem) {
        ulong sum = 0;
        for (int i = 0;count[i]!=0; i++) {
            sum += count[i];
            if (sum > maxElem) {
                ulong diff = sum - maxElem;
                int k=0;
                int countdiff=count[i]-diff;
                for (k = count[i]-1;k>=countdiff; k--) {
                    delete hash[i][k];
                    hash[i][k]=NULL;
                    nElem--;
                }
                count[i]-=diff;
                for (int j = i + 1; count[j]!=0; j++) {
                    for (int l = count[j]-1; l >= 0; l--) {
                        delete hash[j][l];
                        hash[j][l]=NULL;
                        nElem--;
                    }
                    auxcount[j] = count[j] = 0;
                }
                break;
            }
        }
    }
    for (int i = 0;count[i]!=0; i++) {
        auxcount[i] = count[i];        
    }
}

int HashExtended::getNElem() const {
    return nElem;
}

ulong HashExtended::sizeHeight(int h) {
    return auxcount[h];
}

mpz_node_bfs * HashExtended::peekFirst() {
    return hash[0][0];
}
