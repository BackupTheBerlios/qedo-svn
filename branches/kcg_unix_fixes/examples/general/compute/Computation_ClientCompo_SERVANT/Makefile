ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../compute.cidl

IDL_FILES = Computation_ClientCompo_LOCAL.idl \
	Computation_ClientCompo_EQUIVALENT.idl

CPP_FILES = Computation_ClientCompo_EQUIVALENT.cpp \
	Computation_ClientCompo_EQUIVALENT_skel.cpp \
	Computation_ClientCompo_LOCAL.cpp \
	Computation_ClientCompo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libComputation_ClientCompo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libComputation_ClientCompo_SERVANT.so

libComputation_ClientCompo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Computation_ClientCompo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Computation/ClientCompo:1.0" $<

