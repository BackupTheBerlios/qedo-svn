ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_PhilosopherImpl_LOCAL.idl \
	dinner_PhilosopherImpl_EQUIVALENT.idl \
	dinner_PhilosopherImpl_BUSINESS.idl

CPP_FILES = dinner_PhilosopherImpl_BUSINESS.cpp \
	dinner_PhilosopherImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdinner_PhilosopherImpl.so dinner_PhilosopherImpl.zip

LIBS += -L../dinner_PhilosopherImpl_SERVANT -ldinner_PhilosopherImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libdinner_PhilosopherImpl.so

libdinner_PhilosopherImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/PhilosopherImpl:1.0" $< 

dinner_PhilosopherImpl_BUSINESS.cpp: dinner_PhilosopherImpl_EQUIVALENT.h dinner_PhilosopherImpl_LOCAL.h 

dinner_PhilosopherImpl.cpp: dinner_PhilosopherImpl_BUSINESS.h

package: dinner_PhilosopherImpl.zip

dinner_PhilosopherImpl.zip : meta-inf/dinner_PhilosopherImpl.ccd meta-inf/dinner_PhilosopherImpl.csd libdinner_PhilosopherImpl.so
	zip dinner_PhilosopherImpl.zip -j ../dinner_PhilosopherImpl_SERVANT/libdinner_PhilosopherImpl_SERVANT.so libdinner_PhilosopherImpl.so $(CIDL_FILES)
	zip dinner_PhilosopherImpl.zip meta-inf/dinner_PhilosopherImpl.ccd meta-inf/dinner_PhilosopherImpl.csd

meta-inf/dinner_PhilosopherImpl.ccd meta-inf/dinner_PhilosopherImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:dinner/PhilosopherImpl:1.0" ../$(CIDL_FILES) )

