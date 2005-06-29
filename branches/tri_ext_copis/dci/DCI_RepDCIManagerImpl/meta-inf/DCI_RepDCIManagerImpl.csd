<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="RepDCIManagerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DCI/RepDCIManagerHome:1.0">
        <fileinarchive name="deployment.idl"/>
    </idl>
    
    <implementation id="UUID-529D5220-0A8D-4469-9795-770CF78F0527">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/DCI_RepDCIManagerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="DCI_RepDCIManagerImpl.dll"/>
            <entrypoint>create_RepDCIManagerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="DCI_SERVANT.dll"/>
            <entrypoint>create_RepDCIManagerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
