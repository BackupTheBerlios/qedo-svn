<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CalleeImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:HelloWorld/CalleeHome:1.0">
        <fileinarchive name="HelloWorld_CalleeImpl.idl"/>
    </idl>
    
    <implementation id="UUID-">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="HelloWorld_CalleeImpl.ccd" />
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
