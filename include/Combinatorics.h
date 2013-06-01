/* 
 * File:   Combinatorics.h
 * Author: fernando
 *
 * Created on 7 de Setembro de 2011, 17:05
 */

#ifndef COMBINATORICS_H
#define	COMBINATORICS_H
#include <iostream>
using namespace std;

class Combinatorics {
private:
    int arranges[200][20];
    int a[20];
    int n;
    int r;
    long numLeft;
    long totalCombs;
    long TotalArranges;
    long nFact;
    int jump;
public:
    Combinatorics(){
        //arranges=NULL;
        //a=NULL;
    }
    //------------
    // Constructor
    //------------
    Combinatorics(int n, int r) {
        this->n = n;
        this->r = r;
       // a = new int[n];
        nFact = getFactorial(n);
        long rFact = getFactorial(r);
        long nminusrFact = getFactorial(n - r);
        totalCombs = nFact / (rFact * nminusrFact);
        TotalArranges = nFact / nminusrFact;
//        arranges = new int*[TotalArranges];
//        for (int i = 0; i < TotalArranges; i++) {
//            arranges[i] = new int[r];
//        }
        reset();
        k = 0;
        for (int i = 0; i < n; i++) {
            Value[i] = i;
        }
        level=-1;
    }
    int k;
    //Arranjos
    int Value[100];
    int level;
    void getNextPermute();
    void permutations(int actual);
    void swap(int i,int j);
    void generateAllArranges();
    int Comb(int n, int k);
    int Arranjo(int n, int k);
    void printArranges(){
        for(int i=0;i<TotalArranges;i++){
            cout<<i<<" : ";
            for(int j=0;j<r;j++){
                cout<<arranges[i][j];
            }
            cout<<endl;
        }
    }
    int getArrangePosition(int i,int j){
        return arranges[i][j];
    }
    int getArrangePosition(int i, int j,int jump){
        return arranges[i*jump][j];
    }
    void printA(){
        for(int i=0;i<n;i++){
            cout<<a[i];
        }
        cout<<endl;
    }
    //------
    // Reset
    //------

    void reset() {
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }
        numLeft = totalCombs;
    }
    //------------------------------------------------
    // Return number of combinations not yet generated
    //------------------------------------------------

    long getNumLeft() {
        return numLeft;
    }
    //-----------------------------
    // Are there more combinations?
    //-----------------------------

    bool hasMore() {
        return numLeft == 0;
    }
    //------------------------------------
    // Return total number of combinations
    //------------------------------------

    long getTotal() {
        return totalCombs;
    }
    //------------------
    // Compute factorial
    //------------------

    long getFactorial(int n) {
        long fact = 1;
        for (int i = n; i > 1; i--) {
            fact *= i;
        }
        return fact;
    }
    //--------------------------------------------------------
    // Generate next combination (algorithm from Rosen p. 286)
    //--------------------------------------------------------

    int* getNext() {
        if (numLeft == totalCombs) {
            numLeft = numLeft - 1;
            return a;
        }
        int i = r - 1;
        while (a[i] == n - r + i) {
            i--;
        }
        a[i] = a[i] + 1;
        for (int j = i + 1; j < r; j++) {
            a[j] = a[i] + j - i;
        }
        numLeft = numLeft - 1;
        return a;
    }
    virtual ~Combinatorics();
    int** getArranges() const;
    int getK() const;
    long getNFact() const;
    long getTotalArranges() const;
    int getN() const;

    void setJump(int jump) {
        this->jump = jump;
    }

    int getJump() const {
        return jump;
    }
};

#endif	/* COMBINATORICS_H */

