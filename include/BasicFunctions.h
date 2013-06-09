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
#include <fstream>
#include "Cronometro.h"
#include <limits.h>
#include "RandomNumberGenerator.h"
#include "FileRawBuffer.h"
#include <fstream>
void readResults(const char * resultFile);
bool checkResultExist(const char * file);
double log2(mpz_class  l);
double log(mpz_class l);
//double log2(mpf_class  l);
mpf_class log2f(mpf_class l);

double _logsupport(double i, double lval);
double _log(double l);
double _log2(double l);
long ZeckendorfLogarithm(mpz_class n, mpz_class a);
mpz_class generateRandomUZ(int nbits,gmp_randstate_t state);
void constructK1ProblemStandard(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName);
void constructK1ProblemStandard_1(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName);

void constructProblem(int nElements,int nBits,int nPartitions,int nTime,char * fileName);
void constructProblemLPCplex(char * filein,char * outFile);
//void constructProblem(int nElements,int nDigits,int nPartitions,int nTime,char * fileName,ListStructurePtr<number_element>& list);
//void constructProblemLPCplex(NumberPartitionProblem & p,char * outFile);
#endif	/* BASICFUNCTIONS_H */

