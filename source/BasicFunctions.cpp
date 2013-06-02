/* 
 * File:   BasicFunctions.cpp
 * Author: fernando
 * 
 * Created on 13 de Maio de 2013, 16:22
 */

#include <gmp.h>

#include "BasicFunctions.h"
void constructK1ProblemStandard(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName){
    RandomNumberGenerator rng(frwb);
    mpz_class max;
    mpz_pow_ui(max.get_mpz_t(),mpz_class(2).get_mpz_t(),nBits);
    max--;
    double log1=(nPartitions-1)*(log(max)/log(nPartitions));
    int nElem=ceil(log1);
    ofstream filestr(fileName);
    filestr << 3600 << endl;
    filestr << "~" << endl;
    filestr << nElem<< endl;
    filestr << "~" << endl;
    filestr << nPartitions << endl;
    filestr << "~" << endl;
    for (int i = 0; i < nElem; i++) {
        filestr << rng.getNumberExactBits(nBits) << endl;
    }
    filestr.close();
}
void constructK1ProblemStandard_1(ulong nBits, int nPartitions, FileRawBuffer * frwb, char * fileName){
    RandomNumberGenerator rng(frwb);
    mpz_class max;
    mpz_pow_ui(max.get_mpz_t(),mpz_class(2).get_mpz_t(),nBits);
    max--;
    double log1=(nPartitions-1)*(log(max)/log(nPartitions));
    int nElem=ceil(log1);
    ofstream filestr(fileName);
    filestr << 3600 << endl;
    filestr << "~" << endl;
    filestr << nElem<< endl;
    filestr << "~" << endl;
    filestr << nPartitions << endl;
    filestr << "~" << endl;
    for (int i = 0; i < nElem; i++) {
        filestr << rng.getNumberWithMaxBits(nBits) << endl;
    }
    filestr.close();
}
void constructProblem(int nElements, int nBits, int nPartitions, int nTime, char * fileName) {
    srand(time(NULL));
    Cronometro c(Cronometro::NANO_S);
    c.start();
    gmp_randclass r4(gmp_randinit_default);
    r4.seed(c.elapsed());
    c.end();
    ofstream filestr(fileName);
    filestr << nTime << endl;
    filestr << "~" << endl;
    filestr << nElements << endl;
    filestr << "~" << endl;
    filestr << nPartitions << endl;
    filestr << "~" << endl;
    for (int i = 0; i < nElements; i++) {
        mpz_class num(r4.get_z_bits(nBits));
        filestr << num << endl;
    }
    filestr.close();
}

void constructProblemLPCplex(char * filein, char * outFile) {
    ofstream out(outFile);
    ifstream in(filein);
    char buff[2000];
    in.getline(buff,2000);
    in.getline(buff,2000);
    in.getline(buff,2000);
    int iSize=atoi(buff);
    in.getline(buff,2000);
    in.getline(buff,2000);
    int Npart=atoi(buff);
    in.getline(buff,2000);
    out << "MIN" << endl;
    int k = 0;
    mpz_class * a= new mpz_class[iSize];
    for(int i=0;i<iSize;i++){
        in.getline(buff,2000);
        a[i].set_str(buff,10);
    }
    for (int i = 1; i <= Npart; i++) {
        
        for (int j = 1; j <= iSize; j++) {
            string t=a[j-1].get_str(10);
            if (i != Npart) {
                
                if (j != iSize)
                    out << t << " " << "X" << i << j << " + ";
                else
                    out << t << " " << "X" << i << j;
            } else if (i == Npart) {
                out << " - " << t  << " X" << i << j;
            }
        }
        k++;
        out << endl;
        if (k == 2)
            break;
    }
    out << "ST" << endl;
    for (int k = 0; k < Npart - 1; k++) {
        for (int i = k + 1; i <= k + 2; i++) {
            for (int j = 1; j <= iSize; j++) {
                string t=a[j-1].get_str(10);
                if (i == k + 1) {
                    if (j != iSize)
                        out << t<< " " << "X" << i << j << " + ";
                    else
                        out << t<< " " << "X" << i << j;
                } else if (i == k + 2) {
                    out << " - " << t  << " X" << i << j;
                }
            }
        }
        out << " >= " << 0 << endl;
    }
    for (int k = 1; k <= iSize; k++) {
        for (int i = 1; i <= iSize; i++) {
            if (i != Npart) {
                out << "X" << i << k << " + ";
            } else {
                out << "X" << i << k;
            }
        }
        out << " = " << 1 << endl;
    }
    out << "BINARY" << endl;
    for (int k = 1; k <= iSize; k++) {
        for (int i = 1; i <= Npart; i++) {
            out << "X" << i << k << endl;
        }
    }
    out << "END" << endl;
    out.close();
    in.close();
    delete [] a;
}
double _log(double l){
    double ret=0;
    double lval=l-1;
    ret=lval;
    double i=0;
    ret=ret/((i+1)-i*lval+((i+1)*(i+1)*lval)/_logsupport(i+1,lval));
    i++;
    return ret;
}
double _logsupport(double i, double lval){
    if(i==1000){
        return 1;
    }
    return (i+1)-i*lval+((i+1)*(i+1)*lval)/_logsupport(i+1,lval);
}
double log2(mpz_class  l) {
    mpf_class r = l;
    mpf_class t,t1=l;
    int y=1;
    mpf_class resp;
    do{
        mpf_sqrt(t.get_mpf_t(),t1.get_mpf_t());
        y*=2;
        t1=t;
    } while (t>2);
    resp=y*log2(t.get_d());
    /*mpf_t a;
    mpf_init(a);
    mpf_class b(l);
    //cout<<b<<"--"<<l<<endl;
    mpf_div_2exp(a, b.get_mpf_t(), y);
    double temp = mpf_get_d(a);
    temp = pow(temp, 2);
    temp = log(temp) / log(2);
    temp = y + temp / 2;
    mpf_clear(a);
   // cout<<temp<<endl;*/
   return resp.get_d();    
}
double log(mpz_class  l) {
    mpf_class r = l;
    mpf_class t,t1=l;
    int y=1;
    mpf_class resp;
    do{
        mpf_sqrt(t.get_mpf_t(),t1.get_mpf_t());
        y*=2;
        t1=t;
    } while (t>2);
    resp=y*log(t.get_d());
    /*mpf_t a;
    mpf_init(a);
    mpf_class b(l);
    //cout<<b<<"--"<<l<<endl;
    mpf_div_2exp(a, b.get_mpf_t(), y);
    double temp = mpf_get_d(a);
    temp = pow(temp, 2);
    temp = log(temp) / log(2);
    temp = y + temp / 2;
    mpf_clear(a);
   // cout<<temp<<endl;*/
   return resp.get_d();    
}

//double log2(mpf_class  l) {
//    mpf_class r = l;
//    mpf_class t,t1=l;
//    int y=1;
//    mpf_class resp;
//    do{
//        mpf_sqrt(t.get_mpf_t(),t1.get_mpf_t());
//        y*=2;
//        t1=t;
//    } while (t>2);
//    resp=y*log2(t.get_d());
//    /*mpf_t a;
//    mpf_init(a);
//    mpf_class b(l);
//    //cout<<b<<"--"<<l<<endl;
//    mpf_div_2exp(a, b.get_mpf_t(), y);
//    double temp = mpf_get_d(a);
//    temp = pow(temp, 2);
//    temp = log(temp) / log(2);
//    temp = y + temp / 2;
//    mpf_clear(a);
//   // cout<<temp<<endl;*/
//   return resp.get_d();
//    
//}
mpf_class log2f(mpf_class l){
    mpf_class r = l;
    mpf_class t,t1=l;
    int y=1;
    mpf_class resp;
    do{
        mpf_sqrt(t.get_mpf_t(),t1.get_mpf_t());
        y*=2;
        t1=t;
    } while (t>2);
    resp=y*log2(t.get_d());
    /*mpf_t a;
    mpf_init(a);
    mpf_class b(l);
    //cout<<b<<"--"<<l<<endl;
    mpf_div_2exp(a, b.get_mpf_t(), y);
    double temp = mpf_get_d(a);
    temp = pow(temp, 2);
    temp = log(temp) / log(2);
    temp = y + temp / 2;
    mpf_clear(a);
   // cout<<temp<<endl;*/
   return resp;
}
long ZeckendorfLogarithm(mpz_class n,  mpz_class a) {
  /* Check that the input is valid. */
  /* Construct our "Fibonacci iterator" to keep track of where we are in the
   * Fibonacci sequence, including both the base and the logarithm.
   */
  //std::pair<T, T>             fibExponentIterator(T(1), a);
  //std::pair<Integer, Integer> fibBaseIterator(0u, 1u);
  mpz_class first(1);
  mpz_class second(a);
  mpz_class b_first(0);
  mpz_class b_second(1);
  
  /* Keep marching the iterator forward until we arrive at n. */
  while (second<n ) {
    /* Compute the next value in the generalized Fibonacci sequence as
     *
     *   (F(k), F(k+1)) -> (F(k+1), F(k+2))
     */
    
    mpz_class nextExp(first * second);
    cout<<nextExp<<endl;
    first = second;
    second = nextExp;

    mpz_class nextBase (b_first + b_second);
    cout<<nextBase<<endl;
    b_first = b_second;
    b_second = nextBase;
    
  }

  mpz_class result(0);

  /* Keep dividing out terms from the Zeckendorf representation of the number
   * until it reaches one.
   */
  while (b_first != 0) {
    /* If the first of the Fibonacci numbers is less than the current number,
     * divide it out and add the corresponding Fibonacci number to the
     * total.
     */
    if (b_first <= n) {
      n /= b_first;
      result += b_first;
    }

    /* Walk both iterators backward a step:
     *
     *   (F(k), F(k+1)) -> (F(k-1), F(k))
     */
    mpz_class prevExp (second / first);
    second = first;
    first  = prevExp;

    mpz_class prevBase (b_second - b_first);
    b_second = b_first;
    b_first = prevBase;
  }

  return result.get_si();
}

mpz_class generateRandomUZ(int nbits,gmp_randstate_t state){
    mpz_class num;
    mpz_urandomb(num.get_mpz_t(),state,nbits);
    num+=1;
    return num;
}
void readResults(char * resultFile){
    ifstream in(resultFile);
    ofstream matrix("matrix");
    while(!in.eof()){
        int n;
        int min=INT_MAX, sum=0,media=0;
        for(int i=0;i<10;i++){
            in>>n;
            char c;
            in>>c;
            int res;
            in>>res;
            if(res<min){
                min=res;
            }
            sum+=res;
        }
        media=sum/10;
        matrix<<min<<" "<<media<<endl;
    }
}