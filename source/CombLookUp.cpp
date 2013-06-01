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
    combs = new vector<gsl_combination*>[n+1];
    this->n=n;
    for(int i=0;i<=n;i++){
        gsl_combination * temp=gsl_combination_calloc(n,i); 
        combs[i].push_back(temp);
//        cout<<combs[i].at(0)<<endl;
    }
}
bool CombLookUp::getNext(gsl_combination * ret, int k){
    gsl_combination_memcpy(ret,combs[k].at(0));
    int res = gsl_combination_next(combs[k].at(0));
    return (res==GSL_SUCCESS);
}
void CombLookUp::createAllUntil(int k){
    this->k=k;
    for(int i=0;i<=k;i++){
        gsl_combination * temp,*temp1;
        temp=gsl_combination_calloc(n,i);
        int res=0;
        do{            
            combs[i].push_back(temp);
            gsl_combination * temp1 =gsl_combination_calloc(n,i);
            gsl_combination_memcpy(temp1,temp);
            res=gsl_combination_next(temp1);
            temp=temp1;
        }while(res==GSL_SUCCESS);
        cout<<combs[i].size()<<endl;
        getchar();
    }
}
void CombLookUp::print(){
    for(int i=0;i<=k;i++){
        ulong size= combs[i].size();
        for(int j=0;j<size;j++){
            printf("{ ");
            gsl_combination_fprintf(stdout,combs[i].at(j),"%u");
            printf(" }\n");
        }
    }
}