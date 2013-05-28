/* 
 * File:   ComLookUp.cpp
 * Author: fernando
 * 
 * Created on May 28, 2013, 2:11 AM
 */

#include "CombLookUp.h"

CombLookUp::CombLookUp() {
}
CombLookUp::~CombLookUp() {
}
CombLookUp::CombLookUp(int n){
    combs = new vector<gsl_combination*>[n];
    this->n;
}
void CombLookUp::createAllUntil(int k){
    this->k;
    for(int i=0;i<k;i++){
        gsl_combination * temp =gsl_combination_calloc(n,i+1);
        ulong ncomb=gsl_combination_n(temp);
        for(int i=0;i<ncomb;i++){
            combs[i].push_back(temp);
            gsl_combination * temp1 =gsl_combination_calloc(n,i+1);
            gsl_combination_memcpy(temp1,temp);
            gsl_combination_next(temp1);
            temp=temp1;
        }
    }
}
