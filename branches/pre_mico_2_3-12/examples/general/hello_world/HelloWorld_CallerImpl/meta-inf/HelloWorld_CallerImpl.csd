<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CallerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title>Caller Component of the Hello World example</title>
    <author><name>Qedo Team</name></author>
    <description>This component calls the calle component.</description>
    <license href="" />
    <idl id="IDL:HelloWorld/CallerHome:1.0">
        <fileinarchive name="hello.cidl"/>
    </idl>

    <implementation id="UUID-84628f02-c896-42ca-9644-6cdc0f88e017">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/HelloWorld_CallerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libHelloWorld_CallerImpl.so"/>
            <entrypoint>create_CallerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libHelloWorld_CallerImpl_SERVANT.so"/>
            <entrypoint>create_CallerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
    
    <implementation id="UUID-CDE9D487-2CFA-4E66-88EF-B21EA2F40E0D">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/HelloWorld_CallerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="HelloWorld_CallerImpl.dll"/>
            <entrypoint>create_CallerHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="HelloWorld_CallerImpl_SERVANT.dll"/>
            <entrypoint>create_CallerHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>    
</softpkg>
