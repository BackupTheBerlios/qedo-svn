<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CalleeImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title>Callee Component of the Hello World example</title>
    <author><name>Qedo Team</name></author>
    <description>This component is called by the caller component.</description>
    <license href="" />
    <idl id="IDL:HelloWorld/CalleeHome:1.0">
        <fileinarchive name="hello.cidl"/>
    </idl>

    <implementation id="UUID-e4bc061b-5ab8-494c-a21e-fab954876376">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/HelloWorld_CalleeImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libHelloWorld_CalleeImpl.so"/>
            <entrypoint>create_CalleeHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libHelloWorld_CalleeImpl_SERVANT.so"/>
            <entrypoint>create_CalleeHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
    
    <implementation id="UUID-80164643-3114-4A57-97D0-98BB773F869F">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/HelloWorld_CalleeImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="HelloWorld_CalleeImpl.dll"/>
            <entrypoint>create_CalleeHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="HelloWorld_CalleeImpl_SERVANT.dll"/>
            <entrypoint>create_CalleeHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
