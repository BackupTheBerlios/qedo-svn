<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Reader_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatReaderHome:1.0">
        <fileinarchive name="chat.cidl"/>
    </idl>
    
    <implementation id="UUID-d95af665-7530-42e3-8c98-8b09a4cd0b75">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Reader_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Chat_Reader_Compo.dll"/>
            <entrypoint>create_ChatReaderHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Chat_Reader_Compo_SERVANT.dll"/>
            <entrypoint>create_ChatReaderHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
