/* 
 * File:   enums.h
 * Author: fernando
 *
 * Created on 12 de Dezembro de 2011, 19:46
 */

#ifndef ENUMS_H
#define	ENUMS_H
#include <iostream>
using namespace std;
static inline ostream &
Indent(ostream & os, int len) {
    for (int i = 0; i < len; i++) {
        os << ' ';
    }
    return os;
}
inline static int
MIN(int a, int b) {
    return (a < b) ? a : b;
}

// Return the maximum of two numbers

inline static int
MAX(int a, int b) {
    return (a > b) ? a : b;
}

// Use mnemonic constants for valid balance-factor values



// Use mnemonic constants for indicating a change in height



// Return true if the tree is too heavy on the left side
enum dir_t {
    LEFT = 0, RIGHT = 1
};

enum cmp_t {
    MIN_CMP = -1, // less than
    EQ_CMP = 0, // equal to
    MAX_CMP = 1 // greater than
};

enum height_effect_t {
    HEIGHT_NOCHANGE = 0, HEIGHT_CHANGE = 1
};

enum balance_t {
    LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1
};
enum TraversalOrder {
    LTREE, KEY, RTREE
};
inline static int
LEFT_IMBALANCE(short bal) {
    return (bal < LEFT_HEAVY);
}

// Return true if the tree is too heavy on the right side

inline static int
RIGHT_IMBALANCE(short bal) {
    return (bal > RIGHT_HEAVY);
}



#endif	/* ENUMS_H */

