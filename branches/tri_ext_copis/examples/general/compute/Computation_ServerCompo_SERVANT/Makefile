ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../compute.cidl

IDL_FILES = Computation_ServerCompo_LOCAL.idl \
	Computation_ServerCompo_EQUIVALENT.idl

CPP_FILES = Computation_ServerCompo_EQUIVALENT.cpp \
	Computation_ServerCompo_EQUIVALENT_skel.cpp \
	Computation_ServerCompo_LOCAL.cpp \
	Computation_ServerCompo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libComputation_ServerCompo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libComputation_ServerCompo_SERVANT.so

libComputation_ServerCompo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Computation_ServerCompo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Computation/ServerCompo:1.0" $<

