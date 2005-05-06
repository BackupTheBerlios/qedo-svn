<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="SimulationServerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Simulation/SimulationServerHome:1.0">
        <fileinarchive name="simdemo.cidl"/>
    </idl>

    <implementation id="UUID-F21017D0-7B20-4871-8F85-12F89B56B100">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_SimulationServerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Simulation_SimulationServerImpl.dll"/>
            <entrypoint>create_SimulationServerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Simulation_SimulationServerImpl_SERVANT.dll"/>
            <entrypoint>create_SimulationServerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-db269830-d1c7-4f43-9e02-5c75331f0dfe">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_SimulationServerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libSimulation_SimulationServerImpl.so"/>
            <entrypoint>create_SimulationServerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libSimulation_SimulationServerImpl_SERVANT.so"/>
            <entrypoint>create_SimulationServerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

</softpkg>
