include MakeVars

ifeq ($(ORB), MICO)
TARGET = Debug_mico_linux
endif

ifeq ($(ORB), ORBACUS)
TARGET = Debug_orbacus_linux
endif

all: IFRidl ComponentRepositoryLib CIDLRepositoryLib CIDLFrontendLib CIDLGenerator

install: all
	mkdir -p $(QEDO)/bin ; cp ../../CIDL_Backend/CIDLGenerator/cidl_gen $(QEDO)/bin
ComponentRepositoryLib: IFRidl
	mkdir -p ../../CIDL_Repository/ComponentRepositoryLib/$(TARGET); make -C ../../CIDL_Repository/ComponentRepositoryLib $(TARGET)


CIDLRepositoryLib: ComponentRepositoryLib
	 mkdir -p ../../CIDL_Repository/CIDLRepositoryLib/$(TARGET); make -C ../../CIDL_Repository/CIDLRepositoryLib $(TARGET)


IFRidl: 
	 mkdir -p ../../CIDL_Repository/IFRidl/$(TARGET); make -C ../../CIDL_Repository/IFRidl $(TARGET)


CIDLFrontendLib: IFRidl
	 mkdir -p ../../CIDL_Frontend/CIDLFrontendLib/$(TARGET); make -C ../../CIDL_Frontend/CIDLFrontendLib $(TARGET)


CIDLGenerator: CIDLRepositoryLib CIDLFrontendLib ComponentRepositoryLib
	 mkdir -p ../../CIDL_Backend/CIDLGenerator/$(TARGET); make -C ../../CIDL_Backend/CIDLGenerator $(TARGET)






