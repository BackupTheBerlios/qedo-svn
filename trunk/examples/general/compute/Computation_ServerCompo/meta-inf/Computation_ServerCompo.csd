<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="ServerCompo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Computation/ServerHome:1.0">
        <fileinarchive name="compute.cidl"/>
    </idl>
    
    <implementation id="UUID-D5BCA6EC-3759-41EC-9733-4CE717244A5C">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Computation_ServerCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Computation_ServerCompo.dll"/>
            <entrypoint>create_ServerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Computation_ServerCompo_SERVANT.dll"/>
            <entrypoint>create_ServerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
