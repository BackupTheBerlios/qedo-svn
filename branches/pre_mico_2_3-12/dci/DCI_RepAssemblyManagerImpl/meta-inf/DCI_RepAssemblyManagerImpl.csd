<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="RepAssemblyManagerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DCI/RepAssemblyManagerHome:1.0">
        <fileinarchive name="deployment.idl"/>
    </idl>
    
    <implementation id="UUID-EAE715D8-A6FE-44B5-B9CF-A6BD3287511A">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/DCI_RepAssemblyManagerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="DCI_RepAssemblyManagerImpl.dll"/>
            <entrypoint>create_RepAssemblyManagerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="DCI_SERVANT.dll"/>
            <entrypoint>create_RepAssemblyManagerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
