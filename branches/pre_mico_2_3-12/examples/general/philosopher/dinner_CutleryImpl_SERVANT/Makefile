ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_CutleryImpl_LOCAL.idl \
	dinner_CutleryImpl_EQUIVALENT.idl

CPP_FILES = dinner_CutleryImpl_EQUIVALENT.cpp \
	dinner_CutleryImpl_EQUIVALENT_skel.cpp \
	dinner_CutleryImpl_LOCAL.cpp \
	dinner_CutleryImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdinner_CutleryImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libdinner_CutleryImpl_SERVANT.so

libdinner_CutleryImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} dinner_CutleryImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:dinner/CutleryImpl:1.0" $<

