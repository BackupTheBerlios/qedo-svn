ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../chat.cidl

IDL_FILES = Chat_Reader_Compo_LOCAL.idl \
	Chat_Reader_Compo_EQUIVALENT.idl \
	Chat_Reader_Compo_BUSINESS.idl 

CPP_FILES = Chat_Reader_Compo_BUSINESS.cpp \
	Chat_Reader_Compo.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libChat_Reader_Compo.so Chat_Reader_Compo.zip

LIBS += -L../Chat_Reader_Compo_SERVANT -lChat_Reader_Compo_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libChat_Reader_Compo.so 

libChat_Reader_Compo.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:Chat/Reader_Compo:1.0" $< 

Chat_Reader_Compo_BUSINESS.cpp: Chat_Reader_Compo_EQUIVALENT.h Chat_Reader_Compo_LOCAL.h 

Chat_Reader_Compo.cpp: Chat_Reader_Compo_BUSINESS.h

package: Chat_Reader_Compo.zip

Chat_Reader_Compo.zip : meta-inf/Chat_Reader_Compo.ccd meta-inf/Chat_Reader_Compo.csd libChat_Reader_Compo.so
	zip Chat_Reader_Compo.zip -j ../Chat_Reader_Compo_SERVANT/libChat_Reader_Compo_SERVANT.so libChat_Reader_Compo.so $(CIDL_FILES)
	zip Chat_Reader_Compo.zip meta-inf/Chat_Reader_Compo.ccd meta-inf/Chat_Reader_Compo.csd

meta-inf/Chat_Reader_Compo.ccd meta-inf/Chat_Reader_Compo.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:Chat/Reader_Compo:1.0" ../$(CIDL_FILES) )

