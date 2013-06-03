
/* 
 * File:   main.cpp
 * Author: fernando
 *
 * Created on 29 de Agosto de 2011, 10:57
 */
// 
#include <iostream>
//#include "Cronometro.h"
//#include "NumberPartitionProblem.h"
//#include "CompleteKarmarkarKarp.h"
//#include "NumberPartitionProblem_MPZ.h"
//#include "CompleteKarmarkarKarp_MPZ.h"
//#include "ListStructure.h"
//#include <limits.h>
#include <gmpxx.h>
#include "BasicTypes_heap.h"
#include "BasicTypes.h"
#include "BasicFunctions.h"
#include "PPN_Heap.h"
#include "HeapStructure.h"
#include <assert.h>
#include "CombLookUp.h"
//#include <google/heap-checker.h>
//#include <vector>
//#include "BasicTypes.h"
//#include <gsl/gsl_math.h>
//#include <limits>
//#define PI 3.14159
//#include "cplexMip.h"
using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    //    number_element_mpz *a,*b;
    //    a = new number_element_mpz(mpz_class(2));
    //    b = new number_element_mpz(mpz_class(3));
    //    mpz_class prime1(0);
    //    mpz_class prime2(2);
    //    mpz_class prime3(0),prime4(0);
    //    cout<<(*a+*b).id<<endl;
    //     HeapLeakChecker heap_checker("test_foo");{
//    FileRawBuffer * b = new FileRawBuffer("/media/DATA0/qrngdata");
//    for (int i = 0; i < 10; i++) {
//        for (int j = 1; j <= 100; j++) {
//            char buffer[30];
//            sprintf(buffer,"instances/inst-%04d-%03d",(i+1)*100,j);
//            constructK1ProblemStandard_1((i+1)*100, 2, b, buffer);
//        }
//    }
    //constructProblem(100,100,2,3600,"test.txt");
    if(argc==4){
        if (strcmp(argv[1], "lds")==0){
            int type = atoi(argv[2]);
            int wich = atoi(argv[3]);
            char buffer[30];
            sprintf(buffer,"inst-%04d-%03d",type,wich);
            PPN_Heap  ppn(buffer);
            ppn.runLDS();
        }else if(strcmp(argv[1],"bfs")==0){
            int type = atoi(argv[2]);
            int wich = atoi(argv[3]);
            char buffer[30];
            sprintf(buffer,"inst-%04d-%03d",type,wich);
            PPN_Heap  ppn(buffer);
            ppn.runBFS();
        }else if(strcmp(argv[1],"dfs")==0){
            int type = atoi(argv[2]);
            int wich = atoi(argv[3]);
            char buffer[30];
            sprintf(buffer,"inst-%04d-%03d",type,wich);
            PPN_Heap  ppn(buffer);
            ppn.runDFS();
        }
    }

    return 0;
}

