ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../inherit.cidl

IDL_FILES = inherit_DerivedImpl_LOCAL.idl \
	inherit_DerivedImpl_EQUIVALENT.idl \
	inherit_DerivedImpl_BUSINESS.idl 

CPP_FILES = inherit_DerivedImpl_BUSINESS.cpp \
	inherit_DerivedImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = *.zip

LIBS += -L../inherit_DerivedImpl_SERVANT -linherit_DerivedImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libinherit_DerivedImpl.so 

libinherit_DerivedImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:inherit/DerivedImpl:1.0" $< 

inherit_DerivedImpl_BUSINESS.cpp: inherit_DerivedImpl_EQUIVALENT.h inherit_DerivedImpl_LOCAL.h 

inherit_DerivedImpl.cpp: inherit_DerivedImpl_BUSINESS.h

package: inherit_DerivedImpl_$(OS).zip

inherit_DerivedImpl_$(OS).zip : meta-inf/inherit_DerivedImpl.ccd meta-inf/inherit_DerivedImpl.csd libinherit_DerivedImpl.so
	zip inherit_DerivedImpl_$(OS).zip -j ../inherit_DerivedImpl_SERVANT/libinherit_DerivedImpl_SERVANT.so libinherit_DerivedImpl.so $(CIDL_FILES)
	zip inherit_DerivedImpl_$(OS).zip meta-inf/inherit_DerivedImpl.ccd meta-inf/inherit_DerivedImpl.csd

meta-inf/inherit_DerivedImpl.ccd meta-inf/inherit_DerivedImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:inherit/DerivedImpl:1.0" ../$(CIDL_FILES) )

