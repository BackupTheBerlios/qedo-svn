<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="TAPDisplayImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Simulation/TAPDisplayHome:1.0">
        <fileinarchive name="simdemo.cidl"/>
    </idl>

    <implementation id="UUID-B5256F81-D6C1-431E-B6E9-768AEFAB89C3">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_TAPDisplayImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Simulation_TAPDisplayImpl.dll"/>
            <entrypoint>create_TAPDisplayHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Simulation_TAPDisplayImpl_SERVANT.dll"/>
            <entrypoint>create_TAPDisplayHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-bebc9195-f0cb-4148-b62c-c7f5155890af">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_TAPDisplayImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libSimulation_TAPDisplayImpl.so"/>
            <entrypoint>create_TAPDisplayHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libSimulation_TAPDisplayImpl_SERVANT.so"/>
            <entrypoint>create_TAPDisplayHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

</softpkg>
