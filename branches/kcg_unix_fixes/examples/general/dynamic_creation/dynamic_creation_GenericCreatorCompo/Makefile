ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../dynamic_creation.cidl

IDL_FILES = dynamic_creation_GenericCreatorCompo_LOCAL.idl \
	dynamic_creation_GenericCreatorCompo_EQUIVALENT.idl \
	dynamic_creation_GenericCreatorCompo_BUSINESS.idl 

CPP_FILES = dynamic_creation_GenericCreatorCompo_BUSINESS.cpp \
	dynamic_creation_GenericCreatorCompo.cpp \
	component_valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdynamic_creation_GenericCreatorCompo.so dynamic_creation_GenericCreatorCompo.zip

LIBS += -L../dynamic_creation_GenericCreatorCompo_SERVANT -ldynamic_creation_GenericCreatorCompo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libdynamic_creation_GenericCreatorCompo.so 

libdynamic_creation_GenericCreatorCompo.so: ${OBJ_FILES} 

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dynamic_creation/GenericCreatorCompo:1.0" $< 

dynamic_creation_GenericCreatorCompo_BUSINESS.cpp: dynamic_creation_GenericCreatorCompo_EQUIVALENT.h dynamic_creation_GenericCreatorCompo_LOCAL.h 

dynamic_creation_GenericCreatorCompo.cpp: dynamic_creation_GenericCreatorCompo_BUSINESS.h

package: dynamic_creation_GenericCreatorCompo.zip

dynamic_creation_GenericCreatorCompo.zip : meta-inf/dynamic_creation_GenericCreatorCompo.ccd meta-inf/dynamic_creation_GenericCreatorCompo.csd libdynamic_creation_GenericCreatorCompo.so
	zip dynamic_creation_GenericCreatorCompo.zip -j ../dynamic_creation_GenericCreatorCompo_SERVANT/libdynamic_creation_GenericCreatorCompo_SERVANT.so libdynamic_creation_GenericCreatorCompo.so $(CIDL_FILES)
	zip dynamic_creation_GenericCreatorCompo.zip meta-inf/dynamic_creation_GenericCreatorCompo.ccd meta-inf/dynamic_creation_GenericCreatorCompo.csd

meta-inf/dynamic_creation_GenericCreatorCompo.ccd meta-inf/dynamic_creation_GenericCreatorCompo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:dynamic_creation/GenericCreatorCompo:1.0" ../$(CIDL_FILES) )

