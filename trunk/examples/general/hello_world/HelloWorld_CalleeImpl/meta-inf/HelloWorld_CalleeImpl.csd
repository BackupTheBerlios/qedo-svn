<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CalleeImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:HelloWorld/CalleeHome:1.0">
        <fileinarchive name="hello.cidl"/>
    </idl>

    <implementation id="HelleWorld_CalleeImpl-mico-linux-26-10-2003">
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
</softpkg>
