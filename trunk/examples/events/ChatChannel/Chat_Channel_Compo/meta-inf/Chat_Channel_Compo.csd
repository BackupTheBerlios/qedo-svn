<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Channel_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatChannelHome:1.0">
        <fileinarchive name="chat.cidl"/>
    </idl>

    <implementation id="UUID-1d2ee222-9592-4819-996f-8cf90d65565b">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Channel_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libChat_Channel_Compo.so"/>
            <entrypoint>create_ChatChannelHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libChat_Channel_Compo_SERVANT.so"/>
            <entrypoint>create_ChatChannelHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
