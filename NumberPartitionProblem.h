/* 
 * File:   NumberPartitionProblem.h
 * Author: fernando
 *
 * Created on 29 de Agosto de 2011, 10:59
 */

#ifndef NUMBERPARTITIONPROBLEM_H
#define	NUMBERPARTITIONPROBLEM_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "BasicTypes.h"
//#include "CompleteKarmarkarKarp.h"
#define SET_MAIOR(ConjuntoA, ConjuntoB)maior=partitionsSums[maior]<partitionsSums[conjuntoA]?conjuntoA:(partitionsSums[maior]<partitionsSums[conjuntoB]?conjuntoB:maior)
#define SET_MENOR(ConjuntoA, ConjuntoB)menor=partitionsSums[menor]>partitionsSums[conjuntoB]?conjuntoB:(partitionsSums[menor]>partitionsSums[conjuntoA]?conjuntoA:menor)
using namespace std;
struct graspPair{
    graspPair(long long val,long long n){
        id=val;
        number=n;
    }
    graspPair(){
        id=-1;
        number=-1;
    }
    long long id;
    long long number;
};

class NumberPartitionProblem {

public:
    
    NumberPartitionProblem(char * problemFile);
    virtual ~NumberPartitionProblem();
    void generateInitialSolEqualDivision();
    void generateInitialSolEqualDivisionComRealoc();
    void generateInitialSolGuloso();
    void generateInitialSolAleatorio();
   
    //métodos....
    void firstImproved();
    void descidaAleatoria();
    void descida();
    void multiStart(int iter);
    long long getResultado() const;
    void GRASP(float alpha,int MaxIter);
    void IteratedLocalSearch(int MaxIter,float alpha,int MaxPerLvl);
    void graspConstruction(float alpha);
    long long checkBestSolution();
    long long checkSolution();
    long long getBestResultado() const;
    ListStructure<number_element>* getNumberSource() const;
    int getNroParticoes() const;
    void cloneSolutionToBest(list_element<list_element<number_element*>*>*los);
    
private:
    void lerArquivo(char * problemFile);
    int calculateMaxIter();
    bool movimentoTrocaAleatorio();//troca dois elementos entre os dois conjuntos.
    bool avaliaTroca(int a,int conjuntoA, int b,int conjuntoB);//retorna true se melhora.
    bool movimentoRealocaAleatorio();
    bool movimentoRealocaMaiorDiferenca();// realoca um elemento a outro conjunto 
    long long achaMelhorTroca(int & conjuntoA,number_element & numeroA, int & conjuntoB,number_element & numeroB);
    long long achaMelhorRealocacao(int & conjuntoA,number_element & numeroA,int &conjuntoB);
    long long primeiraMelhorTroca(int & conjuntoA,number_element & numeroA, int & conjuntoB,number_element & numeroB);
    long long primeiraMelhorRealocacao(int & conjuntoA,number_element & numeroA,int &conjuntoB);
    long long escolhePrimeiroMelhorVizinho();
    long long escolheMelhorVizinho();
    int maiorParticao();
    int menorParticao();
    long long calculaResultado();
    void clearPartitions();
    void cloneSolutionToBest();
    void cloneSolutionFromBest();
    void MakePertubation(int lvl);
    void constructPertubations();
    long long soma;
    long long media;
    int tempo;
    int quantidade;
    int nroParticoes;
    ListStructure<number_element> * numberSource;
    ListStructure<number_element> ** partitions;
    ListStructure<number_element> ** bestPartitions;
    long long * partitionsSums;
    char * problemFile;
    long long resultado;
    long long bestResultado;
    Pertubation * pertubations;
    int maxPertubations;
};


#endif	/* NUMBERPARTITIONPROBLEM_H */

