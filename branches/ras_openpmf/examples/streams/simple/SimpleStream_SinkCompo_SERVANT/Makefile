ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simple_stream.cidl

IDL_FILES = SimpleStream_SinkCompo_LOCAL.idl \
	SimpleStream_SinkCompo_EQUIVALENT.idl

CPP_FILES = SimpleStream_SinkCompo_EQUIVALENT.cpp \
	SimpleStream_SinkCompo_EQUIVALENT_skel.cpp \
	SimpleStream_SinkCompo_LOCAL.cpp \
	SimpleStream_SinkCompo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimpleStream_SinkCompo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libSimpleStream_SinkCompo_SERVANT.so

libSimpleStream_SinkCompo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} SimpleStream_SinkCompo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:SimpleStream/SinkCompo:1.0" $<

