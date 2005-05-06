ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_BidderImpl_LOCAL.idl \
	auction_BidderImpl_EQUIVALENT.idl

CPP_FILES = auction_BidderImpl_EQUIVALENT.cpp \
	auction_BidderImpl_EQUIVALENT_skel.cpp \
	auction_BidderImpl_LOCAL.cpp \
	auction_BidderImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_BidderImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libauction_BidderImpl_SERVANT.so

libauction_BidderImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} auction_BidderImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:auction/BidderImpl:1.0" $<

