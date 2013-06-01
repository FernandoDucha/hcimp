#include "BasicTypes.h"
//int BookKeeping_mpz::count1=0;

number_element_mpz & operator-(number_element_mpz & A,number_element_mpz & B) {
     number_element_mpz * a= new number_element_mpz(A.id - B.id);
     return *a;
}

number_element_mpz & operator+(number_element_mpz & A,number_element_mpz & B) {

    number_element_mpz * a = new number_element_mpz(A.id + B.id);
    return  *a;
}
