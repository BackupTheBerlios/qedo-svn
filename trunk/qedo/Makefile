Debug: ComponentIDL.Debug ComponentContainer.Debug AssemblyFactory.Debug DeploymentClient.Debug ComponentInstaller.Debug ComponentServer.Debug ComponentServerActivator.Debug


DeploymentClient.Debug: AssemblyFactory.Debug ComponentContainer.Debug ComponentIDL.Debug
	 make -C DeploymentClient Debug


ComponentContainer.Debug: ComponentIDL.Debug
	 make -C ComponentContainer Debug


ComponentInstaller.Debug: ComponentIDL.Debug
	 make -C ComponentInstaller Debug


ComponentServer.Debug: ComponentContainer.Debug ComponentIDL.Debug
	 make -C ComponentServer Debug


ComponentServerActivator.Debug: ComponentIDL.Debug
	 make -C ComponentServerActivator Debug


ComponentIDL.Debug: 
	 make -C ComponentIDL Debug


AssemblyFactory.Debug: ComponentIDL.Debug ComponentContainer.Debug
	 make -C AssemblyFactory Debug


Debug_orbacus_linux: ComponentIDL.Debug_orbacus_linux ComponentContainer.Debug_orbacus_linux AssemblyFactory.Debug_orbacus_linux DeploymentClient.Debug_orbacus_linux ComponentInstaller.Debug_orbacus_linux ComponentServer.Debug_orbacus_linux ComponentServerActivator.Debug_orbacus_linux


DeploymentClient.Debug_orbacus_linux: AssemblyFactory.Debug_orbacus_linux ComponentContainer.Debug_orbacus_linux ComponentIDL.Debug_orbacus_linux
	 mkdir -p DeploymentClient/Debug_orbacus_linux ;make -C DeploymentClient Debug_orbacus_linux


ComponentContainer.Debug_orbacus_linux: ComponentIDL.Debug_orbacus_linux
	 mkdir -p ComponentContainer/Debug_orbacus_linux ;make -C ComponentContainer Debug_orbacus_linux


ComponentInstaller.Debug_orbacus_linux: ComponentIDL.Debug_orbacus_linux
	 mkdir -p ComponentInstaller/Debug_orbacus_linux ;make -C ComponentInstaller Debug_orbacus_linux


ComponentServer.Debug_orbacus_linux: ComponentContainer.Debug_orbacus_linux ComponentIDL.Debug_orbacus_linux
	 mkdir -p ComponentServer/Debug_orbacus_linux ;make -C ComponentServer Debug_orbacus_linux


ComponentServerActivator.Debug_orbacus_linux: ComponentIDL.Debug_orbacus_linux
	 mkdir -p ComponentServerActivator/Debug_orbacus_linux; make -C ComponentServerActivator Debug_orbacus_linux


ComponentIDL.Debug_orbacus_linux: 
	 mkdir -p ComponentIDL/Debug_orbacus_linux; make -C ComponentIDL Debug_orbacus_linux


AssemblyFactory.Debug_orbacus_linux: ComponentIDL.Debug_orbacus_linux ComponentContainer.Debug_orbacus_linux
	 mkdir -p AssemblyFactory/Debug_orbacus_linux; make -C AssemblyFactory Debug_orbacus_linux

Debug_mico_linux: ComponentIDL.Debug_mico_linux ComponentContainer.Debug_mico_linux AssemblyFactory.Debug_mico_linux DeploymentClient.Debug_mico_linux ComponentInstaller.Debug_mico_linux ComponentServer.Debug_mico_linux ComponentServerActivator.Debug_mico_linux


DeploymentClient.Debug_mico_linux: AssemblyFactory.Debug_mico_linux ComponentContainer.Debug_mico_linux ComponentIDL.Debug_mico_linux
	 mkdir -p DeploymentClient/Debug_mico_linux ;make -C DeploymentClient Debug_mico_linux


ComponentContainer.Debug_mico_linux: ComponentIDL.Debug_mico_linux
	 mkdir -p ComponentContainer/Debug_mico_linux ;make -C ComponentContainer Debug_mico_linux


ComponentInstaller.Debug_mico_linux: ComponentIDL.Debug_mico_linux
	 mkdir -p ComponentInstaller/Debug_mico_linux ;make -C ComponentInstaller Debug_mico_linux


ComponentServer.Debug_mico_linux: ComponentContainer.Debug_mico_linux ComponentIDL.Debug_mico_linux
	 mkdir -p ComponentServer/Debug_mico_linux ;make -C ComponentServer Debug_mico_linux


ComponentServerActivator.Debug_mico_linux: ComponentIDL.Debug_mico_linux
	 mkdir -p ComponentServerActivator/Debug_mico_linux; make -C ComponentServerActivator Debug_mico_linux


ComponentIDL.Debug_mico_linux: 
	 mkdir -p ComponentIDL/Debug_mico_linux; make -C ComponentIDL Debug_mico_linux


AssemblyFactory.Debug_mico_linux: ComponentIDL.Debug_mico_linux ComponentContainer.Debug_mico_linux
	 mkdir -p AssemblyFactory/Debug_mico_linux; make -C AssemblyFactory Debug_mico_linux


Release: ComponentIDL.Release ComponentContainer.Release AssemblyFactory.Release DeploymentClient.Release ComponentInstaller.Release ComponentServer.Release ComponentServerActivator.Release


DeploymentClient.Release: AssemblyFactory.Release ComponentContainer.Release ComponentIDL.Release
	 make -C DeploymentClient Release


ComponentContainer.Release: ComponentIDL.Release
	 make -C ComponentContainer Release


ComponentInstaller.Release: ComponentIDL.Release
	 make -C ComponentInstaller Release


ComponentServer.Release: ComponentContainer.Release ComponentIDL.Release
	 make -C ComponentServer Release


ComponentServerActivator.Release: ComponentIDL.Release
	 make -C ComponentServerActivator Release


ComponentIDL.Release: 
	 make -C ComponentIDL Release


AssemblyFactory.Release: ComponentIDL.Release ComponentContainer.Release
	 make -C AssemblyFactory Release


