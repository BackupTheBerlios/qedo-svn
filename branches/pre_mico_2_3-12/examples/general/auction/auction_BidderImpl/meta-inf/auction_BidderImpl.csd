<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="BidderImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:auction/Bidders:1.0">
        <fileinarchive name="auction.cidl"/>
    </idl>

    <implementation id="UUID-5a387a69-6010-40c5-a762-4e980c832b0d">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/auction_BidderImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libauction_BidderImpl.so"/>
            <entrypoint>create_BiddersE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libauction_BidderImpl_SERVANT.so"/>
            <entrypoint>create_BiddersS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
