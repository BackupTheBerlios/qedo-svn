ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../bidder.cidl
IDL_FILES = auction_BidderImpl_LOCAL.idl \
	    auction_BidderImpl_EQUIVALENT.idl \
	    auction_BidderImpl_BUSINESS.idl

CPP_FILES = auction_BidderImpl_BUSINESS.cpp \
				valuetypes.cpp \
            auction_BidderImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../auction_SERVANT -lauction_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_BidderImpl.so

libauction_BidderImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp auction_BidderImpl.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/BidderImpl:1.0" $<

auction_BidderImpl_BUSINESS.cpp: auction_BidderImpl_EQUIVALENT.h auction_BidderImpl_LOCAL.h
