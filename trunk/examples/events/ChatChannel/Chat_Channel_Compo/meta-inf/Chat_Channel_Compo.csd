<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Channel_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatChannelHome:1.0">
        <fileinarchive name="Chat_Channel_Compo.idl"/>
    </idl>
    
    <implementation id="UUID-ca763c38-e98b-48f9-9e86-6eb3269a8ab8">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Channel_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Chat_Channel_Compo.dll"/>
            <entrypoint>create_ChatChannelHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Chat_Channel_Compo_SERVANT.dll"/>
            <entrypoint>create_ChatChannelHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
