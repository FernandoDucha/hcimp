// -------------------------------------------------------------- -*- C++ -*-
// File: ilomipex2.cpp 
// Version 12.3  
// --------------------------------------------------------------------------
// Licensed Materials - Property of IBM
// 5725-A06 5725-A29 5724-Y48 5724-Y49 5724-Y54 5724-Y55
// Copyright IBM Corporation 2000, 2011. All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with
// IBM Corp.
// --------------------------------------------------------------------------
//
// ilomipex2.cpp - Reading in and optimizing a problem
//
// To run this example, command line arguments are required.
// i.e.,   ilomipex2   filename
//
// Example:
//     ilomipex2  mexample.mps
//
#include "cplexMip.h"
#include "BasicTypes.h"
ILOBRANCHCALLBACK1(MyBranch, IloNumVarArray, vars) {
   if ( getBranchType() != BranchOnVariable )
      return;

   // Branch on var with largest objective coefficient
   // among those with largest infeasibility

   IloNumArray x;
   IloNumArray obj;
   IntegerFeasibilityArray feas;

   try {
      x    = IloNumArray(getEnv());
      obj  = IloNumArray(getEnv());
      feas = IntegerFeasibilityArray(getEnv());
      getValues(x, vars);
      getObjCoefs(obj, vars);
      getFeasibilities(feas, vars);

      IloInt bestj  = -1;
      IloNum maxinf = 0.0;
      IloNum maxobj = 0.0;
      IloInt cols = vars.getSize();
      for (IloInt j = 0; j < cols; j++) {
         if ( feas[j] == Infeasible ) {
            IloNum xj_inf = x[j] - IloFloor (x[j]);
            if ( xj_inf > 0.5 )
               xj_inf = 1.0 - xj_inf;
            if ( xj_inf >= maxinf                              &&
                 (xj_inf > maxinf || IloAbs (obj[j]) >= maxobj)  ) {
               bestj  = j;
               maxinf = xj_inf;
               maxobj = IloAbs (obj[j]);
            }
         }
      }

      if ( bestj >= 0 ) {
         makeBranch(vars[bestj], x[bestj], IloCplex::BranchUp,   getObjValue());
         makeBranch(vars[bestj], x[bestj], IloCplex::BranchDown, getObjValue());
      }
   }
   catch (...) {
      x.end();
      obj.end();
      feas.end();
      throw;
   }
   x.end();
   obj.end();
   feas.end();
}

ILONODECALLBACK0(MySelect) {
   IloInt remainingNodes = getNremainingNodes();
   IloInt bestnode = -1;
   IloInt maxdepth = -1;
   IloNum maxiisum = 0.0;
   for (IloInt i = 0; i < remainingNodes; i++) {
      IloInt depth = getDepth(i);
      IloNum iisum = getInfeasibilitySum(i);
      if ( (depth >= maxdepth)                   &&
           (depth > maxdepth || iisum > maxiisum)  ) {
         bestnode = i;
         maxdepth = depth;
         maxiisum = iisum;
      }
   }
   if ( bestnode >= 0 ) selectNode(bestnode);
}


int solveCplex (char * str,ListStructure<number_element> * l)
{
   
   IloEnv env;
   try {
      IloModel model(env);
      IloCplex cplex(env);
      IloObjective   obj;
      IloNumVarArray var(env);
      IloRangeArray  rng(env);
      IloSOS1Array   sos1(env);
      IloSOS2Array   sos2(env);
      IloRangeArray  lazy(env);
      IloRangeArray  cuts(env);

      cplex.importModel(model, str, obj, var, rng, sos1, sos2, lazy, cuts);
      cplex.use(MyBranch(env, var));
      cplex.use(MySelect(env));

      cplex.setParam(IloCplex::MIPSearch, IloCplex::Traditional);

      cplex.extract(model);
      cplex.setParam(IloCplex::EpInt,0.000000000001);
      cplex.setParam(IloCplex::TiLim,120*60);
      if ( lazy.getSize() > 0 )  cplex.addLazyConstraints (lazy);
      if ( cuts.getSize() > 0 )  cplex.addUserCuts (cuts);
      
      cplex.solve();
      
      env.out() << "Solution status = " << cplex.getStatus() << endl;
      env.out() << "Solution value  = " << cplex.getObjValue() << endl;

      IloNumArray vals(env);
      cplex.getValues(vals, var);
     //IloObjective obj=cplex.getObjective();
      env.out() << "Values        = " << vals << endl;
      long long sum=0;
      int a=vals.getSize();
      for(int i=0;i<a;i++){
          int b=l->getSize();
          number_element  n=l->retrieve_K_esimo(i%b)->element;
          if(i<b){
              if(vals[i]>0.9){
                  sum+=n.id;
              }
          }else{
              if(vals[i]>0.9){
                  sum-=n.id;
              }
          }
          
          
      }
   }
   catch (IloException& e) {
      cerr << "Concert exception caught: " << e << endl;
   }
   catch (...) {
      cerr << "Unknown exception caught" << endl;
   }

   env.end();
}  // END main



