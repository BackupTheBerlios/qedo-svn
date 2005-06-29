<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="SellerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:auction/Sellers:1.0">
        <fileinarchive name="auction.cidl"/>
    </idl>

    <implementation id="UUID-1927e659-e4dd-4237-8b2c-cb5ea349c96d">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/auction_SellerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libauction_SellerImpl.so"/>
            <entrypoint>create_SellersE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libauction_SellerImpl_SERVANT.so"/>
            <entrypoint>create_SellersS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
