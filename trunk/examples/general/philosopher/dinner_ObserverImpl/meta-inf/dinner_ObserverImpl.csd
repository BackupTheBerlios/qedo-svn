<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="ObserverImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:dinner/ObserverHome:1.0">
        <fileinarchive name="philosophers.cidl"/>
    </idl>

    <implementation id="UUID-cc5098df-3175-4552-b033-bf14d16d7e09">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_ObserverImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libdinner_ObserverImpl.so"/>
            <entrypoint>create_ObserverHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libdinner_ObserverImpl_SERVANT.so"/>
            <entrypoint>create_ObserverHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
