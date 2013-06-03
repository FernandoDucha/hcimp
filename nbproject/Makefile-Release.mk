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
	${OBJECTDIR}/source/Avl.o \
	${OBJECTDIR}/source/BFS.o \
	${OBJECTDIR}/source/BasicFunctions.o \
	${OBJECTDIR}/source/BasicTypes.o \
	${OBJECTDIR}/source/BasicTypes_heap.o \
	${OBJECTDIR}/source/CombLookUp.o \
	${OBJECTDIR}/source/Combinatorics.o \
	${OBJECTDIR}/source/CompleteKarmarkarKarp.o \
	${OBJECTDIR}/source/CompleteKarmarkarKarp_MPZ.o \
	${OBJECTDIR}/source/Cronometro.o \
	${OBJECTDIR}/source/Hash.o \
	${OBJECTDIR}/source/HashExtended.o \
	${OBJECTDIR}/source/HeapStrctPtr.o \
	${OBJECTDIR}/source/HeapStrctPtrMin.o \
	${OBJECTDIR}/source/HeapStructure.o \
	${OBJECTDIR}/source/ListStructure.o \
	${OBJECTDIR}/source/ListStructurePtr.o \
	${OBJECTDIR}/source/Mpz_Heap_Node_Template.o \
	${OBJECTDIR}/source/NumberPartitionProblem.o \
	${OBJECTDIR}/source/NumberPartitionProblem_MPZ.o \
	${OBJECTDIR}/source/PPN_Heap.o \
	${OBJECTDIR}/source/Semaphore.o \
	${OBJECTDIR}/source/main.o


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
LDLIBSOPTIONS=-lm -pthread -lrt -lgmp -lgmpxx `pkg-config --libs gsl` ../RandomFwk/dist/Release/GNU-Linux-x86/libRandomFwk.a  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ../RandomFwk/dist/Release/GNU-Linux-x86/libRandomFwk.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/Avl.o: source/Avl.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Avl.o source/Avl.cpp

${OBJECTDIR}/source/BFS.o: source/BFS.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BFS.o source/BFS.cpp

${OBJECTDIR}/source/BasicFunctions.o: source/BasicFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicFunctions.o source/BasicFunctions.cpp

${OBJECTDIR}/source/BasicTypes.o: source/BasicTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicTypes.o source/BasicTypes.cpp

${OBJECTDIR}/source/BasicTypes_heap.o: source/BasicTypes_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicTypes_heap.o source/BasicTypes_heap.cpp

${OBJECTDIR}/source/CombLookUp.o: source/CombLookUp.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CombLookUp.o source/CombLookUp.cpp

${OBJECTDIR}/source/Combinatorics.o: source/Combinatorics.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Combinatorics.o source/Combinatorics.cpp

${OBJECTDIR}/source/CompleteKarmarkarKarp.o: source/CompleteKarmarkarKarp.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CompleteKarmarkarKarp.o source/CompleteKarmarkarKarp.cpp

${OBJECTDIR}/source/CompleteKarmarkarKarp_MPZ.o: source/CompleteKarmarkarKarp_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CompleteKarmarkarKarp_MPZ.o source/CompleteKarmarkarKarp_MPZ.cpp

${OBJECTDIR}/source/Cronometro.o: source/Cronometro.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Cronometro.o source/Cronometro.cpp

${OBJECTDIR}/source/Hash.o: source/Hash.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Hash.o source/Hash.cpp

${OBJECTDIR}/source/HashExtended.o: source/HashExtended.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HashExtended.o source/HashExtended.cpp

${OBJECTDIR}/source/HeapStrctPtr.o: source/HeapStrctPtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStrctPtr.o source/HeapStrctPtr.cpp

${OBJECTDIR}/source/HeapStrctPtrMin.o: source/HeapStrctPtrMin.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStrctPtrMin.o source/HeapStrctPtrMin.cpp

${OBJECTDIR}/source/HeapStructure.o: source/HeapStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStructure.o source/HeapStructure.cpp

${OBJECTDIR}/source/ListStructure.o: source/ListStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ListStructure.o source/ListStructure.cpp

${OBJECTDIR}/source/ListStructurePtr.o: source/ListStructurePtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ListStructurePtr.o source/ListStructurePtr.cpp

${OBJECTDIR}/source/Mpz_Heap_Node_Template.o: source/Mpz_Heap_Node_Template.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Mpz_Heap_Node_Template.o source/Mpz_Heap_Node_Template.cpp

${OBJECTDIR}/source/NumberPartitionProblem.o: source/NumberPartitionProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/NumberPartitionProblem.o source/NumberPartitionProblem.cpp

${OBJECTDIR}/source/NumberPartitionProblem_MPZ.o: source/NumberPartitionProblem_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/NumberPartitionProblem_MPZ.o source/NumberPartitionProblem_MPZ.cpp

${OBJECTDIR}/source/PPN_Heap.o: source/PPN_Heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/PPN_Heap.o source/PPN_Heap.cpp

${OBJECTDIR}/source/Semaphore.o: source/Semaphore.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Semaphore.o source/Semaphore.cpp

${OBJECTDIR}/source/main.o: source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include `pkg-config --cflags gsl` -std=c++11 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/main.o source/main.cpp

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
