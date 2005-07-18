
include ../MakeComponentVars

all: $(OS)_assembly.zip

$(OS)_assembly.zip: Computation_ClientCompo.zip Computation_ServerCompo.zip meta-inf/$(OS)_assembly.cad
	zip $(OS)_assembly.zip Computation_ClientCompo.zip Computation_ServerCompo.zip meta-inf/$(OS)_assembly.cad

Computation_ClientCompo.zip:
	cp ../Computation_ClientCompo/Computation_ClientCompo.zip .

Computation_ServerCompo.zip:
	cp ../Computation_ServerCompo/Computation_ServerCompo.zip .

