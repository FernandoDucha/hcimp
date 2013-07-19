/* 
 * File:   SolutionObject.h
 * Author: fordem
 *
 * Created on July 19, 2013, 6:29 AM
 */

#ifndef SOLUTIONOBJECT_H
#define	SOLUTIONOBJECT_H
#include <map>
#include "GeneralUsage.h"
using namespace std;
class SolutionObject {
public:
    SolutionObject(map<uint16_t,mpz_class> invtbl, uint16_t*solVec,mpz_class sum);
    virtual ~SolutionObject();
private:
    map<uint16_t,mpz_class> NumMapTable;
    uint16_t * solVector;
    mpz_class result;
    typedef map<uint16_t,mpz_class>::iterator NMapIt;
};

#endif	/* SOLUTIONOBJECT_H */

