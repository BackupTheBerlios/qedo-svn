ORB_IDL_INCLUDE = -I.. 

CIDL_FILES = ../philosophers.cidl
IDL_FILES = dinner_CutleryImpl_LOCAL.idl \
	    dinner_CutleryImpl_EQUIVALENT.idl \
	    dinner_CutleryImpl_BUSINESS.idl

CPP_FILES = dinner_CutleryImpl_BUSINESS.cpp \
				valuetypes.cpp \
            dinner_CutleryImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../dinner_SERVANT -ldinner_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libdinner_CutleryImpl.so

libdinner_CutleryImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/CutleryImpl:1.0" $<

dinner_CutleryImpl_BUSINESS.cpp: dinner_CutleryImpl_EQUIVALENT.h dinner_CutleryImpl_LOCAL.h
