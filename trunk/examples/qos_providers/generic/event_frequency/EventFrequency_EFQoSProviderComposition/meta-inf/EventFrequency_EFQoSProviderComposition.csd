<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="EFQoSProviderComposition_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:EventFrequency/EFQoSProviderHome:1.0">
        <fileinarchive name="event_frequency.idl"/>
    </idl>

    <implementation id="UUID-01e7eb19-b096-4f41-b207-0f35c11ff6c8">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/EventFrequency_EFQoSProviderComposition.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libEventFrequency_EFQoSProviderComposition.so"/>
            <entrypoint>create_EFQoSProviderHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libEventFrequency_EFQoSProviderComposition_SERVANT.so"/>
            <entrypoint>create_EFQoSProviderHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
