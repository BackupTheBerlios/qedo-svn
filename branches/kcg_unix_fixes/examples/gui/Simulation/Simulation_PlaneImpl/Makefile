ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simdemo.cidl

IDL_FILES = Simulation_PlaneImpl_BUSINESS.idl 

CPP_FILES = Simulation_PlaneImpl_BUSINESS.cpp \
	Simulation_PlaneImpl.cpp \
	component_valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${OBJ_FILES} \
	Simulation_PlaneImpl_BUSINESS.cpp \
	Simulation_PlaneImpl_BUSINESS.h \
	Simulation_PlaneImpl_BUSINESS_skel.cpp \
	Simulation_PlaneImpl_BUSINESS_skel.h \
	libSimulation_PlaneImpl.so \
	Simulation_PlaneImpl.zip\
	component_valuetypes.cpp \
	component_valuetypes.h 

LIBS += -L../Simulation_PlaneImpl_SERVANT -lSimulation_PlaneImpl_SERVANT -L/usr/X11/lib -lfltk 

CXXFLAGS += -I. -g -I../Simulation_PlaneImpl_SERVANT -I/usr/X11/include

IDL_FLAGS += -I../Simulation_PlaneImpl_SERVANT 

include ../MakeComponentVars

all: libSimulation_PlaneImpl.so 

libSimulation_PlaneImpl.so: ${OBJ_FILES} 

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Simulation/PlaneImpl:1.0" $< 

Simulation_PlaneImpl.cpp: Simulation_PlaneImpl_BUSINESS.h

package: Simulation_PlaneImpl.zip

Simulation_PlaneImpl.zip : meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd libSimulation_PlaneImpl.so
	zip Simulation_PlaneImpl.zip -j ../Simulation_PlaneImpl_SERVANT/libSimulation_PlaneImpl_SERVANT.so libSimulation_PlaneImpl.so $(CIDL_FILES)
	zip Simulation_PlaneImpl.zip meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd

meta-inf/Simulation_PlaneImpl.ccd meta-inf/Simulation_PlaneImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Simulation/PlaneImpl:1.0" ../$(CIDL_FILES) )

