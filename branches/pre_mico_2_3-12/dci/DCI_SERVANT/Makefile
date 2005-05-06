ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../deployment.cidl

IDL_FILES = DCI_LOCAL.idl \
	DCI_EQUIVALENT.idl

CPP_FILES = DCI_EQUIVALENT.cpp \
	DCI_EQUIVALENT_skel.cpp \
	DCI_LOCAL.cpp \
	DCI_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libDCI_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libDCI_SERVANT.so

libDCI_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} DCI_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:DCI:1.0" $<

