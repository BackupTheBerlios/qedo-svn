ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../compute.cidl

IDL_FILES = Computation_ServerCompo_LOCAL.idl \
	Computation_ServerCompo_EQUIVALENT.idl \
	Computation_ServerCompo_BUSINESS.idl 

CPP_FILES = Computation_ServerCompo_BUSINESS.cpp \
	Computation_ServerCompo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libComputation_ServerCompo.so Computation_ServerCompo.zip

LIBS += -L../Computation_ServerCompo_SERVANT -lComputation_ServerCompo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libComputation_ServerCompo.so 

libComputation_ServerCompo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Computation/ServerCompo:1.0" $< 

Computation_ServerCompo_BUSINESS.cpp: Computation_ServerCompo_EQUIVALENT.h Computation_ServerCompo_LOCAL.h 

Computation_ServerCompo.cpp: Computation_ServerCompo_BUSINESS.h

package: Computation_ServerCompo.zip

Computation_ServerCompo.zip : meta-inf/Computation_ServerCompo.ccd meta-inf/Computation_ServerCompo.csd libComputation_ServerCompo.so
	zip Computation_ServerCompo.zip -j ../Computation_ServerCompo_SERVANT/libComputation_ServerCompo_SERVANT.so libComputation_ServerCompo.so $(CIDL_FILES)
	zip Computation_ServerCompo.zip meta-inf/Computation_ServerCompo.ccd meta-inf/Computation_ServerCompo.csd

meta-inf/Computation_ServerCompo.ccd meta-inf/Computation_ServerCompo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Computation/ServerCompo:1.0" ../$(CIDL_FILES) )

