ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_PlaneImpl_LOCAL.idl \
	Simulation_PlaneImpl_EQUIVALENT.idl

CPP_FILES = Simulation_PlaneImpl_EQUIVALENT.cpp \
	Simulation_PlaneImpl_EQUIVALENT_skel.cpp \
	Simulation_PlaneImpl_LOCAL.cpp \
	Simulation_PlaneImpl_SERVANT.cpp \
	Simulation_PlaneImpl_PSS.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${CPP_FILES} \
	${CPP_FILES:%.cpp=%.h} \
	Simulation_PlaneImpl_LOCAL_skel.cpp \
	Simulation_PlaneImpl_LOCAL_skel.h \
	Simulation_PlaneImpl_PSS.cpp \
	Simulation_PlaneImpl_PSS.h \
	${OBJ_FILES} \
	libSimulation_PlaneImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimulation_PlaneImpl_SERVANT.so

libSimulation_PlaneImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Simulation_PlaneImpl_SERVANT.cpp Simulation_PlaneImpl_PSS.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Simulation/PlaneImpl:1.0" $<

