<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="ObserverImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DiningPhilosophers/ObserverHome:1.0">
        <fileinarchive name="dinner.cidl"/>
    </idl>
    
    <implementation id="UUID-5BE5DBAF-6667-4FF7-A579-0C7EFBDBF104">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_ObserverImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="dinner_ObserverImpl.dll"/>
            <entrypoint>create_ObserverHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="dinner_ObserverImpl_SERVANT.dll"/>
            <entrypoint>create_ObserverHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
