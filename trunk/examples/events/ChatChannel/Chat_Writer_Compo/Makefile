ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../chat.cidl

IDL_FILES = Chat_Writer_Compo_LOCAL.idl \
	Chat_Writer_Compo_EQUIVALENT.idl \
	Chat_Writer_Compo_BUSINESS.idl 

CPP_FILES = Chat_Writer_Compo_BUSINESS.cpp \
	Chat_Writer_Compo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libChat_Writer_Compo.so Chat_Writer_Compo.zip

LIBS += -L../Chat_Writer_Compo_SERVANT -lChat_Writer_Compo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libChat_Writer_Compo.so 

libChat_Writer_Compo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Chat/Writer_Compo:1.0" $< 

Chat_Writer_Compo_BUSINESS.cpp: Chat_Writer_Compo_EQUIVALENT.h Chat_Writer_Compo_LOCAL.h 

Chat_Writer_Compo.cpp: Chat_Writer_Compo_BUSINESS.h

package: Chat_Writer_Compo.zip

Chat_Writer_Compo.zip : meta-inf/Chat_Writer_Compo.ccd meta-inf/Chat_Writer_Compo.csd libChat_Writer_Compo.so
	zip Chat_Writer_Compo.zip -j ../Chat_Writer_Compo_SERVANT/libChat_Writer_Compo_SERVANT.so libChat_Writer_Compo.so $(CIDL_FILES)
	zip Chat_Writer_Compo.zip meta-inf/Chat_Writer_Compo.ccd meta-inf/Chat_Writer_Compo.csd

meta-inf/Chat_Writer_Compo.ccd meta-inf/Chat_Writer_Compo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Chat/Writer_Compo:1.0" ../$(CIDL_FILES) )

