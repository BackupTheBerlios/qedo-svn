
include ../MakeComponentVars

all: auction_$(OS).zip

auction_$(OS).zip: auction_AuctioneerImpl.zip auction_BidderImpl.zip auction_SellerImpl.zip meta-inf/auction_$(OS).cad
	zip auction_$(OS).zip auction_AuctioneerImpl.zip \
	auction_BidderImpl.zip auction_SellerImpl.zip \
	meta-inf/auction_$(OS).cad

auction_AuctioneerImpl.zip :
	cp ../auction_AuctioneerImpl/auction_AuctioneerImpl.zip  .

auction_BidderImpl.zip :
	cp ../auction_BidderImpl/auction_BidderImpl.zip  .

auction_SellerImpl.zip :
	cp ../auction_SellerImpl/auction_SellerImpl.zip  .

