QEDO = /home/boehme
CIDL_GEN = ${QEDO}/bin/cidl_gen
ORB_IDL_INCLUDE = -I.. -I/home/boehme/include -I/home/boehme/include/mico 
CIDL_ORB_DEF = -DMICO_ORB -DMICO_CIDL_GEN

CIDL_FILES = ../philosophers.cidl
IDL_FILES = dinner_PhilosopherImpl_LOCAL.idl \
	    dinner_PhilosopherImpl_EQUIVALENT.idl \
	    dinner_PhilosopherImpl_BUSINESS.idl

CPP_FILES = dinner_PhilosopherImpl_BUSINESS.cpp \
				valuetypes.cpp \
            dinner_PhilosopherImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../dinner_SERVANT -ldinner_SERVANT

IDL_FLAGS += -I${QEDO}/idl --relative-paths
CXXFLAGS += -I. -I../dinnerServant -I${QEDO}/include -g
include ../MakeVars

all: libdinner_PhilosopherImpl.so

libdinner_PhilosopherImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/PhilosopherImpl:1.0" $<
