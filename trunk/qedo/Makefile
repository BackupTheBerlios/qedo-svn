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

include MakeVars

SUBDIRS = ComponentIDL \
	  ComponentContainer \
	  ComponentInstaller \
	  ComponentServer \
	  ComponentServerActivator \
	  AssemblyFactory \
	  HomeFinder \
	  DeploymentClient

all: $(SUBDIRS:%=%-all)

.PHONY: install-dir

${exec_prefix}/bin:
	mkinstalldirs $@

$(exec_prefix)/etc:
	mkinstalldirs $@

$(exec_prefix)/lib:
	mkinstalldirs $@

$(exec_prefix)/include:
	mkinstalldirs $@

$(exec_prefix)/idl:
	mkinstalldirs $@

install-dir: ${exec_prefix}/bin $(exec_prefix)/etc $(exec_prefix)/lib $(exec_prefix)/include $(exec_prefix)/idl

install: install-dir $(SUBDIRS:%=%-install)

%-all: %
	make -C $< all

%-install: %
	make -C $< install
