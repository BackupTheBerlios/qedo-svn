ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../monitoring_service.cidl

IDL_FILES = container_service_MonImpl_LOCAL.idl \
	container_service_MonImpl_EQUIVALENT.idl \
	container_service_MonImpl_BUSINESS.idl

CPP_FILES = container_service_MonImpl_BUSINESS.cpp \
	container_service_MonImpl.cpp \
	ServerContainerInterceptor.cpp \
	valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libcontainer_service_MonImpl.so container_service_MonImpl.zip

LIBS += -L../container_service_MonImpl_SERVANT -lcontainer_service_MonImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libcontainer_service_MonImpl.so 

libcontainer_service_MonImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:container_service/MonImpl:1.0" $< 

container_service_MonImpl_BUSINESS.cpp: container_service_MonImpl_EQUIVALENT.h container_service_MonImpl_LOCAL.h 

container_service_MonImpl.cpp: container_service_MonImpl_BUSINESS.h

package: container_service_MonImpl.zip

container_service_MonImpl.zip : meta-inf/container_service_MonImpl.ccd meta-inf/container_service_MonImpl.csd libcontainer_service_MonImpl.so
	zip container_service_MonImpl.zip -j ../container_service_MonImpl_SERVANT/libcontainer_service_MonImpl_SERVANT.so libcontainer_service_MonImpl.so $(CIDL_FILES)
	zip container_service_MonImpl.zip meta-inf/container_service_MonImpl.ccd meta-inf/container_service_MonImpl.csd

meta-inf/container_service_MonImpl.ccd meta-inf/container_service_MonImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:container_service/MonImpl:1.0" ../$(CIDL_FILES) )

