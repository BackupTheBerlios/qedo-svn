ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../deployment.cidl

IDL_FILES = DCI_RepNodeManagerImpl_LOCAL.idl \
	DCI_RepNodeManagerImpl_EQUIVALENT.idl \
	DCI_RepNodeManagerImpl_BUSINESS.idl 

CPP_FILES = DCI_RepNodeManagerImpl_BUSINESS.cpp \
	DCI_RepNodeManagerImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libDCI_RepNodeManagerImpl.so DCI_RepNodeManagerImpl.zip

LIBS += -L../DCI_SERVANT -lDCI_SERVANT -L../mda-infra -lDCI_mda_infra

CXXFLAGS += -I. -I../mda-infra -g

include ../MakeComponentVars

all: libDCI_RepNodeManagerImpl.so 

libDCI_RepNodeManagerImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:DCI/RepNodeManagerImpl:1.0" $< 

DCI_RepNodeManagerImpl_BUSINESS.cpp: DCI_RepNodeManagerImpl_EQUIVALENT.h DCI_RepNodeManagerImpl_LOCAL.h 

DCI_RepNodeManagerImpl.cpp: DCI_RepNodeManagerImpl_BUSINESS.h

package: DCI_RepNodeManagerImpl.zip

DCI_RepNodeManagerImpl.zip : meta-inf/DCI_RepNodeManagerImpl.ccd meta-inf/DCI_RepNodeManagerImpl.csd libDCI_RepNodeManagerImpl.so
	zip DCI_RepNodeManagerImpl.zip -j ../DCI_SERVANT/libDCI_SERVANT.so libDCI_RepNodeManagerImpl.so $(CIDL_FILES)
	zip DCI_RepNodeManagerImpl.zip meta-inf/DCI_RepNodeManagerImpl.ccd meta-inf/DCI_RepNodeManagerImpl.csd

meta-inf/DCI_RepNodeManagerImpl.ccd meta-inf/DCI_RepNodeManagerImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:DCI/RepNodeManagerImpl:1.0" ../$(CIDL_FILES) )

