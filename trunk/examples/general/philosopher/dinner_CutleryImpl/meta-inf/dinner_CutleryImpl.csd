<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CutleryImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:dinner/CutleryHome:1.0">
        <fileinarchive name="philosophers.cidl"/>
    </idl>

    <implementation id="UUID-5dfe42f5-f1f5-469d-97aa-9563b10f063f">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libdinner_CutleryImpl.so"/>
            <entrypoint>create_CutleryHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libdinner_CutleryImpl_SERVANT.so"/>
            <entrypoint>create_CutleryHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
    
    <implementation id="UUID-0A1FBCDC-D196-41F0-AAFE-8015C32C51A1">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="dinner_CutleryImpl.dll"/>
            <entrypoint>create_CutleryHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="dinner_CutleryImpl_SERVANT.dll"/>
            <entrypoint>create_CutleryHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
