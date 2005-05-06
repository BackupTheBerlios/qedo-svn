<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="RepositoryImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DCI/RepositoryHome:1.0">
        <fileinarchive name="deployment.idl"/>
    </idl>
    
    <implementation id="UUID-0ED2D963-FA1C-4558-BA04-10624A87AA38">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/DCI_RepositoryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="DCI_RepositoryImpl.dll"/>
            <entrypoint>create_RepositoryHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="DCI_SERVANT.dll"/>
            <entrypoint>create_RepositoryHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
