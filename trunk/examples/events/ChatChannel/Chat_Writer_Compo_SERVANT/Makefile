ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../chat.cidl

IDL_FILES = Chat_Writer_Compo_LOCAL.idl \
	Chat_Writer_Compo_EQUIVALENT.idl

CPP_FILES = Chat_Writer_Compo_EQUIVALENT.cpp \
	Chat_Writer_Compo_EQUIVALENT_skel.cpp \
	Chat_Writer_Compo_LOCAL.cpp \
	Chat_Writer_Compo_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libChat_Writer_Compo_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libChat_Writer_Compo_SERVANT.so

libChat_Writer_Compo_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} Chat_Writer_Compo_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:Chat/Writer_Compo:1.0" $<

