ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auctioneer.cidl
IDL_FILES = auction_AuctioneerImpl_LOCAL.idl \
	    auction_AuctioneerImpl_EQUIVALENT.idl \
	    auction_AuctioneerImpl_BUSINESS.idl

CPP_FILES = auction_AuctioneerImpl_BUSINESS.cpp \
				valuetypes.cpp \
            auction_AuctioneerImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../auction_SERVANT -lauction_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_AuctioneerImpl.so

libauction_AuctioneerImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp auction_AuctioneerImpl.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/AuctioneerImpl:1.0" $<

auction_AuctioneerImpl_BUSINESS.cpp: auction_AuctioneerImpl_EQUIVALENT.h auction_AuctioneerImpl_LOCAL.h
