#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Avl.o \
	${OBJECTDIR}/BFS.o \
	${OBJECTDIR}/BasicFunctions.o \
	${OBJECTDIR}/BasicTypes.o \
	${OBJECTDIR}/BasicTypes_heap.o \
	${OBJECTDIR}/Combinatorics.o \
	${OBJECTDIR}/CompleteKarmarkarKarp.o \
	${OBJECTDIR}/CompleteKarmarkarKarp_MPZ.o \
	${OBJECTDIR}/Cronometro.o \
	${OBJECTDIR}/Hash.o \
	${OBJECTDIR}/HashExtended.o \
	${OBJECTDIR}/HeapStrctPtr.o \
	${OBJECTDIR}/HeapStructure.o \
	${OBJECTDIR}/ListStructure.o \
	${OBJECTDIR}/ListStructurePtr.o \
	${OBJECTDIR}/Mpz_Heap_Node_Template.o \
	${OBJECTDIR}/NumberPartitionProblem.o \
	${OBJECTDIR}/NumberPartitionProblem_MPZ.o \
	${OBJECTDIR}/PPN_Heap.o \
	${OBJECTDIR}/Semaphore.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fexceptions -DIL_STD -std=c++11
CXXFLAGS=-fexceptions -DIL_STD -std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/lib/x86-64_sles10_4.1/static_pic -L/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/lib/x86-64_sles10_4.1/static_pic -lm -pthread -lrt -lmpfr -lgsl -lgmp -lgmpxx -ltcmalloc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Avl.o: Avl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Avl.o Avl.cpp

${OBJECTDIR}/BFS.o: BFS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BFS.o BFS.cpp

${OBJECTDIR}/BasicFunctions.o: BasicFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BasicFunctions.o BasicFunctions.cpp

${OBJECTDIR}/BasicTypes.o: BasicTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BasicTypes.o BasicTypes.cpp

${OBJECTDIR}/BasicTypes_heap.o: BasicTypes_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BasicTypes_heap.o BasicTypes_heap.cpp

${OBJECTDIR}/Combinatorics.o: Combinatorics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Combinatorics.o Combinatorics.cpp

${OBJECTDIR}/CompleteKarmarkarKarp.o: CompleteKarmarkarKarp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CompleteKarmarkarKarp.o CompleteKarmarkarKarp.cpp

${OBJECTDIR}/CompleteKarmarkarKarp_MPZ.o: CompleteKarmarkarKarp_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CompleteKarmarkarKarp_MPZ.o CompleteKarmarkarKarp_MPZ.cpp

${OBJECTDIR}/Cronometro.o: Cronometro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Cronometro.o Cronometro.cpp

${OBJECTDIR}/Hash.o: Hash.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Hash.o Hash.cpp

${OBJECTDIR}/HashExtended.o: HashExtended.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HashExtended.o HashExtended.cpp

${OBJECTDIR}/HeapStrctPtr.o: HeapStrctPtr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HeapStrctPtr.o HeapStrctPtr.cpp

${OBJECTDIR}/HeapStructure.o: HeapStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HeapStructure.o HeapStructure.cpp

${OBJECTDIR}/ListStructure.o: ListStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ListStructure.o ListStructure.cpp

${OBJECTDIR}/ListStructurePtr.o: ListStructurePtr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ListStructurePtr.o ListStructurePtr.cpp

${OBJECTDIR}/Mpz_Heap_Node_Template.o: Mpz_Heap_Node_Template.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mpz_Heap_Node_Template.o Mpz_Heap_Node_Template.cpp

${OBJECTDIR}/NumberPartitionProblem.o: NumberPartitionProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NumberPartitionProblem.o NumberPartitionProblem.cpp

${OBJECTDIR}/NumberPartitionProblem_MPZ.o: NumberPartitionProblem_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/NumberPartitionProblem_MPZ.o NumberPartitionProblem_MPZ.cpp

${OBJECTDIR}/PPN_Heap.o: PPN_Heap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/PPN_Heap.o PPN_Heap.cpp

${OBJECTDIR}/Semaphore.o: Semaphore.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Semaphore.o Semaphore.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilconcert -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/opl/include/ilcplex -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/include -I/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/include -fexceptions -DIL_STD -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
