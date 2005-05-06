<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="AuctioneerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:auction/Auctioneers:1.0">
        <fileinarchive name="auction.cidl"/>
    </idl>

    <implementation id="UUID-7c2c2fe5-7bb7-4e89-bdca-14f5b37e15fe">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/auction_AuctioneerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libauction_AuctioneerImpl.so"/>
            <entrypoint>create_AuctioneersE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libauction_AuctioneerImpl_SERVANT.so"/>
            <entrypoint>create_AuctioneersS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
