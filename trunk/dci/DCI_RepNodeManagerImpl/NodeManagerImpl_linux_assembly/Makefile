
include ../../MakeComponentVars

all: DCINodeManager_$(OS).zip

DCINodeManager_$(OS).zip: DCI_RepNodeManagerImpl
	zip DCINodeManager_$(OS).zip meta-inf/DCINodemanager.cad meta-inf/DCI_RepNodeManagerImpl.cpf
	zip DCINodeManager_$(OS).zip DCI_RepNodeManagerImpl.zip

DCI_RepNodeManagerImpl:
	rm -f ../DCI_RepNodeManagerImpl.zip
	$(MAKE) -C .. package
	cp ../DCI_RepNodeManagerImpl.zip .
