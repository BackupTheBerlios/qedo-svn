ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../hello.cidl

IDL_FILES = HelloWorld_CalleeImpl_LOCAL.idl \
	HelloWorld_CalleeImpl_EQUIVALENT.idl

CPP_FILES = HelloWorld_CalleeImpl_EQUIVALENT.cpp \
	HelloWorld_CalleeImpl_EQUIVALENT_skel.cpp \
	HelloWorld_CalleeImpl_LOCAL.cpp \
	HelloWorld_CalleeImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CXXFLAGS += -I.

include ../MakeComponentVars

all: libHelloWorld_CalleeImpl_SERVANT.so

libHelloWorld_CalleeImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} HelloWorld_CalleeImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:HelloWorld/CalleeImpl:1.0" $<

