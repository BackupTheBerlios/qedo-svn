include MakeVars

ifeq ($(ORB), MICO)
TARGET = Debug_mico_linux
endif

all: Componentidl ComponentContainer AssemblyFactory DeploymentClient ComponentInstaller ComponentServer ComponentServerActivator HomeFinder

Componentidl:
	mkdir -p ComponentIDL/$(TARGET) ; make -C ComponentIDL $(TARGET)

install: all

DeploymentClient: AssemblyFactory ComponentContainer ComponentIDL
	 mkdir -p DeploymentClient/$(TARGET) ;make -C DeploymentClient $(TARGET)

ComponentContainer: ComponentIDL
	 mkdir -p ComponentContainer/$(TARGET) ;make -C ComponentContainer $(TARGET)

ComponentInstaller: ComponentIDL
	 mkdir -p ComponentInstaller/$(TARGET) ;make -C ComponentInstaller $(TARGET)

ComponentServer: ComponentContainer ComponentIDL
	 mkdir -p ComponentServer/$(TARGET) ;make -C ComponentServer $(TARGET)

ComponentServerActivator: ComponentIDL
	 mkdir -p ComponentServerActivator/$(TARGET); make -C ComponentServerActivator $(TARGET)

x:
	echo $(TARGET)

AssemblyFactory: ComponentIDL ComponentContainer
	 mkdir -p AssemblyFactory/$(TARGET); make -C AssemblyFactory $(TARGET)

HomeFinder: ComponentIDL
	 mkdir -p HomeFinder/$(TARGET) ;make -C HomeFinder $(TARGET)
