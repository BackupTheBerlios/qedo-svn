ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_SellerImpl_LOCAL.idl \
	auction_SellerImpl_EQUIVALENT.idl

CPP_FILES = auction_SellerImpl_EQUIVALENT.cpp \
	auction_SellerImpl_EQUIVALENT_skel.cpp \
	auction_SellerImpl_LOCAL.cpp \
	auction_SellerImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_SellerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libauction_SellerImpl_SERVANT.so

libauction_SellerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} auction_SellerImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:auction/SellerImpl:1.0" $<

