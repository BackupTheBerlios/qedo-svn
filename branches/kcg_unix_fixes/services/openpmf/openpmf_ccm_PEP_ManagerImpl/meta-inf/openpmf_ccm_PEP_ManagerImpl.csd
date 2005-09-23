<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="PEP_ManagerImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>Rudolf Schreiner</name></author>
    <description>OpenPMF PEP</description>
    <license href="" />
    <idl id="IDL:openpmf_ccm/pep_manager_home:1.0">
        <fileinarchive name="openpmf_ccm.cidl"/>
    </idl>
    
    <implementation id="UUID-5432c43b-9ced-4524-b50d-3c37a88159f8">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/openpmf_ccm_PEP_ManagerImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libopenpmf_ccm_PEP_ManagerImpl.so"/>
            <entrypoint>create_pep_manager_homeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libopenpmf_ccm_PEP_ManagerImpl_SERVANT.so"/>
            <entrypoint>create_pep_manager_homeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
