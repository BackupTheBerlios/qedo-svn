<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="PhilosopherImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:dinner/PhilosopherHome:1.0">
        <fileinarchive name="philosophers.cidl"/>
    </idl>

    <implementation id="UUID-865b0bf5-4409-4302-92c2-f9e10cda7750">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_PhilosopherImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libdinner_PhilosopherImpl.so"/>
            <entrypoint>create_PhilosopherHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libdinner_PhilosopherImpl_SERVANT.so"/>
            <entrypoint>create_PhilosopherHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
