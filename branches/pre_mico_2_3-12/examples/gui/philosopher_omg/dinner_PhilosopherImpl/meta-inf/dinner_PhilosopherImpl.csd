<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="PhilosopherImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DiningPhilosophers/PhilosopherHome:1.0">
        <fileinarchive name="dinner.cidl"/>
    </idl>

    <implementation id="UUID-54CA2428-8A31-4E76-A7F8-8B17DA1F87AB">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_PhilosopherImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="dinner_PhilosopherImpl.dll"/>
            <entrypoint>create_PhilosopherHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="dinner_PhilosopherImpl_SERVANT.dll"/>
            <entrypoint>create_PhilosopherHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-b74aa0de-aa9a-412c-a6e6-1e1d009e16f3">
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
