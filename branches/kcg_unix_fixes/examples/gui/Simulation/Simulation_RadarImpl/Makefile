ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_RadarImpl_BUSINESS.idl 

CPP_FILES = Simulation_RadarImpl_BUSINESS.cpp \
	Simulation_RadarImpl.cpp \
	component_valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${OBJ_FILES} \
	Simulation_RadarImpl_BUSINESS.cpp \
	Simulation_RadarImpl_BUSINESS.h \
	Simulation_RadarImpl_BUSINESS_skel.cpp \
	Simulation_RadarImpl_BUSINESS_skel.h \
	libSimulation_RadarImpl.so \
	Simulation_RadarImpl.zip\
	component_valuetypes.cpp \
	component_valuetypes.h 

LIBS += -L../Simulation_RadarImpl_SERVANT -lSimulation_RadarImpl_SERVANT -L/usr/X11/lib -lfltk

CXXFLAGS += -I. -g -I../Simulation_RadarImpl_SERVANT -I/usr/X11/include

IDL_FLAGS += -I../Simulation_RadarImpl_SERVANT 

include ../MakeComponentVars

all: libSimulation_RadarImpl.so 

libSimulation_RadarImpl.so: ${OBJ_FILES} 

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/RadarImpl:1.0" $< 

Simulation_RadarImpl.cpp: Simulation_RadarImpl_BUSINESS.h

package: Simulation_RadarImpl.zip

Simulation_RadarImpl.zip : meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd libSimulation_RadarImpl.so
	zip Simulation_RadarImpl.zip -j ../Simulation_RadarImpl_SERVANT/libSimulation_RadarImpl_SERVANT.so libSimulation_RadarImpl.so $(CIDL_FILES)
	zip Simulation_RadarImpl.zip meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd

meta-inf/Simulation_RadarImpl.ccd meta-inf/Simulation_RadarImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/RadarImpl:1.0" ../$(CIDL_FILES) )

