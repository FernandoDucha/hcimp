/* 
 * File:   Combinatorics.cpp
 * Author: fernando
 * 
 * Created on 7 de Setembro de 2011, 17:05
 */

#include "Combinatorics.h"

void Combinatorics::permutations(int actual) {
    level = level + 1;
    Value[actual] = level; // = is assignment
    if (level == r) { // == is comparison
        //AddItem();     // to the list box
        for (int i = 0; i < r; i++) {
            arranges[k][i] = Value[i];
        }
        k++;
    } else
        for (int i = 0; i < r; i++)
            if (Value[i] == 0) {
                    permutations(i);
            }

    level = level - 1;
    Value[actual] = 0;
}
void Combinatorics::getNextPermute()
  {
    int i = n - 1;
    while (a[i-1] >= a[i]) 
      i = i-1;

    int j = n;
    while (a[j-1] <= a[i-1]) 
      j = j-1;
    
    swap(i-1, j-1);    // swap values at positions (i-1) and (j-1)

    i++; j = n;
    while (i < j)
    {
      swap(i-1, j-1);
      i++;
      j--;
    }
  }
 void Combinatorics::swap(int i,int j){
     int temp=a[i];
     a[i]=a[j];
     a[j]=temp;
 }
 void Combinatorics::generateAllArranges(){
     if(nFact==TotalArranges){
         
         for(int i=0;i<TotalArranges;i++){
             for(int j=0;j<r;j++){
                 arranges[i][j]=a[j];
             }
             getNextPermute();
         }
     }else{
         int jump=nFact/TotalArranges;
         //cout<<jump<<endl;
         for(int i=0;i<TotalArranges;i++){
             //printA();
             for(int j=0;j<r;j++){
                 arranges[i][j]=a[j];
             }
             for(int k=0;k<jump;k++){
                 getNextPermute();
                 //printA();
             }
         }
     }
     
 }
 Combinatorics::~Combinatorics(){
//     if(a!=NULL)
//        delete [] a;
    /* if(arranges!=NULL){
         for(int i=0;i<TotalArranges;i++){
             delete [] arranges[i];
         }
         delete [] arranges;
     }*/
 }

 int** Combinatorics::getArranges() const {
     return (int**)arranges;
 }

 int Combinatorics::getK() const {
     return k;
 }

 long Combinatorics::getNFact() const {
     return nFact;
 }

 long Combinatorics::getTotalArranges() const {
     return TotalArranges;
 }

 int Combinatorics::getN() const {
     return n;
 }
 int  Combinatorics::Comb(int n, int k){
     int nfact=getFactorial(n);
     int kfact=getFactorial(k);
     int n_kfact=getFactorial(n-k);
     return nfact/(kfact*n_kfact);
 }
 int Combinatorics::Arranjo(int n, int k){
     int nfact=getFactorial(n);
     int n_kfact=getFactorial(n-k);
     return nfact/n_kfact;
 }