<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="PlaneImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Simulation/PlaneHome:1.0">
        <fileinarchive name="simdemo.cidl"/>
    </idl>

    <implementation id="UUID-A69A6DFA-9C18-402D-9195-163CA169C8DB">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_PlaneImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Simulation_PlaneImpl.dll"/>
            <entrypoint>create_PlaneHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Simulation_PlaneImpl_SERVANT.dll"/>
            <entrypoint>create_PlaneHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-c185735a-6a5f-461e-804b-6028fdd03d64">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_PlaneImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libSimulation_PlaneImpl.so"/>
            <entrypoint>create_PlaneHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libSimulation_PlaneImpl_SERVANT.so"/>
            <entrypoint>create_PlaneHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

</softpkg>
