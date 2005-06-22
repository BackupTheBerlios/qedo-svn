<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="GenericCreatorCompo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:dynamic_creation/GenericCreatorHome:1.0">
        <fileinarchive name="dynamic_creation.cidl"/>
    </idl>
    
    <implementation id="UUID-BE41ED16-2DCC-40D2-BE94-856F0A693B2C">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dynamic_creation_GenericCreatorCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="dynamic_creation_GenericCreatorCompo.dll"/>
            <entrypoint>create_GenericCreatorHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="dynamic_creation_GenericCreatorCompo_SERVANT.dll"/>
            <entrypoint>create_GenericCreatorHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
