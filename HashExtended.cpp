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
        hash[i] = new heap_node_p[(int)(maxElements/2)];
        for(int j=0;j<0.5*maxElements;j++){
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
        for (int i = 0; i < searchSpace; i++) {
            sum += count[i];
            if (sum > maxElem) {
                cout<<"entrou aqui"<<endl;
                ulong diff = sum - maxElem;
                int k=0;
                for (k = count[i]-1; k >= count[i]-diff; k--) {
                    delete hash[i][k];
                    hash[i][k]=NULL;
                    nElem--;
                }
                count[i]-=diff;
                for (int j = i + 1; j < searchSpace&&count[j]!=0; j++) {
                    for (int l = count[j] - 1; l >= 0; l--) {
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
    cout<<nElem<<endl;
    for (int i = 0; i < searchSpace; i++) {
        auxcount[i] = count[i];
        if(auxcount[i]!=0){
            if(hash[i][0]==NULL){
                cout<<"merda"<<endl;
            }
        }else{
            break;
        }
        //cout<<i<<"--"<<auxcount[i]<<"---"<<sum<<endl;
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