ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../monitoring_service.cidl

IDL_FILES = container_service_MonImpl_LOCAL.idl \
	container_service_MonImpl_EQUIVALENT.idl

CPP_FILES = container_service_MonImpl_EQUIVALENT.cpp \
	container_service_MonImpl_EQUIVALENT_skel.cpp \
	container_service_MonImpl_LOCAL.cpp \
	container_service_MonImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libcontainer_service_MonImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libcontainer_service_MonImpl_SERVANT.so

libcontainer_service_MonImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} container_service_MonImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:container_service/MonImpl:1.0" $<

