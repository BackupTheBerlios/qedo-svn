
include ../../MakeComponentVars

all: DCINodeManager_$(OS).zip

DCINodeManager_$(OS).zip: DCI_RepNodeManagerImpl
	zip DCINodeManager_$(OS).zip meta-inf/*
	zip DCINodeManager_$(OS).zip DCI_RepNodeManagerImpl.zip

DCI_RepNodeManagerImpl:
	$(MAKE) -C .. package
	cp ../DCI_RepNodeManagerImpl.zip .
