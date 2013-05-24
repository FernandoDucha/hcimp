/* 
 * File:   NumberPartitionProblem_MPZ.h
 * Author: fernando
 *
 * Created on 29 de Agosto de 2011, 10:59
 */

#ifndef NumberPartitionProblem_MPZ_H
#define	NumberPartitionProblem_MPZ_H
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "BFS.h"
#include "BasicFunctions.h"
//#include "CompleteKarmarkarKarp.h"
#define SET_MAIOR(ConjuntoA, ConjuntoB)maior=partitionsSums[maior]<partitionsSums[conjuntoA]?conjuntoA:(partitionsSums[maior]<partitionsSums[conjuntoB]?conjuntoB:maior)
#define SET_MENOR(ConjuntoA, ConjuntoB)menor=partitionsSums[menor]>partitionsSums[conjuntoB]?conjuntoB:(partitionsSums[menor]>partitionsSums[conjuntoA]?conjuntoA:menor)
using namespace std;
struct graspPair_MPZ{
    graspPair_MPZ(mpz_class val,mpz_class n){
        id=val;
        number=n;
    }
    graspPair_MPZ(){
        id=-1;
        number=-1;
    }
    mpz_class id;
    mpz_class number;
};

class NumberPartitionProblem_MPZ {

public:
    
    NumberPartitionProblem_MPZ(char * problemFile);
    virtual ~NumberPartitionProblem_MPZ();
    void generateInitialSolEqualDivision();
    void generateInitialSolEqualDivisionComRealoc();
    void generateInitialSolGuloso();
    void generateInitialSolAleatorio();
   
    //métodos....
    void firstImproved();
    void descidaAleatoria();
    void descida();
    void multiStart(int iter);
    mpz_class getResultado() const;
    void GRASP(float alpha,int MaxIter);
    void IteratedLocalSearch(int MaxIter,float alpha,int MaxPerLvl);
    void graspConstruction(float alpha);
    mpz_class checkBestSolution();
    mpz_class checkSolution();
    mpz_class getBestResultado() const;
    ListStructure<number_element_mpz>* getNumberSource() const;
    int getNroParticoes() const;
    void cloneSolutionToBest(ListOfSums_mpz * los);
    void cloneSolutionToBest(los_bfs * los);
    int getQuantidade() const;
    mpz_class getMedia() const;
    
private:
    void getListFromBkp(bkp_bfs* b,ListStructure<number_element_mpz>*ret);
    void getListFromBkp(BookKeeping_mpz* b,ListStructure<number_element_mpz>*ret);
    void lerArquivo(char * problemFile);
    int calculateMaxIter();
    bool movimentoTrocaAleatorio();//troca dois elementos entre os dois conjuntos.
    bool avaliaTroca(mpz_class a,int conjuntoA, mpz_class b,int conjuntoB);//retorna true se melhora.
    bool movimentoRealocaAleatorio();
    bool movimentoRealocaMaiorDiferenca();// realoca um elemento a outro conjunto 
    mpz_class achaMelhorTroca(int & conjuntoA,number_element_mpz & numeroA, int & conjuntoB,number_element_mpz & numeroB);
    mpz_class achaMelhorRealocacao(int & conjuntoA,number_element_mpz & numeroA,int &conjuntoB);
    mpz_class primeiraMelhorTroca(int & conjuntoA,number_element_mpz & numeroA, int & conjuntoB,number_element_mpz & numeroB);
    mpz_class primeiraMelhorRealocacao(int & conjuntoA,number_element_mpz & numeroA,int &conjuntoB);
    mpz_class escolhePrimeiroMelhorVizinho();
    mpz_class escolheMelhorVizinho();
    int maiorParticao();
    int menorParticao();
    mpz_class calculaResultado();
    void clearPartitions();
    void cloneSolutionToBest();
    void cloneSolutionFromBest();
    void MakePertubation(int lvl);
    void constructPertubations();
    mpz_class soma;
    mpz_class media;
    int tempo;
    int quantidade;
    int nroParticoes;
    ListStructure<number_element_mpz> * numberSource;
    ListStructure<number_element_mpz> ** partitions;
    ListStructure<number_element_mpz> ** bestPartitions;
    mpz_class * partitionsSums;
    char * problemFile;
    mpz_class resultado;
    mpz_class bestResultado;
    Pertubation * pertubations;
    int maxPertubations;
};

#endif	/* NumberPartitionProblem_MPZ_H */

