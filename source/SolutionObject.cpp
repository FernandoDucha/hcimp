/* 
 * File:   SolutionObject.cpp
 * Author: fordem
 * 
 * Created on July 19, 2013, 6:29 AM
 */

#include <algorithm>

#include "SolutionObject.h"

SolutionObject::SolutionObject(map<uint16_t,mpz_class> invtbl, uint16_t*solVec,mpz_class sum) {
    NumMapTable=invtbl;
    solVector=solVec;
    result=sum;
    NMapIt b=NumMapTable.begin();
    NMapIt e=NumMapTable.end();
    for(b;b!=e;b++){
        if(solVector[(*b).first]){
            result-=(*b).second;
        }        
    }
    cout<<log2(result+1)<<endl;
}

SolutionObject::~SolutionObject() {
}

