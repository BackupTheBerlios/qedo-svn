ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../event_frequency.cidl

IDL_FILES = EventFrequency_EFQoSProviderComposition_LOCAL.idl \
	EventFrequency_EFQoSProviderComposition_EQUIVALENT.idl \
	EventFrequency_EFQoSProviderComposition_BUSINESS.idl 

CPP_FILES = EventFrequency_EFQoSProviderComposition_BUSINESS.cpp \
	EventFrequency_EFQoSProviderComposition.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libEventFrequency_EFQoSProviderComposition.so EventFrequency_EFQoSProviderComposition.zip

LIBS += -L../EventFrequency_EFQoSProviderComposition_SERVANT -lEventFrequency_EFQoSProviderComposition_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libEventFrequency_EFQoSProviderComposition.so 

libEventFrequency_EFQoSProviderComposition.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:EventFrequency/EFQoSProviderComposition:1.0" $< 

EventFrequency_EFQoSProviderComposition_BUSINESS.cpp: EventFrequency_EFQoSProviderComposition_EQUIVALENT.h EventFrequency_EFQoSProviderComposition_LOCAL.h 

EventFrequency_EFQoSProviderComposition.cpp: EventFrequency_EFQoSProviderComposition_BUSINESS.h

package: EventFrequency_EFQoSProviderComposition.zip

EventFrequency_EFQoSProviderComposition.zip : meta-inf/EventFrequency_EFQoSProviderComposition.ccd meta-inf/EventFrequency_EFQoSProviderComposition.csd libEventFrequency_EFQoSProviderComposition.so
	zip EventFrequency_EFQoSProviderComposition.zip -j ../EventFrequency_EFQoSProviderComposition_SERVANT/libEventFrequency_EFQoSProviderComposition_SERVANT.so libEventFrequency_EFQoSProviderComposition.so $(CIDL_FILES)
	zip EventFrequency_EFQoSProviderComposition.zip meta-inf/EventFrequency_EFQoSProviderComposition.ccd meta-inf/EventFrequency_EFQoSProviderComposition.csd

meta-inf/EventFrequency_EFQoSProviderComposition.ccd meta-inf/EventFrequency_EFQoSProviderComposition.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:EventFrequency/EFQoSProviderComposition:1.0" ../$(CIDL_FILES) )

