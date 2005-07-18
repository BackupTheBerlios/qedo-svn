ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_RadarImpl_LOCAL.idl \
	Simulation_RadarImpl_EQUIVALENT.idl

CPP_FILES = Simulation_RadarImpl_EQUIVALENT.cpp \
	Simulation_RadarImpl_EQUIVALENT_skel.cpp \
	Simulation_RadarImpl_LOCAL.cpp \
	Simulation_RadarImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_RadarImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimulation_RadarImpl_SERVANT.so

libSimulation_RadarImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Simulation_RadarImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Simulation/RadarImpl:1.0" $<

