QEDO = /home/boehme
CIDL_GEN = ${QEDO}/bin/cidl_gen
ORB_IDL_INCLUDE = -I../IDL -I/home/boehme/include -I/home/boehme/include/mico 
CIDL_ORB_DEF = -DMICO_ORB -DMICO_CIDL_GEN

CIDL_FILES = ../IDL/philosophers.cidl
IDL_FILES = dinner_LOCAL.idl dinner_EQUIVALENT.idl dinne_BUSINESS.idl

CPP_FILES = dinner_EQUIVALENT.cpp \
				dinner_EQUIVALENT_skel.cpp \
            dinner_LOCAL.cpp \
				dinner_SERVANT.cpp 
OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

IDL_FLAGS += -I${QEDO}/idl --relative-paths
CXXFLAGS += -I. -I${QEDO}/include
include ../MakeVars

all: libphilosopherS.so

libphilosopherS.so: ${OBJ_FILES}

${IDL_FILES} : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target dinner $<
