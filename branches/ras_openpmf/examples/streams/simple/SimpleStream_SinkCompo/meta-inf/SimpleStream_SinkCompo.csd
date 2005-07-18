<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="SinkCompo_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:SimpleStream/StreamSinkHome:1.0">
        <fileinarchive name="simple_stream.cidl"/>
    </idl>

    <implementation id="UUID-C77B2B02-DC72-48B0-BB12-C377B119798B">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/SimpleStream_SinkCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="SimpleStream_SinkCompo.dll"/>
            <entrypoint>create_StreamSinkHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="SimpleStream_SinkCompo_SERVANT.dll"/>
            <entrypoint>create_StreamSinkHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-b34081fe-9268-41a2-85f7-0167ef88c830">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/SimpleStream_SinkCompo.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libSimpleStream_SinkCompo.so"/>
            <entrypoint>create_StreamSinkHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libSimpleStream_SinkCompo_SERVANT.so"/>
            <entrypoint>create_StreamSinkHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
