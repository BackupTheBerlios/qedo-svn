ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../inherit.cidl

IDL_FILES = inherit_DerivedImpl_LOCAL.idl \
	inherit_DerivedImpl_EQUIVALENT.idl \
	inherit_DerivedImpl_BUSINESS.idl 

CPP_FILES = inherit_DerivedImpl_BUSINESS.cpp \
	inherit_DerivedImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

LIBS += -L../inherit_DerivedImpl_SERVANT -linherit_DerivedImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libinherit_DerivedImpl.so 

libinherit_DerivedImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:inherit/DerivedImpl:1.0" $< 

inherit_DerivedImpl_BUSINESS.cpp: inherit_DerivedImpl_EQUIVALENT.h inherit_DerivedImpl_LOCAL.h 

inherit_DerivedImpl.cpp: inherit_DerivedImpl_BUSINESS.h

