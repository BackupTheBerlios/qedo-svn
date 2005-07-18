ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_AuctioneerImpl_LOCAL.idl \
	auction_AuctioneerImpl_EQUIVALENT.idl

CPP_FILES = auction_AuctioneerImpl_EQUIVALENT.cpp \
	auction_AuctioneerImpl_EQUIVALENT_skel.cpp \
	auction_AuctioneerImpl_LOCAL.cpp \
	auction_AuctioneerImpl_SERVANT.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_AuctioneerImpl_SERVANT.so

CXXFLAGS += -I.

include ../MakeComponentVars

all: libauction_AuctioneerImpl_SERVANT.so

libauction_AuctioneerImpl_SERVANT.so: ${OBJ_FILES}

${IDL_FILES} auction_AuctioneerImpl_SERVANT.cpp: ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--servant --target "IDL:auction/AuctioneerImpl:1.0" $<

