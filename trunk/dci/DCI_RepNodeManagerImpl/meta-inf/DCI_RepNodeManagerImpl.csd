<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="RepNodeManagerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DCI/RepNodeManagerHome:1.0">
        <fileinarchive name="deployment.idl"/>
    </idl>
    
    <implementation id="UUID-2F9C6737-D25D-400C-9D4C-E21245D71F2F">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/DCI_RepNodeManagerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="DCI_RepNodeManagerImpl.dll"/>
            <entrypoint>create_RepNodeManagerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="DCI_SERVANT.dll"/>
            <entrypoint>create_RepNodeManagerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
