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
CC=g++
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/11_enhanced_helloworld.o \
	${OBJECTDIR}/19_calc.o \
	${OBJECTDIR}/37_handson_pointers.o \
	${OBJECTDIR}/brute.o \
	${OBJECTDIR}/one_day_game.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/test.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learningpathbeginningcpp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learningpathbeginningcpp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learningpathbeginningcpp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/11_enhanced_helloworld.o: 11_enhanced_helloworld.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/11_enhanced_helloworld.o 11_enhanced_helloworld.cpp

${OBJECTDIR}/19_calc.o: 19_calc.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/19_calc.o 19_calc.cpp

${OBJECTDIR}/37_handson_pointers.o: 37_handson_pointers.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/37_handson_pointers.o 37_handson_pointers.cpp

${OBJECTDIR}/brute.o: brute.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/brute.o brute.cpp

${OBJECTDIR}/data.hpp.gch: data.hpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o "$@" data.hpp

${OBJECTDIR}/find.hpp.gch: find.hpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o "$@" find.hpp

${OBJECTDIR}/functions.hpp.gch: functions.hpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o "$@" functions.hpp

${OBJECTDIR}/one_day_game.o: one_day_game.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/one_day_game.o one_day_game.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:
	cd ../../../NetBeansProjects/GoogleTest && ${MAKE}  -f Makefile CONF=Debug

${TESTDIR}/TestFiles/f1: ${TESTDIR}/test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   ../../../NetBeansProjects/GoogleTest/dist/Debug/GNU-MacOSX/libgoogletest.a 


${TESTDIR}/test.o: test.cpp 
	${MKDIR} -p ${TESTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/Users/roman.subik/pworkspace/googletest/googletest -I/Users/roman.subik/pworkspace/googletest/googletest/include -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/test.o test.cpp


${OBJECTDIR}/11_enhanced_helloworld_nomain.o: ${OBJECTDIR}/11_enhanced_helloworld.o 11_enhanced_helloworld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/11_enhanced_helloworld.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/11_enhanced_helloworld_nomain.o 11_enhanced_helloworld.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/11_enhanced_helloworld.o ${OBJECTDIR}/11_enhanced_helloworld_nomain.o;\
	fi

${OBJECTDIR}/19_calc_nomain.o: ${OBJECTDIR}/19_calc.o 19_calc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/19_calc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/19_calc_nomain.o 19_calc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/19_calc.o ${OBJECTDIR}/19_calc_nomain.o;\
	fi

${OBJECTDIR}/37_handson_pointers_nomain.o: ${OBJECTDIR}/37_handson_pointers.o 37_handson_pointers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/37_handson_pointers.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/37_handson_pointers_nomain.o 37_handson_pointers.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/37_handson_pointers.o ${OBJECTDIR}/37_handson_pointers_nomain.o;\
	fi

${OBJECTDIR}/brute_nomain.o: ${OBJECTDIR}/brute.o brute.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/brute.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/brute_nomain.o brute.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/brute.o ${OBJECTDIR}/brute_nomain.o;\
	fi

${OBJECTDIR}/data_nomain.hpp.gch: ${OBJECTDIR}/data.hpp.gch data.hpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data.hpp.gch`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o "$@" data.hpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data.hpp.gch ${OBJECTDIR}/data_nomain.hpp.gch;\
	fi

${OBJECTDIR}/find_nomain.hpp.gch: ${OBJECTDIR}/find.hpp.gch find.hpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/find.hpp.gch`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o "$@" find.hpp;\
	else  \
	    ${CP} ${OBJECTDIR}/find.hpp.gch ${OBJECTDIR}/find_nomain.hpp.gch;\
	fi

${OBJECTDIR}/functions_nomain.hpp.gch: ${OBJECTDIR}/functions.hpp.gch functions.hpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/functions.hpp.gch`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o "$@" functions.hpp;\
	else  \
	    ${CP} ${OBJECTDIR}/functions.hpp.gch ${OBJECTDIR}/functions_nomain.hpp.gch;\
	fi

${OBJECTDIR}/one_day_game_nomain.o: ${OBJECTDIR}/one_day_game.o one_day_game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/one_day_game.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/one_day_game_nomain.o one_day_game.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/one_day_game.o ${OBJECTDIR}/one_day_game_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
