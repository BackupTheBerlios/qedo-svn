ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simple_stream.cidl

IDL_FILES = SimpleStream_SourceCompo_LOCAL.idl \
	SimpleStream_SourceCompo_EQUIVALENT.idl \
	SimpleStream_SourceCompo_BUSINESS.idl 

CPP_FILES = SimpleStream_SourceCompo_BUSINESS.cpp \
	SimpleStream_SourceCompo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimpleStream_SourceCompo.so SimpleStream_SourceCompo.zip

LIBS += -L../SimpleStream_SourceCompo_SERVANT -lSimpleStream_SourceCompo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimpleStream_SourceCompo.so 

libSimpleStream_SourceCompo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:SimpleStream/SourceCompo:1.0" $< 

SimpleStream_SourceCompo_BUSINESS.cpp: SimpleStream_SourceCompo_EQUIVALENT.h SimpleStream_SourceCompo_LOCAL.h 

SimpleStream_SourceCompo.cpp: SimpleStream_SourceCompo_BUSINESS.h

package: SimpleStream_SourceCompo.zip

SimpleStream_SourceCompo.zip : meta-inf/SimpleStream_SourceCompo.ccd meta-inf/SimpleStream_SourceCompo.csd libSimpleStream_SourceCompo.so
	zip SimpleStream_SourceCompo.zip -j ../SimpleStream_SourceCompo_SERVANT/libSimpleStream_SourceCompo_SERVANT.so libSimpleStream_SourceCompo.so $(CIDL_FILES)
	zip SimpleStream_SourceCompo.zip meta-inf/SimpleStream_SourceCompo.ccd meta-inf/SimpleStream_SourceCompo.csd

meta-inf/SimpleStream_SourceCompo.ccd meta-inf/SimpleStream_SourceCompo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:SimpleStream/SourceCompo:1.0" ../$(CIDL_FILES) )

