ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_ObserverImpl_LOCAL.idl \
	dinner_ObserverImpl_EQUIVALENT.idl \
	dinner_ObserverImpl_BUSINESS.idl

CPP_FILES = dinner_ObserverImpl_BUSINESS.cpp \
	dinner_ObserverImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdinner_ObserverImpl.so dinner_ObserverImpl.zip

LIBS += -L../dinner_ObserverImpl_SERVANT -ldinner_ObserverImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libdinner_ObserverImpl.so

libdinner_ObserverImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/ObserverImpl:1.0" $< 

dinner_ObserverImpl_BUSINESS.cpp: dinner_ObserverImpl_EQUIVALENT.h dinner_ObserverImpl_LOCAL.h 

dinner_ObserverImpl.cpp: dinner_ObserverImpl_BUSINESS.h

package: dinner_ObserverImpl.zip

dinner_ObserverImpl.zip : meta-inf/dinner_ObserverImpl.ccd meta-inf/dinner_ObserverImpl.csd libdinner_ObserverImpl.so
	zip dinner_ObserverImpl.zip -j ../dinner_ObserverImpl_SERVANT/libdinner_ObserverImpl_SERVANT.so libdinner_ObserverImpl.so $(CIDL_FILES)
	zip dinner_ObserverImpl.zip meta-inf/dinner_ObserverImpl.ccd meta-inf/dinner_ObserverImpl.csd

meta-inf/dinner_ObserverImpl.ccd meta-inf/dinner_ObserverImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:dinner/ObserverImpl:1.0" ../$(CIDL_FILES) )

