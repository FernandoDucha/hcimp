/* 
 * File:   ComLookUp.h
 * Author: fernando
 *
 * Created on May 28, 2013, 2:11 AM
 */

#ifndef COMBLOOKUP_H
#define	COMBLOOKUP_H
#include <gsl/gsl_combination.h>
#include <vector>
using namespace std;
class CombLookUp {
    
public:
    CombLookUp();
    CombLookUp(int n);
    void createAllUntil(int k);
    void print();
    virtual ~CombLookUp();
private:
    vector<gsl_combination *> * combs;
    uint n;
    uint k;
};

#endif	/* COMBLOOKUP_H */

