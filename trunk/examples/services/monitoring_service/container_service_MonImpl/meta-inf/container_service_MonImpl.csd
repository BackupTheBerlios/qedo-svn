<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="MonImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:container_service/monitor_home:1.0">
        <fileinarchive name="monitoring_service.cidl"/>
    </idl>

    <implementation id="UUID-6173a5ee-17a4-43da-844f-35fbbd643b53">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/container_service_MonImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libcontainer_service_MonImpl.so"/>
            <entrypoint>create_monitor_homeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libcontainer_service_MonImpl_SERVANT.so"/>
            <entrypoint>create_monitor_homeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
