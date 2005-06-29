<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="Writer_Compo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Chat/ChatWriterHome:1.0">
        <fileinarchive name="chat.idl"/>
    </idl>

    <implementation id="UUID-0ef50e60-f613-4e3e-91da-37c71d21c6c9">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Chat_Writer_Compo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libChat_Writer_Compo.so"/>
            <entrypoint>create_ChatWriterHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libChat_Writer_Compo_SERVANT.so"/>
            <entrypoint>create_ChatWriterHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
    
    <implementation id="UUID-FB1660B4-755D-4F58-ADE8-B7BF8FAAA497">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
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
