ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_SimulationServerImpl_LOCAL.idl \
	Simulation_SimulationServerImpl_EQUIVALENT.idl \
	Simulation_SimulationServerImpl_BUSINESS.idl 

CPP_FILES = Simulation_SimulationServerImpl_BUSINESS.cpp \
	Simulation_SimulationServerImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_SimulationServerImpl.so Simulation_SimulationServerImpl.zip

LIBS += -L../Simulation_SimulationServerImpl_SERVANT -lSimulation_SimulationServerImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimulation_SimulationServerImpl.so 

libSimulation_SimulationServerImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/SimulationServerImpl:1.0" $< 

Simulation_SimulationServerImpl_BUSINESS.cpp: Simulation_SimulationServerImpl_EQUIVALENT.h Simulation_SimulationServerImpl_LOCAL.h 

Simulation_SimulationServerImpl.cpp: Simulation_SimulationServerImpl_BUSINESS.h

package: Simulation_SimulationServerImpl.zip

Simulation_SimulationServerImpl.zip : meta-inf/Simulation_SimulationServerImpl.ccd meta-inf/Simulation_SimulationServerImpl.csd libSimulation_SimulationServerImpl.so
	zip Simulation_SimulationServerImpl.zip -j ../Simulation_SimulationServerImpl_SERVANT/libSimulation_SimulationServerImpl_SERVANT.so libSimulation_SimulationServerImpl.so $(CIDL_FILES)
	zip Simulation_SimulationServerImpl.zip meta-inf/Simulation_SimulationServerImpl.ccd meta-inf/Simulation_SimulationServerImpl.csd

meta-inf/Simulation_SimulationServerImpl.ccd meta-inf/Simulation_SimulationServerImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/SimulationServerImpl:1.0" ../$(CIDL_FILES) )

