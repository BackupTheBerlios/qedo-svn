ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_TAPDisplayImpl_BUSINESS.idl 

CPP_FILES = Simulation_TAPDisplayImpl_BUSINESS.cpp \
	Simulation_TAPDisplayImpl.cpp \
	component_valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${OBJ_FILES} \
	Simulation_TAPDisplayImpl_BUSINESS.cpp \
	Simulation_TAPDisplayImpl_BUSINESS.h \
	Simulation_TAPDisplayImpl_BUSINESS_skel.cpp \
	Simulation_TAPDisplayImpl_BUSINESS_skel.h \
	libSimulation_TAPDisplayImpl.so \
	Simulation_TAPDisplayImpl.zip\
	component_valuetypes.cpp \
	component_valuetypes.h 

LIBS += -L../Simulation_TAPDisplayImpl_SERVANT -lSimulation_TAPDisplayImpl_SERVANT -L/usr/X11/lib -lfltk 

CXXFLAGS += -I. -g -I../Simulation_TAPDisplayImpl_SERVANT -I/usr/X11/include

IDL_FLAGS += -I../Simulation_TAPDisplayImpl_SERVANT 

include ../MakeComponentVars

all: libSimulation_TAPDisplayImpl.so 

libSimulation_TAPDisplayImpl.so: ${OBJ_FILES} 

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/TAPDisplayImpl:1.0" $< 

Simulation_TAPDisplayImpl.cpp: Simulation_TAPDisplayImpl_BUSINESS.h

package: Simulation_TAPDisplayImpl.zip

Simulation_TAPDisplayImpl.zip : meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd libSimulation_TAPDisplayImpl.so
	zip Simulation_TAPDisplayImpl.zip -j ../Simulation_TAPDisplayImpl_SERVANT/libSimulation_TAPDisplayImpl_SERVANT.so libSimulation_TAPDisplayImpl.so $(CIDL_FILES)
	zip Simulation_TAPDisplayImpl.zip meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd

meta-inf/Simulation_TAPDisplayImpl.ccd meta-inf/Simulation_TAPDisplayImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/TAPDisplayImpl:1.0" ../$(CIDL_FILES) )

