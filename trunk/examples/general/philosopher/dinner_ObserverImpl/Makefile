QEDO = /home/boehme
CIDL_GEN = ${QEDO}/bin/cidl_gen
ORB_IDL_INCLUDE = -I.. -I/home/boehme/include -I/home/boehme/include/mico 
CIDL_ORB_DEF = -DMICO_ORB -DMICO_CIDL_GEN

CIDL_FILES = ../philosophers.cidl
IDL_FILES = dinner_ObserverImpl_LOCAL.idl \
	    dinner_ObserverImpl_EQUIVALENT.idl \
	    dinner_ObserverImpl_BUSINESS.idl

CPP_FILES = dinner_ObserverImpl_BUSINESS.cpp \
				valuetypes.cpp \
            dinner_ObserverImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../dinner_SERVANT -ldinner_SERVANT

IDL_FLAGS += -I${QEDO}/idl --relative-paths
CXXFLAGS += -I. -I../dinnerServant -I${QEDO}/include -g
include ../MakeVars

all: libdinner_ObserverImpl.so

libdinner_ObserverImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/ObserverImpl:1.0" $<
