ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../openpmf_ccm.cidl

IDL_FILES = openpmf_ccm_PEP_ManagerImpl_BUSINESS.idl

CPP_FILES = openpmf_ccm_PEP_ManagerImpl_BUSINESS.cpp \
	openpmf_ccm_PEP_ManagerImpl.cpp \
	component_valuetypes.cpp

H_FILES = openpmf_ccm_PEP_ManagerImpl_BUSINESS.h \
        openpmf_ccm_PEP_ManagerImpl.h \
        component_valuetypes.h

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} ServerPEPInterceptor.o
CPP_GEN_FILES = ${IDL_FILES:%.idl=%.cpp}
H_GEN_FILES = ${IDL_FILES:%.idl=%.h}
CPP_GEN_SKEL_FILES = ${IDL_FILES:%.idl=%_skel.cpp}
H_GEN_SKEL_FILES = ${IDL_FILES:%.idl=%_skel.h}

CLEAN_FILES = ${IDL_FILES} ${CPP_GEN_FILES} ${CPP_GEN_SKEL_FILES} ${H_GEN_FILES} ${H_GEN_SKEL_FILES} ${OBJ_FILES} libopenpmf_ccm_PEP_ManagerImpl.so OpenPMFPEPImpl.zip libOpenPMFPEPImpl.so openpmf_ccm_PEP_ManagerImpl_PSS.* component_valuetypes.* ServerPEPInterceptor.o

LIBS += -L../openpmf_ccm_PEP_ManagerImpl_SERVANT -lopenpmf_ccm_PEP_ManagerImpl_SERVANT -L/usr/local/lib -lpmf2.3.12 -lpmfcorba2.3.12 -lpmfccm2.3.12

CXXFLAGS += -I. -I../openpmf_ccm_PEP_ManagerImpl_SERVANT/

IDL_FLAGS += -I../openpmf_ccm_PEP_ManagerImpl_SERVANT/

include ../MakeComponentVars

all: libopenpmf_ccm_PEP_ManagerImpl.so

libopenpmf_ccm_PEP_ManagerImpl.so: ${OBJ_FILES} 

${IDL_FILES} component_valuetypes.cpp openpmf_ccm_PEP_ManagerImpl.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:openpmf_ccm/PEP_ManagerImpl:1.0" $< 

openpmf_ccm_PEP_ManagerImpl_BUSINESS.cpp: ../openpmf_ccm_PEP_ManagerImpl_SERVANT/openpmf_ccm_PEP_ManagerImpl_EQUIVALENT.h ../openpmf_ccm_PEP_ManagerImpl_SERVANT/openpmf_ccm_PEP_ManagerImpl_LOCAL.h 

OpenPMFPEPImpl.cpp: openpmf_ccm_PEP_ManagerImpl_BUSINESS.h

package: OpenPMFPEPImpl.zip

OpenPMFPEPImpl.zip : libOpenPMFPEPImpl.so
	zip OpenPMFPEPImpl.zip -j ../openpmf_ccm_PEP_ManagerImpl_SERVANT/libopenpmf_ccm_PEP_ManagerImpl_SERVANT.so libopenpmf_ccm_PEP_ManagerImpl.so $(CIDL_FILES)
	zip OpenPMFPEPImpl.zip meta-inf/openpmf_ccm_PEP_ManagerImpl.ccd meta-inf/openpmf_ccm_PEP_ManagerImpl.csd

install: package
	mkdir -p ${QEDO}/services
	cp OpenPMFPEPImpl.zip ${QEDO}/services/.
