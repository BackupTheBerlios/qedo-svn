ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_BidderImpl_LOCAL.idl \
	auction_BidderImpl_EQUIVALENT.idl \
	auction_BidderImpl_BUSINESS.idl 

CPP_FILES = auction_BidderImpl_BUSINESS.cpp \
	auction_BidderImpl.cpp \
	valuetypes.cpp 

OBJ_FILES = ${CPP_FILES:%.cpp=%.o} 

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_BidderImpl.so auction_BidderImpl.zip

LIBS += -L../auction_BidderImpl_SERVANT -lauction_BidderImpl_SERVANT 

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_BidderImpl.so 

libauction_BidderImpl.so: ${OBJ_FILES} 

${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/BidderImpl:1.0" $< 

auction_BidderImpl_BUSINESS.cpp: auction_BidderImpl_EQUIVALENT.h auction_BidderImpl_LOCAL.h 

auction_BidderImpl.cpp: auction_BidderImpl_BUSINESS.h

package: auction_BidderImpl.zip

auction_BidderImpl.zip : meta-inf/auction_BidderImpl.ccd meta-inf/auction_BidderImpl.csd libauction_BidderImpl.so
	zip auction_BidderImpl.zip -j ../auction_BidderImpl_SERVANT/libauction_BidderImpl_SERVANT.so libauction_BidderImpl.so $(CIDL_FILES)
	zip auction_BidderImpl.zip meta-inf/auction_BidderImpl.ccd meta-inf/auction_BidderImpl.csd

meta-inf/auction_BidderImpl.ccd meta-inf/auction_BidderImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:auction/BidderImpl:1.0" ../$(CIDL_FILES) )

