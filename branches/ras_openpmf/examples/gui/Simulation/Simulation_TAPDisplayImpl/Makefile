ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_TAPDisplayImpl_LOCAL.idl \
	Simulation_TAPDisplayImpl_EQUIVALENT.idl \
	Simulation_TAPDisplayImpl_BUSINESS.idl 

CPP_FILES = Simulation_TAPDisplayImpl_BUSINESS.cpp \
	Simulation_TAPDisplayImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_TAPDisplayImpl.so Simulation_TAPDisplayImpl.zip

LIBS += -L../Simulation_TAPDisplayImpl_SERVANT -lSimulation_TAPDisplayImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimulation_TAPDisplayImpl.so 

libSimulation_TAPDisplayImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/TAPDisplayImpl:1.0" $< 

Simulation_TAPDisplayImpl_BUSINESS.cpp: Simulation_TAPDisplayImpl_EQUIVALENT.h Simulation_TAPDisplayImpl_LOCAL.h 

Simulation_TAPDisplayImpl.cpp: Simulation_TAPDisplayImpl_BUSINESS.h

package: Simulation_TAPDisplayImpl.zip

Simulation_TAPDisplayImpl.zip : meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd libSimulation_TAPDisplayImpl.so
	zip Simulation_TAPDisplayImpl.zip -j ../Simulation_TAPDisplayImpl_SERVANT/libSimulation_TAPDisplayImpl_SERVANT.so libSimulation_TAPDisplayImpl.so $(CIDL_FILES)
	zip Simulation_TAPDisplayImpl.zip meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd

meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/TAPDisplayImpl:1.0" ../$(CIDL_FILES) )

