ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_PhilosopherImpl_LOCAL.idl \
	dinner_PhilosopherImpl_EQUIVALENT.idl

CPP_FILES = dinner_PhilosopherImpl_EQUIVALENT.cpp \
	dinner_PhilosopherImpl_EQUIVALENT_skel.cpp \
	dinner_PhilosopherImpl_LOCAL.cpp \
	dinner_PhilosopherImpl_SERVANT.cpp \
	dinner_PhilosopherImpl_PSS.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${CPP_FILES} \
	${CPP_FILES:%.cpp=%.h} \
	dinner_PhilosopherImpl_LOCAL_skel.cpp \
	dinner_PhilosopherImpl_LOCAL_skel.h \
	dinner_PhilosopherImpl_PSS.cpp \
	dinner_PhilosopherImpl_PSS.h \
	${OBJ_FILES} \
	libdinner_PhilosopherImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libdinner_PhilosopherImpl_SERVANT.so

libdinner_PhilosopherImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} dinner_PhilosopherImpl_SERVANT.cpp dinner_PhilosopherImpl_PSS.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:dinner/PhilosopherImpl:1.0" $<

