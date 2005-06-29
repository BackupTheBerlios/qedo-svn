ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../inherit.cidl

IDL_FILES = inherit_DerivedImpl_LOCAL.idl \
	inherit_DerivedImpl_EQUIVALENT.idl

CPP_FILES = inherit_DerivedImpl_EQUIVALENT.cpp \
	inherit_DerivedImpl_EQUIVALENT_skel.cpp \
	inherit_DerivedImpl_LOCAL.cpp \
	inherit_DerivedImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CXXFLAGS += -I.

include ../MakeComponentVars

all: libinherit_DerivedImpl_SERVANT.so

libinherit_DerivedImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} inherit_DerivedImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:inherit/DerivedImpl:1.0" $<

