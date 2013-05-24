/* 
 * File:   cplexMip.h
 * Author: fernando
 *
 * Created on 1 de Outubro de 2011, 14:15
 */

#ifndef CPLEXMIP_H
#define	CPLEXMIP_H
#include "ListStructure.h"
#include "BasicTypes.h"
#include <ilcplex/ilocplex.h>
ILOSTLBEGIN
int solveCplex (char * str,ListStructure<number_element> * l);

#endif	/* CPLEXMIP_H */

