include MakeVars

ifeq ($(ORB), MICO_ORB)
TARGET = Debug_mico_linux
endif

all: componentidl componentcontainer assemblyfactory deploymentclient componentinstaller componentserver componentserveractivator homefinder

install: all
	sh distributeQedo.sh $(QEDO)

componentidl:
	mkdir -p ComponentIDL/$(TARGET) ; make -C ComponentIDL $(TARGET)

install: all

deploymentclient: AssemblyFactory ComponentContainer ComponentIDL
	 mkdir -p DeploymentClient/$(TARGET) ;make -C DeploymentClient $(TARGET)

componentcontainer: ComponentIDL
	 mkdir -p ComponentContainer/$(TARGET) ;make -C ComponentContainer $(TARGET)

componentinstaller: ComponentIDL
	 mkdir -p ComponentInstaller/$(TARGET) ;make -C ComponentInstaller $(TARGET)

componentserver: ComponentContainer ComponentIDL
	 mkdir -p ComponentServer/$(TARGET) ;make -C ComponentServer $(TARGET)

componentserveractivator: ComponentIDL
	 mkdir -p ComponentServerActivator/$(TARGET); make -C ComponentServerActivator $(TARGET)

assemblyfactory: ComponentIDL ComponentContainer
	 mkdir -p AssemblyFactory/$(TARGET); make -C AssemblyFactory $(TARGET)

homefinder: ComponentIDL
	 mkdir -p HomeFinder/$(TARGET) ;make -C HomeFinder $(TARGET)
