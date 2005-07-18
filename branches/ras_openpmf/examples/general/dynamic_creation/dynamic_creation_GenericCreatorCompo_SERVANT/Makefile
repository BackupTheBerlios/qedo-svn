ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../dynamic_creation.cidl

IDL_FILES = dynamic_creation_GenericCreatorCompo_LOCAL.idl \
	dynamic_creation_GenericCreatorCompo_EQUIVALENT.idl

CPP_FILES = dynamic_creation_GenericCreatorCompo_EQUIVALENT.cpp \
	dynamic_creation_GenericCreatorCompo_EQUIVALENT_skel.cpp \
	dynamic_creation_GenericCreatorCompo_LOCAL.cpp \
	dynamic_creation_GenericCreatorCompo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdynamic_creation_GenericCreatorCompo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libdynamic_creation_GenericCreatorCompo_SERVANT.so

libdynamic_creation_GenericCreatorCompo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} dynamic_creation_GenericCreatorCompo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:dynamic_creation/GenericCreatorCompo:1.0" $<

