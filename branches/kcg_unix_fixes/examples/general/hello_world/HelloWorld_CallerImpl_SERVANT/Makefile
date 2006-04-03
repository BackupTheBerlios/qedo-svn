ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../hello.cidl

IDL_FILES = HelloWorld_CallerImpl_LOCAL.idl \
	HelloWorld_CallerImpl_EQUIVALENT.idl

CPP_FILES = HelloWorld_CallerImpl_EQUIVALENT.cpp \
	HelloWorld_CallerImpl_EQUIVALENT_skel.cpp \
	HelloWorld_CallerImpl_LOCAL.cpp \
	HelloWorld_CallerImpl_SERVANT.cpp \
	HelloWorld_CallerImpl_PSS.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} \
	${CPP_FILES} \
	${CPP_FILES:%.cpp=%.h} \
	HelloWorld_CallerImpl_LOCAL_skel.cpp \
	HelloWorld_CallerImpl_LOCAL_skel.h \
	HelloWorld_CallerImpl_PSS.cpp \
	HelloWorld_CallerImpl_PSS.h \
	${OBJ_FILES} \
	libHelloWorld_CallerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libHelloWorld_CallerImpl_SERVANT.so

libHelloWorld_CallerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} HelloWorld_CallerImpl_SERVANT.cpp HelloWorld_CallerImpl_PSS.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:HelloWorld/CallerImpl:1.0" $<

