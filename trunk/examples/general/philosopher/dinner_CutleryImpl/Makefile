ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../philosophers.cidl

IDL_FILES = dinner_CutleryImpl_LOCAL.idl \
	dinner_CutleryImpl_EQUIVALENT.idl \
	dinner_CutleryImpl_BUSINESS.idl

CPP_FILES = dinner_CutleryImpl_BUSINESS.cpp \
	dinner_CutleryImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libdinner_CutleryImpl.so dinner_CutleryImpl.zip

LIBS += -L../dinner_CutleryImpl_SERVANT -ldinner_CutleryImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libdinner_CutleryImpl.so

libdinner_CutleryImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:dinner/CutleryImpl:1.0" $< 

dinner_CutleryImpl_BUSINESS.cpp: dinner_CutleryImpl_EQUIVALENT.h dinner_CutleryImpl_LOCAL.h 

dinner_CutleryImpl.cpp: dinner_CutleryImpl_BUSINESS.h

package: dinner_CutleryImpl.zip

dinner_CutleryImpl.zip : meta-inf/dinner_CutleryImpl.ccd meta-inf/dinner_CutleryImpl.csd libdinner_CutleryImpl.so
	zip dinner_CutleryImpl.zip -j ../dinner_CutleryImpl_SERVANT/libdinner_CutleryImpl_SERVANT.so libdinner_CutleryImpl.so $(CIDL_FILES)
	zip dinner_CutleryImpl.zip meta-inf/dinner_CutleryImpl.ccd meta-inf/dinner_CutleryImpl.csd

meta-inf/dinner_CutleryImpl.ccd meta-inf/dinner_CutleryImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:dinner/CutleryImpl:1.0" ../$(CIDL_FILES) )

