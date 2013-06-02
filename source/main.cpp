
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
   // FileRawBuffer * b = new FileRawBuffer("/media/DATA0/qrngdata");
   constructProblem(100,100,2,3600,"test.txt");    
    PPN_Heap a("test.txt");
    a.runLDS();
    //delete b;
    //    CombLookUp a(1000);
    //    a.createAllUntil(1000);
    //    a.print();
    //   }
    //    }
    //    if (!heap_checker.NoLeaks()) assert(NULL == "heap memory leak");
    //constructProblem(100,100,2,60,"test.txt");
    // constructProblemLPCplex("test.txt","cplex.txt");
    /* int p1=350377;
     mpz_pow_ui(prime3.get_mpz_t(),prime2.get_mpz_t(),p1);
     prime3-=1;
     cout<<prime3<<endl;
     cout<<"Grandeza: "<<log2(prime3)/log2(10)<<endl;
     //  cout<<prime2<<endl;
     prime1-=1;*/
    //    mpz_class a(3);
    //    Cronometro c(Cronometro::SEGUNDOS);
    //    c.start();
    //    mpz_class b;
    //    for(prime1=1;prime1<10000;prime1++){
    //        mpz_pow_ui(a.get_mpz_t(),a.get_mpz_t(),prime1.get_ui());
    //        a-=1;
    //        b=a;
    //        //cout<<prime1<<"-"<<a<<endl;
    //        if(a%2==1){
    //            cout<<a<<"-"<<c.elapsed()<<endl;
    ////            if(a!=0){
    ////                cout<<log2(a)<<endl;
    ////            }
    //        }
    //        a=3;
    //    }
    //    cout<<b<<endl;
    /*for(int i=0;i<argc;i++){
     
     *    cout<<i<<" : "<<argv[i]<<endl;
    }
    NumberPartitionProblem_MPZ* p = new NumberPartitionProblem_MPZ(argv[1]);
    CompleteKarmarkarKarp_MPZ ckk(p, p->getNroParticoes());
    if (strcmp(argv[2], "lds")==0){
        ckk.runLDS1(atoi(argv[3]), atoi(argv[4]));
        cout << log2(ckk.GetMin() + 1) << " -- " << log2(p->checkBestSolution() + 1) << endl;
    }else if(strcmp(argv[2],"bfs")==0){
        ckk.runBFS1(atoi(argv[3]));
        cout << log2(ckk.GetMin() + 1) << " -- " << log2(p->checkBestSolution() + 1) << endl;
    }else if(strcmp(argv[2],"dfs")==0){
        ckk.runDFS1();
        cout << log2(ckk.GetMin() + 1) << " -- " << log2(p->checkBestSolution() + 1) << endl;
    }*/

    return 0;
}

