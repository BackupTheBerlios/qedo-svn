ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../openpmf_ccm.cidl

IDL_FILES = openpmf_ccm_PEP_ManagerImpl_LOCAL.idl \
	openpmf_ccm_PEP_ManagerImpl_EQUIVALENT.idl

CPP_FILES = openpmf_ccm_PEP_ManagerImpl_EQUIVALENT.cpp \
	openpmf_ccm_PEP_ManagerImpl_EQUIVALENT_skel.cpp \
	openpmf_ccm_PEP_ManagerImpl_LOCAL.cpp \
	openpmf_ccm_PEP_ManagerImpl_LOCAL_skel.cpp \
	openpmf_ccm_PEP_ManagerImpl_SERVANT.cpp \
	openpmf_ccm_PEP_ManagerImpl_PSS.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

H_FILES = ${CPP_FILES:%.cpp=%.h}

CLEAN_FILES = ${IDL_FILES} ${CPP_FILES} ${H_FILES} ${OBJ_FILES} libopenpmf_ccm_PEP_ManagerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libopenpmf_ccm_PEP_ManagerImpl_SERVANT.so

libopenpmf_ccm_PEP_ManagerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} openpmf_ccm_PEP_ManagerImpl_SERVANT.cpp openpmf_ccm_PEP_ManagerImpl_PSS.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:openpmf_ccm/PEP_ManagerImpl:1.0" $<

install:

