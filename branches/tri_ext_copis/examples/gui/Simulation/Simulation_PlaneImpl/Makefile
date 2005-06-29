ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_PlaneImpl_LOCAL.idl \
	Simulation_PlaneImpl_EQUIVALENT.idl \
	Simulation_PlaneImpl_BUSINESS.idl 

CPP_FILES = Simulation_PlaneImpl_BUSINESS.cpp \
	Simulation_PlaneImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimulation_PlaneImpl.so Simulation_PlaneImpl.zip

LIBS += -L../Simulation_PlaneImpl_SERVANT -lSimulation_PlaneImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimulation_PlaneImpl.so 

libSimulation_PlaneImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/PlaneImpl:1.0" $< 

Simulation_PlaneImpl_BUSINESS.cpp: Simulation_PlaneImpl_EQUIVALENT.h Simulation_PlaneImpl_LOCAL.h 

Simulation_PlaneImpl.cpp: Simulation_PlaneImpl_BUSINESS.h

package: Simulation_PlaneImpl.zip

Simulation_PlaneImpl.zip : meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd libSimulation_PlaneImpl.so
	zip Simulation_PlaneImpl.zip -j ../Simulation_PlaneImpl_SERVANT/libSimulation_PlaneImpl_SERVANT.so libSimulation_PlaneImpl.so $(CIDL_FILES)
	zip Simulation_PlaneImpl.zip meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd

meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/PlaneImpl:1.0" ../$(CIDL_FILES) )

