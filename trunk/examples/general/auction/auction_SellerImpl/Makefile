ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../auction.cidl

IDL_FILES = auction_SellerImpl_LOCAL.idl \
	auction_SellerImpl_EQUIVALENT.idl \
	auction_SellerImpl_BUSINESS.idl

CPP_FILES = auction_SellerImpl_BUSINESS.cpp \
	auction_SellerImpl.cpp \
	component_valuetypes.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

CLEAN_FILES = ${IDL_FILES} ${OBJ_FILES} libauction_SellerImpl.so auction_SellerImpl.zip

LIBS += -L../auction_SellerImpl_SERVANT -lauction_SellerImpl_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_SellerImpl.so

libauction_SellerImpl.so: ${OBJ_FILES}

${IDL_FILES} component_valuetypes.cpp : ${CIDL_FILES} 
	${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/SellerImpl:1.0" $< 

auction_SellerImpl_BUSINESS.cpp: auction_SellerImpl_EQUIVALENT.h auction_SellerImpl_LOCAL.h 

auction_SellerImpl.cpp: auction_SellerImpl_BUSINESS.h

package: auction_SellerImpl.zip

auction_SellerImpl.zip : meta-inf/auction_SellerImpl.ccd meta-inf/auction_SellerImpl.csd libauction_SellerImpl.so
	zip auction_SellerImpl.zip -j ../auction_SellerImpl_SERVANT/libauction_SellerImpl_SERVANT.so libauction_SellerImpl.so $(CIDL_FILES)
	zip auction_SellerImpl.zip meta-inf/auction_SellerImpl.ccd meta-inf/auction_SellerImpl.csd

meta-inf/auction_SellerImpl.ccd meta-inf/auction_SellerImpl.csd :
	[ -d meta-inf ] || mkdir ./meta-inf
	(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	-d --target "IDL:auction/SellerImpl:1.0" ../$(CIDL_FILES) )

