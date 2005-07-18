ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_TAPDisplayImpl_LOCAL.idl \
	Simulation_TAPDisplayImpl_EQUIVALENT.idl

CPP_FILES = Simulation_TAPDisplayImpl_EQUIVALENT.cpp \
	Simulation_TAPDisplayImpl_EQUIVALENT_skel.cpp \
	Simulation_TAPDisplayImpl_LOCAL.cpp \
	Simulation_TAPDisplayImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_TAPDisplayImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimulation_TAPDisplayImpl_SERVANT.so

libSimulation_TAPDisplayImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Simulation_TAPDisplayImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Simulation/TAPDisplayImpl:1.0" $<

