ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../event_frequency.cidl

IDL_FILES = EventFrequency_EFQoSProviderComposition_LOCAL.idl \
	EventFrequency_EFQoSProviderComposition_EQUIVALENT.idl

CPP_FILES = EventFrequency_EFQoSProviderComposition_EQUIVALENT.cpp \
	EventFrequency_EFQoSProviderComposition_EQUIVALENT_skel.cpp \
	EventFrequency_EFQoSProviderComposition_LOCAL.cpp \
	EventFrequency_EFQoSProviderComposition_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libEventFrequency_EFQoSProviderComposition_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libEventFrequency_EFQoSProviderComposition_SERVANT.so

libEventFrequency_EFQoSProviderComposition_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} EventFrequency_EFQoSProviderComposition_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:EventFrequency/EFQoSProviderComposition:1.0" $<

