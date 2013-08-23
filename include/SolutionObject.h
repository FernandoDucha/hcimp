/* 
 * File:   SolutionObject.h
 * Author: fordem
 *
 * Created on July 19, 2013, 6:29 AM
 */

#ifndef SOLUTIONOBJECT_H
#define	SOLUTIONOBJECT_H
#include <map>
#include <iostream>
#include <gmpxx.h>
#include "BasicFunctions.h"

using namespace std;
class SolutionObject {
private:
    map<uint16_t, mpz_class> NumMapTable;
    uint8_t * solVector;
    mpz_class NumSum, PartSum;

    typedef map<uint16_t, mpz_class>::iterator NMapIt;
public:
    typedef pair<uint16_t,uint16_t> swap;
    SolutionObject(){
        solVector=NULL;
    }
    SolutionObject(map<uint16_t, mpz_class> invtbl, uint8_t*solVec, mpz_class sum);
    mpz_class getResult();
    virtual ~SolutionObject();
    mpz_class testMoveInvert(uint16_t pos);
    mpz_class testMoveSwap(swap p);
    mpz_class makeMoveInvert(uint16_t pos);
    mpz_class makeMoveSwap(swap p);
    mpz_class encode();
    SolutionObject & operator=(SolutionObject & rhs);
};

inline mpz_class SolutionObject::getResult() {
    mpz_class ret = NumSum - 2 * PartSum;
    ret = (ret < 0) ? -ret : ret;
    return ret;
}
#endif	/* SOLUTIONOBJECT_H */

