ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl
IDL_FILES = dinner_LOCAL.idl dinner_EQUIVALENT.idl

CPP_FILES = dinner_EQUIVALENT.cpp \
				dinner_EQUIVALENT_skel.cpp \
            dinner_LOCAL.cpp \
				dinner_SERVANT.cpp 
OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CXXFLAGS += -I. 

include ../MakeVars

all: libdinner_SERVANT.so

libdinner_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} dinner_SERVANT.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target dinner $<
