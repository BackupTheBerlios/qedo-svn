ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../chat.cidl

IDL_FILES = Chat_Channel_Compo_LOCAL.idl \
	Chat_Channel_Compo_EQUIVALENT.idl \
	Chat_Channel_Compo_BUSINESS.idl

CPP_FILES = Chat_Channel_Compo_BUSINESS.cpp \
	Chat_Channel_Compo.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libChat_Channel_Compo.so Chat_Channel_Compo.zip

LIBS += -L../Chat_Channel_Compo_SERVANT -lChat_Channel_Compo_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libChat_Channel_Compo.so

libChat_Channel_Compo.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Chat/Channel_Compo:1.0" $< 

Chat_Channel_Compo_BUSINESS.cpp: Chat_Channel_Compo_EQUIVALENT.h Chat_Channel_Compo_LOCAL.h 

Chat_Channel_Compo.cpp: Chat_Channel_Compo_BUSINESS.h

package: Chat_Channel_Compo.zip

Chat_Channel_Compo.zip : meta-inf/Chat_Channel_Compo.ccd meta-inf/Chat_Channel_Compo.csd libChat_Channel_Compo.so
	zip Chat_Channel_Compo.zip -j ../Chat_Channel_Compo_SERVANT/libChat_Channel_Compo_SERVANT.so libChat_Channel_Compo.so $(CIDL_FILES)
	zip Chat_Channel_Compo.zip meta-inf/Chat_Channel_Compo.ccd meta-inf/Chat_Channel_Compo.csd

meta-inf/Chat_Channel_Compo.ccd meta-inf/Chat_Channel_Compo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Chat/Channel_Compo:1.0" ../$(CIDL_FILES) )

