/* 
 * File:   BasicFunctions.h
 * Author: fernando
 *
 * Created on 13 de Maio de 2013, 16:22
 */
#ifndef BASICFUNCTIONS_H
#define	BASICFUNCTIONS_H
#include <gmpxx.h>
#include <math.h>
#include "Cronometro.h"
#include <limits.h>
#include "RandomNumberGenerator.h"
#include "FileRawBuffer.h"
#include <fstream>
#include <iostream>
using namespace std;
#define ONE 0xFF
#define ZERO 0x00

void readResults(const char * resultFile);
bool checkResultExist(const char * file);
double log2(mpz_class l);
double log(mpz_class l);
//double log2(mpf_class  l);
mpf_class log2f(mpf_class l);

double _logsupport(double i, double lval);
double _log(double l);
double _log2(double l);
long ZeckendorfLogarithm(mpz_class n, mpz_class a);
mpz_class generateRandomUZ(int nbits, gmp_randstate_t state);
void constructK1ProblemStandard(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName);
void constructK1ProblemStandard_1(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName);

template <class item >void quicksort(item * list, int l, int r) {
    if (r <= l) 
        return;
    int i = partition(list, l, r);
    quicksort(list, l, i - 1);
    quicksort(list, i + 1, r);
}

template <class item >int partition(item * list, int l, int r) {
    int i = l - 1;
    int j = r;
    item v = list[r];
    for (;;) {
        while (list[++i] < v);
        while (v < list[--j]) {
            if (j == l) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        item temp = list[i];
        list[i] = list[j];
        list[j] = temp;
        //mpz_swap(list[i].get_mpz_t(), list[j].get_mpz_t());
    }
    item temp = list[i];
    list[i] = list[r];
    list[r] = temp;
    //mpz_swap(list[i].get_mpz_t(), list[r].get_mpz_t());
    return i;
}
void constructProblem(int nElements, int nBits, int nPartitions, int nTime, char * fileName);
void constructProblemLPCplex(char * filein, char * outFile);
//void constructProblem(int nElements,int nDigits,int nPartitions,int nTime,char * fileName,ListStructurePtr<number_element>& list);
//void constructProblemLPCplex(NumberPartitionProblem & p,char * outFile);
#endif	/* BASICFUNCTIONS_H */

