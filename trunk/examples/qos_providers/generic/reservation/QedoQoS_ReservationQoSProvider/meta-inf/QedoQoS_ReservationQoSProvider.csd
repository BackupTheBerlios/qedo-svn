<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="ReservationQoSProvider_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:QedoQoS/ReservationHome:1.0">
        <fileinarchive name="reservation.cidl"/>
    </idl>
    
    <implementation id="UUID-75C14130-5525-4FD7-AB5D-A3EC110A596D">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/QedoQoS_ReservationQoSProvider.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="QedoQoS_ReservationQoSProvider.dll"/>
            <entrypoint>create_ReservationHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="QedoQoS_ReservationQoSProvider_SERVANT.dll"/>
            <entrypoint>create_ReservationHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
