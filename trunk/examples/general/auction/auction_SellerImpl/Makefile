ORB_IDL_INCLUDE = -I..

CIDL_FILES = ../seller.cidl
IDL_FILES = auction_SellerImpl_LOCAL.idl \
	    auction_SellerImpl_EQUIVALENT.idl \
	    auction_SellerImpl_BUSINESS.idl

CPP_FILES = auction_SellerImpl_BUSINESS.cpp \
				valuetypes.cpp \
            auction_SellerImpl.cpp

OBJ_FILES = ${CPP_FILES:%.cpp=%.o}

LIBS += -L../auction_SERVANT -lauction_SERVANT

CXXFLAGS += -I. -g

include ../MakeComponentVars

all: libauction_SellerImpl.so

libauction_SellerImpl.so: ${OBJ_FILES}

${IDL_FILES} valuetypes.cpp auction_SellerImpl.cpp : ${CIDL_FILES}
	${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \
	--business --target "IDL:auction/SellerImpl:1.0" $<

auction_SellerImpl_BUSINESS.cpp: auction_SellerImpl_EQUIVALENT.h auction_SellerImpl_LOCAL.h
