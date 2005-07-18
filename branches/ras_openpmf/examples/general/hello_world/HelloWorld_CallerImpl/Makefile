ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../hello.cidl

IDL_FILES = HelloWorld_CallerImpl_LOCAL.idl \
	HelloWorld_CallerImpl_EQUIVALENT.idl \
	HelloWorld_CallerImpl_BUSINESS.idl

CPP_FILES = HelloWorld_CallerImpl_BUSINESS.cpp \
	HelloWorld_CallerImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${OBJ_FILES} HelloWorld_CallerImpl.so HelloWorld_CallerImpl.zip

LIBS += -L../HelloWorld_CallerImpl_SERVANT -lHelloWorld_CallerImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libHelloWorld_CallerImpl.so

libHelloWorld_CallerImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:HelloWorld/CallerImpl:1.0" $< 

HelloWorld_CallerImpl_BUSINESS.cpp: HelloWorld_CallerImpl_EQUIVALENT.h HelloWorld_CallerImpl_LOCAL.h 

HelloWorld_CallerImpl.cpp: HelloWorld_CallerImpl_BUSINESS.h

package: HelloWorld_CallerImpl.zip

HelloWorld_CallerImpl.zip : meta-inf/HelloWorld_CallerImpl.ccd meta-inf/HelloWorld_CallerImpl.csd libHelloWorld_CallerImpl.so
	zip HelloWorld_CallerImpl.zip -j ../HelloWorld_CallerImpl_SERVANT/libHelloWorld_CallerImpl_SERVANT.so libHelloWorld_CallerImpl.so $(CIDL_FILES)
	zip HelloWorld_CallerImpl.zip meta-inf/HelloWorld_CallerImpl.ccd meta-inf/HelloWorld_CallerImpl.csd

meta-inf/HelloWorld_CallerImpl.ccd meta-inf/HelloWorld_CallerImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:HelloWorld/CallerImpl:1.0" ../$(CIDL_FILES) )

