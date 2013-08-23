/* 
 * File:   SolutionObject.cpp
 * Author: fordem
 * 
 * Created on July 19, 2013, 6:29 AM
 */

#include "SolutionObject.h"

SolutionObject::SolutionObject(map<uint16_t, mpz_class> invtbl, uint8_t*solVec, mpz_class sum) {
    NumMapTable = invtbl;
    solVector = solVec;
    NumSum = sum;
    NMapIt b = NumMapTable.begin();
    NMapIt e = NumMapTable.end();
    PartSum = 0;
    for (b; b != e; b++) {
        if (solVector[(*b).first]) {
            PartSum += (*b).second;
        }
    }
}

mpz_class SolutionObject::testMoveInvert(uint16_t pos) {
    if (solVector[pos]) {
        PartSum -= NumMapTable[pos];
    } else {
        PartSum += NumMapTable[pos];
    }
    mpz_class ret = getResult();
    if (solVector[pos]) {
        PartSum += NumMapTable[pos];
    } else {
        PartSum -= NumMapTable[pos];
    }
    return ret;
}

mpz_class SolutionObject::testMoveSwap(swap p) {
    if (solVector[p.first]^solVector[p.second]) {
        if (solVector[p.first]) {
            PartSum -= NumMapTable[p.first];
            PartSum += NumMapTable[p.second];
        } else {
            PartSum += NumMapTable[p.first];
            PartSum -= NumMapTable[p.second];
        }
        mpz_class ret = getResult();
        if (solVector[p.first]) {
            PartSum += NumMapTable[p.first];
            PartSum -= NumMapTable[p.second];
        } else {
            PartSum -= NumMapTable[p.first];
            PartSum += NumMapTable[p.second];
        }
        return ret;
    }
    return -1;
}

mpz_class SolutionObject::makeMoveInvert(uint16_t pos) {
    if (solVector[pos]) {
        PartSum -= NumMapTable[pos];
    } else {
        PartSum += NumMapTable[pos];
    }
    solVector[pos] = ~solVector[pos];
    mpz_class ret = getResult();
    return ret;
}

mpz_class SolutionObject::makeMoveSwap(swap p) {
    if (solVector[p.first]^solVector[p.second]) {
        if (solVector[p.first]) {
            PartSum -= NumMapTable[p.first];
            PartSum += NumMapTable[p.second];
        } else {
            PartSum += NumMapTable[p.first];
            PartSum -= NumMapTable[p.second];
        }
        solVector[p.first] = ~solVector[p.first];
        solVector[p.second] = ~solVector[p.second];
        mpz_class ret = getResult();
        return ret;
    }
    return -1;
}

mpz_class SolutionObject::encode() {
    NMapIt b = NumMapTable.begin();
    NMapIt e = NumMapTable.end();
    mpz_class ret = 0;
    for (b; b != e; b++) {
        if (solVector[(*b).first]) {
            ret += mpz_class(1) << (*b).first;
        }
    }
    return ret;
}

SolutionObject::~SolutionObject() {
    delete [] solVector;
}
SolutionObject & SolutionObject::operator=(SolutionObject & rhs){
    int s = rhs.NumMapTable.size();
    if(!solVector){
        solVector= new uint8_t[s];
    }else{
        delete [] solVector;
        solVector = new uint8_t[s];
    }
    memcpy(solVector,rhs.solVector,s);
    NumMapTable = rhs.NumMapTable;
    PartSum=rhs.PartSum;
    NumSum=rhs.NumSum;
}