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
#include <iostream>
using namespace std;
class CombLookUp {
    
public:
    CombLookUp();
    CombLookUp(int n);
    void createAllUntil(int k);
    bool  getNext(gsl_combination* ret,int k);
    void print();
    virtual ~CombLookUp();
private:
    vector<gsl_combination *> * combs;
    uint n;
    uint k;
    bool last;
};

#endif	/* COMBLOOKUP_H */

