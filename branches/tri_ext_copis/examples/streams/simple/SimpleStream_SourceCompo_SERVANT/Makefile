ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simple_stream.cidl

IDL_FILES = SimpleStream_SourceCompo_LOCAL.idl \
	SimpleStream_SourceCompo_EQUIVALENT.idl

CPP_FILES = SimpleStream_SourceCompo_EQUIVALENT.cpp \
	SimpleStream_SourceCompo_EQUIVALENT_skel.cpp \
	SimpleStream_SourceCompo_LOCAL.cpp \
	SimpleStream_SourceCompo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimpleStream_SourceCompo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimpleStream_SourceCompo_SERVANT.so

libSimpleStream_SourceCompo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} SimpleStream_SourceCompo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:SimpleStream/SourceCompo:1.0" $<

