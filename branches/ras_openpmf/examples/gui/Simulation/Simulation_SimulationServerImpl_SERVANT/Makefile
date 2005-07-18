ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_SimulationServerImpl_LOCAL.idl \
	Simulation_SimulationServerImpl_EQUIVALENT.idl

CPP_FILES = Simulation_SimulationServerImpl_EQUIVALENT.cpp \
	Simulation_SimulationServerImpl_EQUIVALENT_skel.cpp \
	Simulation_SimulationServerImpl_LOCAL.cpp \
	Simulation_SimulationServerImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_SimulationServerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimulation_SimulationServerImpl_SERVANT.so

libSimulation_SimulationServerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Simulation_SimulationServerImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Simulation/SimulationServerImpl:1.0" $<

