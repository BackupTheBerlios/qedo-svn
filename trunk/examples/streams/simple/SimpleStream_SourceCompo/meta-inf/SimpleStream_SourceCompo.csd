<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="SourceCompo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:SimpleStream/StreamSourceHome:1.0">
        <fileinarchive name="simple_stream.cidl"/>
    </idl>
    
    <implementation id="UUID-F43174FD-986A-4BA5-9656-3D82F61C95FB">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/SimpleStream_SourceCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="SimpleStream_SourceCompo.dll"/>
            <entrypoint>create_StreamSourceHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="SimpleStream_SourceCompo_SERVANT.dll"/>
            <entrypoint>create_StreamSourceHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
