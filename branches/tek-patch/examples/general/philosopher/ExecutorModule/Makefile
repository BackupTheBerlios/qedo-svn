QEDO = /home/boehme
CIDL_GEN = ${QEDO}/bin/cidl_gen
ORB_IDL_INCLUDE = -I../IDL -I/home/boehme/include -I/home/boehme/include/mico 
CIDL_ORB_DEF = -DMICO_ORB -DMICO_CIDL_GEN

CIDL_FILES = ../IDL/philosophers.cidl
IDL_FILES = dinner_LOCAL.idl dinner_EQUIVALENT.idl dinne_BUSINESS.idl

CPP_FILES = dinner_BUSINESS.cpp \
				valuetypes.cpp \
            dinner_CutleryImpl.cpp \
            dinner_ObserverImpl.cpp \
				dinner_PhilosopherImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../ServantModule -lphilosopherS

IDL_FLAGS += -I${QEDO}/idl --relative-paths
CXXFLAGS += -I. -I./ServantModule -I${QEDO}/include -g
include ../MakeVars

all: libphilosopherE.so

libphilosopherE.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target dinner $<
