ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_AuctioneerImpl_LOCAL.idl \
	auction_AuctioneerImpl_EQUIVALENT.idl \
	auction_AuctioneerImpl_BUSINESS.idl 

CPP_FILES = auction_AuctioneerImpl_BUSINESS.cpp \
	auction_AuctioneerImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_AuctioneerImpl.so auction_AuctioneerImpl.zip

LIBS += -L../auction_AuctioneerImpl_SERVANT -lauction_AuctioneerImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_AuctioneerImpl.so 

libauction_AuctioneerImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/AuctioneerImpl:1.0" $< 

auction_AuctioneerImpl_BUSINESS.cpp: auction_AuctioneerImpl_EQUIVALENT.h auction_AuctioneerImpl_LOCAL.h 

auction_AuctioneerImpl.cpp: auction_AuctioneerImpl_BUSINESS.h

package: auction_AuctioneerImpl.zip

auction_AuctioneerImpl.zip : meta-inf/auction_AuctioneerImpl.ccd meta-inf/auction_AuctioneerImpl.csd libauction_AuctioneerImpl.so
	zip auction_AuctioneerImpl.zip -j ../auction_AuctioneerImpl_SERVANT/libauction_AuctioneerImpl_SERVANT.so libauction_AuctioneerImpl.so $(CIDL_FILES)
	zip auction_AuctioneerImpl.zip meta-inf/auction_AuctioneerImpl.ccd meta-inf/auction_AuctioneerImpl.csd

meta-inf/auction_AuctioneerImpl.ccd meta-inf/auction_AuctioneerImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:auction/AuctioneerImpl:1.0" ../$(CIDL_FILES) )

