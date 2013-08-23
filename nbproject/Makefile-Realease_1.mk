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
CND_CONF=Realease_1
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
	${OBJECTDIR}/source/SolutionObject.o \
	${OBJECTDIR}/source/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -m64 -fexceptions -DIL_STD
CXXFLAGS=-m64 -m64 -fexceptions -DIL_STD

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lm -pthread -lrt -lmpfr -lgmp -lgmpxx /usr/lib/libgsl.a /usr/lib/libgslcblas.a ../RandomFwk/dist/Release/GNU-Linux-x86/librandomfwk.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: /usr/lib/libgsl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: /usr/lib/libgslcblas.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ../RandomFwk/dist/Release/GNU-Linux-x86/librandomfwk.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/Avl.o: nbproject/Makefile-${CND_CONF}.mk source/Avl.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Avl.o source/Avl.cpp

${OBJECTDIR}/source/BFS.o: nbproject/Makefile-${CND_CONF}.mk source/BFS.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BFS.o source/BFS.cpp

${OBJECTDIR}/source/BasicFunctions.o: nbproject/Makefile-${CND_CONF}.mk source/BasicFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicFunctions.o source/BasicFunctions.cpp

${OBJECTDIR}/source/BasicTypes.o: nbproject/Makefile-${CND_CONF}.mk source/BasicTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicTypes.o source/BasicTypes.cpp

${OBJECTDIR}/source/BasicTypes_heap.o: nbproject/Makefile-${CND_CONF}.mk source/BasicTypes_heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/BasicTypes_heap.o source/BasicTypes_heap.cpp

${OBJECTDIR}/source/CombLookUp.o: nbproject/Makefile-${CND_CONF}.mk source/CombLookUp.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CombLookUp.o source/CombLookUp.cpp

${OBJECTDIR}/source/Combinatorics.o: nbproject/Makefile-${CND_CONF}.mk source/Combinatorics.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Combinatorics.o source/Combinatorics.cpp

${OBJECTDIR}/source/CompleteKarmarkarKarp.o: nbproject/Makefile-${CND_CONF}.mk source/CompleteKarmarkarKarp.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CompleteKarmarkarKarp.o source/CompleteKarmarkarKarp.cpp

${OBJECTDIR}/source/CompleteKarmarkarKarp_MPZ.o: nbproject/Makefile-${CND_CONF}.mk source/CompleteKarmarkarKarp_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/CompleteKarmarkarKarp_MPZ.o source/CompleteKarmarkarKarp_MPZ.cpp

${OBJECTDIR}/source/Cronometro.o: nbproject/Makefile-${CND_CONF}.mk source/Cronometro.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Cronometro.o source/Cronometro.cpp

${OBJECTDIR}/source/Hash.o: nbproject/Makefile-${CND_CONF}.mk source/Hash.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Hash.o source/Hash.cpp

${OBJECTDIR}/source/HashExtended.o: nbproject/Makefile-${CND_CONF}.mk source/HashExtended.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HashExtended.o source/HashExtended.cpp

${OBJECTDIR}/source/HeapStrctPtr.o: nbproject/Makefile-${CND_CONF}.mk source/HeapStrctPtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStrctPtr.o source/HeapStrctPtr.cpp

${OBJECTDIR}/source/HeapStrctPtrMin.o: nbproject/Makefile-${CND_CONF}.mk source/HeapStrctPtrMin.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStrctPtrMin.o source/HeapStrctPtrMin.cpp

${OBJECTDIR}/source/HeapStructure.o: nbproject/Makefile-${CND_CONF}.mk source/HeapStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/HeapStructure.o source/HeapStructure.cpp

${OBJECTDIR}/source/ListStructure.o: nbproject/Makefile-${CND_CONF}.mk source/ListStructure.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ListStructure.o source/ListStructure.cpp

${OBJECTDIR}/source/ListStructurePtr.o: nbproject/Makefile-${CND_CONF}.mk source/ListStructurePtr.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ListStructurePtr.o source/ListStructurePtr.cpp

${OBJECTDIR}/source/Mpz_Heap_Node_Template.o: nbproject/Makefile-${CND_CONF}.mk source/Mpz_Heap_Node_Template.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Mpz_Heap_Node_Template.o source/Mpz_Heap_Node_Template.cpp

${OBJECTDIR}/source/NumberPartitionProblem.o: nbproject/Makefile-${CND_CONF}.mk source/NumberPartitionProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/NumberPartitionProblem.o source/NumberPartitionProblem.cpp

${OBJECTDIR}/source/NumberPartitionProblem_MPZ.o: nbproject/Makefile-${CND_CONF}.mk source/NumberPartitionProblem_MPZ.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/NumberPartitionProblem_MPZ.o source/NumberPartitionProblem_MPZ.cpp

${OBJECTDIR}/source/PPN_Heap.o: nbproject/Makefile-${CND_CONF}.mk source/PPN_Heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/PPN_Heap.o source/PPN_Heap.cpp

${OBJECTDIR}/source/Semaphore.o: nbproject/Makefile-${CND_CONF}.mk source/Semaphore.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Semaphore.o source/Semaphore.cpp

${OBJECTDIR}/source/SolutionObject.o: nbproject/Makefile-${CND_CONF}.mk source/SolutionObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/SolutionObject.o source/SolutionObject.cpp

${OBJECTDIR}/source/main.o: nbproject/Makefile-${CND_CONF}.mk source/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O3 -Iinclude -I../RandomFwk/include -std=c++11 -m64 -fexceptions -DIL_STD -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/main.o source/main.cpp

# Subprojects
.build-subprojects:
	cd ../RandomFwk && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hcimp

# Subprojects
.clean-subprojects:
	cd ../RandomFwk && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
