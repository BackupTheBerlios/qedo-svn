
include ../MakeComponentVars

all: sim_$(OS).zip

sim_$(OS).zip: Simulation_PlaneImpl.zip Simulation_RadarImpl.zip Simulation_SimulationServerImpl.zip Simulation_TAPDisplayImpl.zip meta-inf/sim_$(OS).cad
	zip sim_$(OS).zip Simulation_PlaneImpl.zip Simulation_RadarImpl.zip Simulation_SimulationServerImpl.zip Simulation_TAPDisplayImpl.zip meta-inf/sim_$(OS).cad meta-inf/plane1.cpf meta-inf/plane2.cpf meta-inf/radar1.cpf meta-inf/radar2.cpf meta-inf/tapdisplay1.cpf

Simulation_PlaneImpl.zip:
	cp ../Simulation_PlaneImpl/Simulation_PlaneImpl.zip .

Simulation_RadarImpl.zip:
	cp ../Simulation_RadarImpl/Simulation_RadarImpl.zip .

Simulation_SimulationServerImpl.zip:
	cp ../Simulation_SimulationServerImpl/Simulation_SimulationServerImpl.zip .

Simulation_TAPDisplayImpl.zip:
	cp ../Simulation_TAPDisplayImpl/Simulation_TAPDisplayImpl.zip .

