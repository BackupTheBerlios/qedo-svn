# Qedo - Quality of Service Enabled Distributed Objects
#
# http://qedo.berlios.de/
#
# Copyright (C) 2002-2003 by the Qedo Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

.NOTPARALLEL:

SUBDIRS = auction_AuctioneerImpl_SERVANT \
	auction_AuctioneerImpl \
	auction_BidderImpl_SERVANT \
	auction_BidderImpl \
	auction_SellerImpl_SERVANT \
	auction_SellerImpl

all: MakeComponentVars $(SUBDIRS:%=%-all)

clean: $(SUBDIRS:%=%-clean)


%-all: %
	$(MAKE) -C $< all


MakeComponentVars:
	cp ${QEDO}/etc/MakeComponentVars .

%-clean: %
	$(MAKE) -C $< clean

package:
	$(MAKE) -C auction_AuctioneerImpl package
	$(MAKE) -C auction_BidderImpl package
	$(MAKE) -C auction_SellerImpl package

assembly: package
	$(MAKE) -C auction_Linux_assembly
