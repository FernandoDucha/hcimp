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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1469337217/Avl.o \
	${OBJECTDIR}/_ext/1469337217/BFS.o \
	${OBJECTDIR}/_ext/1469337217/BasicFunctions.o \
	${OBJECTDIR}/_ext/1469337217/BasicTypes.o \
	${OBJECTDIR}/_ext/1469337217/BasicTypes_heap.o \
	${OBJECTDIR}/_ext/1469337217/CombLookUp.o \
	${OBJECTDIR}/_ext/1469337217/Combinatorics.o \
	${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp.o \
	${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp_MPZ.o \
	${OBJECTDIR}/_ext/1469337217/Cronometro.o \
	${OBJECTDIR}/_ext/1469337217/Hash.o \
	${OBJECTDIR}/_ext/1469337217/HashExtended.o \
	${OBJECTDIR}/_ext/1469337217/HeapStrctPtr.o \
	${OBJECTDIR}/_ext/1469337217/HeapStrctPtrMin.o \
	${OBJECTDIR}/_ext/1469337217/HeapStructure.o \
	${OBJECTDIR}/_ext/1469337217/ListStructure.o \
	${OBJECTDIR}/_ext/1469337217/ListStructurePtr.o \
	${OBJECTDIR}/_ext/1469337217/Mpz_Heap_Node_Template.o \
	${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem.o \
	${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem_MPZ.o \
	${OBJECTDIR}/_ext/1469337217/PPN_Heap.o \
	${OBJECTDIR}/_ext/1469337217/Semaphore.o \
	${OBJECTDIR}/_ext/1469337217/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fPIC -fexceptions -DNDEBUG -DIL_STD
CXXFLAGS=-m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/opt/ibm/ILOG/CPLEX_Studio_Academic123/cplex/lib/x86-64_sles10_4.1/static_pic -L/opt/ibm/ILOG/CPLEX_Studio_Academic123/concert/lib/x86-64_sles10_4.1/static_pic -lm -pthread -lrt -lgmp -lgmpxx `pkg-config --libs gsl`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1469337217/Avl.o: /home/fernando/Dropbox/HC/HCImp/source/Avl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Avl.o /home/fernando/Dropbox/HC/HCImp/source/Avl.cpp

${OBJECTDIR}/_ext/1469337217/BFS.o: /home/fernando/Dropbox/HC/HCImp/source/BFS.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/BFS.o /home/fernando/Dropbox/HC/HCImp/source/BFS.cpp

${OBJECTDIR}/_ext/1469337217/BasicFunctions.o: /home/fernando/Dropbox/HC/HCImp/source/BasicFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/BasicFunctions.o /home/fernando/Dropbox/HC/HCImp/source/BasicFunctions.cpp

${OBJECTDIR}/_ext/1469337217/BasicTypes.o: /home/fernando/Dropbox/HC/HCImp/source/BasicTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/BasicTypes.o /home/fernando/Dropbox/HC/HCImp/source/BasicTypes.cpp

${OBJECTDIR}/_ext/1469337217/BasicTypes_heap.o: /home/fernando/Dropbox/HC/HCImp/source/BasicTypes_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/BasicTypes_heap.o /home/fernando/Dropbox/HC/HCImp/source/BasicTypes_heap.cpp

${OBJECTDIR}/_ext/1469337217/CombLookUp.o: /home/fernando/Dropbox/HC/HCImp/source/CombLookUp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/CombLookUp.o /home/fernando/Dropbox/HC/HCImp/source/CombLookUp.cpp

${OBJECTDIR}/_ext/1469337217/Combinatorics.o: /home/fernando/Dropbox/HC/HCImp/source/Combinatorics.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Combinatorics.o /home/fernando/Dropbox/HC/HCImp/source/Combinatorics.cpp

${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp.o: /home/fernando/Dropbox/HC/HCImp/source/CompleteKarmarkarKarp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp.o /home/fernando/Dropbox/HC/HCImp/source/CompleteKarmarkarKarp.cpp

${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp_MPZ.o: /home/fernando/Dropbox/HC/HCImp/source/CompleteKarmarkarKarp_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/CompleteKarmarkarKarp_MPZ.o /home/fernando/Dropbox/HC/HCImp/source/CompleteKarmarkarKarp_MPZ.cpp

${OBJECTDIR}/_ext/1469337217/Cronometro.o: /home/fernando/Dropbox/HC/HCImp/source/Cronometro.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Cronometro.o /home/fernando/Dropbox/HC/HCImp/source/Cronometro.cpp

${OBJECTDIR}/_ext/1469337217/Hash.o: /home/fernando/Dropbox/HC/HCImp/source/Hash.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Hash.o /home/fernando/Dropbox/HC/HCImp/source/Hash.cpp

${OBJECTDIR}/_ext/1469337217/HashExtended.o: /home/fernando/Dropbox/HC/HCImp/source/HashExtended.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/HashExtended.o /home/fernando/Dropbox/HC/HCImp/source/HashExtended.cpp

${OBJECTDIR}/_ext/1469337217/HeapStrctPtr.o: /home/fernando/Dropbox/HC/HCImp/source/HeapStrctPtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/HeapStrctPtr.o /home/fernando/Dropbox/HC/HCImp/source/HeapStrctPtr.cpp

${OBJECTDIR}/_ext/1469337217/HeapStrctPtrMin.o: /home/fernando/Dropbox/HC/HCImp/source/HeapStrctPtrMin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/HeapStrctPtrMin.o /home/fernando/Dropbox/HC/HCImp/source/HeapStrctPtrMin.cpp

${OBJECTDIR}/_ext/1469337217/HeapStructure.o: /home/fernando/Dropbox/HC/HCImp/source/HeapStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/HeapStructure.o /home/fernando/Dropbox/HC/HCImp/source/HeapStructure.cpp

${OBJECTDIR}/_ext/1469337217/ListStructure.o: /home/fernando/Dropbox/HC/HCImp/source/ListStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/ListStructure.o /home/fernando/Dropbox/HC/HCImp/source/ListStructure.cpp

${OBJECTDIR}/_ext/1469337217/ListStructurePtr.o: /home/fernando/Dropbox/HC/HCImp/source/ListStructurePtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/ListStructurePtr.o /home/fernando/Dropbox/HC/HCImp/source/ListStructurePtr.cpp

${OBJECTDIR}/_ext/1469337217/Mpz_Heap_Node_Template.o: /home/fernando/Dropbox/HC/HCImp/source/Mpz_Heap_Node_Template.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Mpz_Heap_Node_Template.o /home/fernando/Dropbox/HC/HCImp/source/Mpz_Heap_Node_Template.cpp

${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem.o: /home/fernando/Dropbox/HC/HCImp/source/NumberPartitionProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem.o /home/fernando/Dropbox/HC/HCImp/source/NumberPartitionProblem.cpp

${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem_MPZ.o: /home/fernando/Dropbox/HC/HCImp/source/NumberPartitionProblem_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/NumberPartitionProblem_MPZ.o /home/fernando/Dropbox/HC/HCImp/source/NumberPartitionProblem_MPZ.cpp

${OBJECTDIR}/_ext/1469337217/PPN_Heap.o: /home/fernando/Dropbox/HC/HCImp/source/PPN_Heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/PPN_Heap.o /home/fernando/Dropbox/HC/HCImp/source/PPN_Heap.cpp

${OBJECTDIR}/_ext/1469337217/Semaphore.o: /home/fernando/Dropbox/HC/HCImp/source/Semaphore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/Semaphore.o /home/fernando/Dropbox/HC/HCImp/source/Semaphore.cpp

${OBJECTDIR}/_ext/1469337217/main.o: /home/fernando/Dropbox/HC/HCImp/source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1469337217
	${RM} $@.d
	$(COMPILE.cc) -O3 `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1469337217/main.o /home/fernando/Dropbox/HC/HCImp/source/main.cpp

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
