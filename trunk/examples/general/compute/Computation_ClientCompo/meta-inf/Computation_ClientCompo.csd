<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="ClientCompo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Computation/ClientHome:1.0">
        <fileinarchive name="compute.cidl"/>
    </idl>
    
    <implementation id="UUID-6222631A-DD06-4561-988F-BA45ECA7984A">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Computation_ClientCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Computation_ClientCompo.dll"/>
            <entrypoint>create_ClientHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Computation_ClientCompo_SERVANT.dll"/>
            <entrypoint>create_ClientHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
