ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_ObserverImpl_LOCAL.idl \
	dinner_ObserverImpl_EQUIVALENT.idl

CPP_FILES = dinner_ObserverImpl_EQUIVALENT.cpp \
	dinner_ObserverImpl_EQUIVALENT_skel.cpp \
	dinner_ObserverImpl_LOCAL.cpp \
	dinner_ObserverImpl_SERVANT.cpp \
	dinner_ObserverImpl_PSS.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${CPP_FILES} \
	${CPP_FILES:%.cpp=%.h} \
	dinner_ObserverImpl_LOCAL_skel.cpp \
	dinner_ObserverImpl_LOCAL_skel.h \
	dinner_ObserverImpl_PSS.cpp \
	dinner_ObserverImpl_PSS.h \
	${OBJ_FILES} \
	libdinner_ObserverImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libdinner_ObserverImpl_SERVANT.so

libdinner_ObserverImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} dinner_ObserverImpl_SERVANT.cpp dinner_ObserverImpl_PSS.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:dinner/ObserverImpl:1.0" $<

