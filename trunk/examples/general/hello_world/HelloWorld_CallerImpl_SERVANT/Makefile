ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../hello.cidl

IDL_FILES = HelloWorld_CallerImpl_LOCAL.idl \
	HelloWorld_CallerImpl_EQUIVALENT.idl

CPP_FILES = HelloWorld_CallerImpl_EQUIVALENT.cpp \
	HelloWorld_CallerImpl_EQUIVALENT_skel.cpp \
	HelloWorld_CallerImpl_LOCAL.cpp \
	HelloWorld_CallerImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${OBJ_FILES} HelloWorld_CallerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libHelloWorld_CallerImpl_SERVANT.so

libHelloWorld_CallerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} HelloWorld_CallerImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:HelloWorld/CallerImpl:1.0" $<

