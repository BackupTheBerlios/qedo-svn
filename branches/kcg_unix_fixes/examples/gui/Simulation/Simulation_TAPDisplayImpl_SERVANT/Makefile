ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_TAPDisplayImpl_LOCAL.idl \
	Simulation_TAPDisplayImpl_EQUIVALENT.idl

CPP_FILES = Simulation_TAPDisplayImpl_EQUIVALENT.cpp \
	Simulation_TAPDisplayImpl_EQUIVALENT_skel.cpp \
	Simulation_TAPDisplayImpl_LOCAL.cpp \
	Simulation_TAPDisplayImpl_SERVANT.cpp \
	Simulation_TAPDisplayImpl_PSS.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${CPP_FILES} \
	${CPP_FILES:%.cpp=%.h} \
	Simulation_TAPDisplayImpl_LOCAL_skel.cpp \
	Simulation_TAPDisplayImpl_LOCAL_skel.h \
	Simulation_TAPDisplayImpl_PSS.cpp \
	Simulation_TAPDisplayImpl_PSS.h \
	${OBJ_FILES} \
	libSimulation_TAPDisplayImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimulation_TAPDisplayImpl_SERVANT.so

libSimulation_TAPDisplayImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Simulation_TAPDisplayImpl_SERVANT.cpp Simulation_TAPDisplayImpl_PSS.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Simulation/TAPDisplayImpl:1.0" $<

