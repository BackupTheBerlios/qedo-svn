# Qedo - Quality of Service Enabled Distributed Objects
#
# http://www.qedo.org/
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

SUBDIRS = Simulation_PlaneImpl_SERVANT \
	Simulation_PlaneImpl \
	Simulation_RadarImpl_SERVANT \
	Simulation_RadarImpl \
	Simulation_SimulationServerImpl_SERVANT \
	Simulation_SimulationServerImpl \
	Simulation_TAPDisplayImpl_SERVANT \
	Simulation_TAPDisplayImpl


all: MakeComponentVars $(SUBDIRS:%=%-all)

clean: $(SUBDIRS:%=%-clean)


%-all: %
	$(MAKE) -C $< all


MakeComponentVars:
	cp ${QEDO}/etc/MakeComponentVars .

%-clean: %
	$(MAKE) -C $< clean

package:
	$(MAKE) -C Simulation_PlaneImpl package
	$(MAKE) -C Simulation_RadarImpl package
	$(MAKE) -C Simulation_SimulationServerImpl package
	$(MAKE) -C Simulation_TAPDisplayImpl package

assembly: package
	$(MAKE) -C sim_linux_assembly
