<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Writer_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatWriterHome:1.0">
        <fileinarchive name="chat.cidl"/>
    </idl>
    
    <implementation id="UUID-823583de-b0cf-4ea7-96eb-551ee57a6caf">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Writer_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Chat_Writer_Compo.dll"/>
            <entrypoint>create_ChatWriterHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Chat_Writer_Compo_SERVANT.dll"/>
            <entrypoint>create_ChatWriterHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
