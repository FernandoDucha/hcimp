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

    typedef pair<uint16_t, uint16_t> swap;
    typedef map<uint16_t, mpz_class>::iterator NMapIt;
public:
    SolutionObject(map<uint16_t, mpz_class> invtbl, uint8_t*solVec, mpz_class sum);
    double getResult();
    virtual ~SolutionObject();
    double testMoveInvert(uint16_t pos);
    double testMoveSwap(swap p);
    double makeMoveInvert(uint16_t pos);
    double makeMoveSwap(swap p);
    mpz_class encode();
};

inline double SolutionObject::getResult() {
    mpz_class ret = NumSum - 2 * PartSum;
    ret = (ret < 0) ? -ret : ret;
    return log2(ret);
}
#endif	/* SOLUTIONOBJECT_H */

