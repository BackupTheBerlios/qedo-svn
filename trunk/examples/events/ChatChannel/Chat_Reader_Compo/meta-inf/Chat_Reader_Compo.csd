<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Reader_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatReaderHome:1.0">
        <fileinarchive name="chat.idl"/>
    </idl>

    <implementation id="UUID-d4eb84e6-9929-4d07-bc41-c973b1a1f9d5">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Reader_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libChat_Reader_Compo.so"/>
            <entrypoint>create_ChatReaderHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libChat_Reader_Compo_SERVANT.so"/>
            <entrypoint>create_ChatReaderHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
    
    <implementation id="UUID-464832FE-BCD5-4B0C-9FE9-50405E5F029A">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
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
