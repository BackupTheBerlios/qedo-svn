ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../simple_stream.cidl

IDL_FILES = SimpleStream_SinkCompo_LOCAL.idl \
	SimpleStream_SinkCompo_EQUIVALENT.idl \
	SimpleStream_SinkCompo_BUSINESS.idl 

CPP_FILES = SimpleStream_SinkCompo_BUSINESS.cpp \
	SimpleStream_SinkCompo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libSimpleStream_SinkCompo.so SimpleStream_SinkCompo.zip

LIBS += -L../SimpleStream_SinkCompo_SERVANT -lSimpleStream_SinkCompo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libSimpleStream_SinkCompo.so 

libSimpleStream_SinkCompo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:SimpleStream/SinkCompo:1.0" $< 

SimpleStream_SinkCompo_BUSINESS.cpp: SimpleStream_SinkCompo_EQUIVALENT.h SimpleStream_SinkCompo_LOCAL.h 

SimpleStream_SinkCompo.cpp: SimpleStream_SinkCompo_BUSINESS.h

package: SimpleStream_SinkCompo.zip

SimpleStream_SinkCompo.zip : meta-inf/SimpleStream_SinkCompo.ccd meta-inf/SimpleStream_SinkCompo.csd libSimpleStream_SinkCompo.so
	zip SimpleStream_SinkCompo.zip -j ../SimpleStream_SinkCompo_SERVANT/libSimpleStream_SinkCompo_SERVANT.so libSimpleStream_SinkCompo.so $(CIDL_FILES)
	zip SimpleStream_SinkCompo.zip meta-inf/SimpleStream_SinkCompo.ccd meta-inf/SimpleStream_SinkCompo.csd

meta-inf/SimpleStream_SinkCompo.ccd meta-inf/SimpleStream_SinkCompo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:SimpleStream/SinkCompo:1.0" ../$(CIDL_FILES) )

