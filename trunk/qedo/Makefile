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


