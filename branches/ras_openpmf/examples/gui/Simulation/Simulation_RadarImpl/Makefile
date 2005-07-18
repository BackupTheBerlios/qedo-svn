ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_RadarImpl_LOCAL.idl \
	Simulation_RadarImpl_EQUIVALENT.idl \
	Simulation_RadarImpl_BUSINESS.idl 

CPP_FILES = Simulation_RadarImpl_BUSINESS.cpp \
	Simulation_RadarImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_RadarImpl.so Simulation_RadarImpl.zip

LIBS += -L../Simulation_RadarImpl_SERVANT -lSimulation_RadarImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimulation_RadarImpl.so 

libSimulation_RadarImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/RadarImpl:1.0" $< 

Simulation_RadarImpl_BUSINESS.cpp: Simulation_RadarImpl_EQUIVALENT.h Simulation_RadarImpl_LOCAL.h 

Simulation_RadarImpl.cpp: Simulation_RadarImpl_BUSINESS.h

package: Simulation_RadarImpl.zip

Simulation_RadarImpl.zip : meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd libSimulation_RadarImpl.so
	zip Simulation_RadarImpl.zip -j ../Simulation_RadarImpl_SERVANT/libSimulation_RadarImpl_SERVANT.so libSimulation_RadarImpl.so $(CIDL_FILES)
	zip Simulation_RadarImpl.zip meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd

meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/RadarImpl:1.0" ../$(CIDL_FILES) )

