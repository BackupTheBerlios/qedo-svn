ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../compute.cidl

IDL_FILES = Computation_ClientCompo_LOCAL.idl \
	Computation_ClientCompo_EQUIVALENT.idl \
	Computation_ClientCompo_BUSINESS.idl 

CPP_FILES = Computation_ClientCompo_BUSINESS.cpp \
	Computation_ClientCompo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libComputation_ClientCompo.so Computation_ClientCompo.zip

LIBS += -L../Computation_ClientCompo_SERVANT -lComputation_ClientCompo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libComputation_ClientCompo.so 

libComputation_ClientCompo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Computation/ClientCompo:1.0" $< 

Computation_ClientCompo_BUSINESS.cpp: Computation_ClientCompo_EQUIVALENT.h Computation_ClientCompo_LOCAL.h 

Computation_ClientCompo.cpp: Computation_ClientCompo_BUSINESS.h

package: Computation_ClientCompo.zip

Computation_ClientCompo.zip : meta-inf/Computation_ClientCompo.ccd meta-inf/Computation_ClientCompo.csd libComputation_ClientCompo.so
	zip Computation_ClientCompo.zip -j ../Computation_ClientCompo_SERVANT/libComputation_ClientCompo_SERVANT.so libComputation_ClientCompo.so $(CIDL_FILES)
	zip Computation_ClientCompo.zip meta-inf/Computation_ClientCompo.ccd meta-inf/Computation_ClientCompo.csd

meta-inf/Computation_ClientCompo.ccd meta-inf/Computation_ClientCompo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Computation/ClientCompo:1.0" ../$(CIDL_FILES) )

