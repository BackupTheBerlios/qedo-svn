ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../hello.cidl

IDL_FILES = HelloWorld_CalleeImpl_LOCAL.idl \
	HelloWorld_CalleeImpl_EQUIVALENT.idl \
	HelloWorld_CalleeImpl_BUSINESS.idl

CPP_FILES = HelloWorld_CalleeImpl_BUSINESS.cpp \
	HelloWorld_CalleeImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${OBJ_FILES} HelloWorld_CalleeImpl.so HelloWorld_CalleeImpl.zip

LIBS += -L../HelloWorld_CalleeImpl_SERVANT -lHelloWorld_CalleeImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libHelloWorld_CalleeImpl.so

libHelloWorld_CalleeImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:HelloWorld/CalleeImpl:1.0" $< 

HelloWorld_CalleeImpl_BUSINESS.cpp: HelloWorld_CalleeImpl_EQUIVALENT.h HelloWorld_CalleeImpl_LOCAL.h 

HelloWorld_CalleeImpl.cpp: HelloWorld_CalleeImpl_BUSINESS.h

package: HelloWorld_CalleeImpl.zip

HelloWorld_CalleeImpl.zip : meta-inf/HelloWorld_CalleeImpl.ccd meta-inf/HelloWorld_CalleeImpl.csd libHelloWorld_CalleeImpl.so
	zip HelloWorld_CalleeImpl.zip -j ../HelloWorld_CalleeImpl_SERVANT/libHelloWorld_CalleeImpl_SERVANT.so libHelloWorld_CalleeImpl.so $(CIDL_FILES)
	zip HelloWorld_CalleeImpl.zip meta-inf/HelloWorld_CalleeImpl.ccd meta-inf/HelloWorld_CalleeImpl.csd

meta-inf/HelloWorld_CalleeImpl.ccd meta-inf/HelloWorld_CalleeImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:HelloWorld/CalleeImpl:1.0" ../$(CIDL_FILES) )

