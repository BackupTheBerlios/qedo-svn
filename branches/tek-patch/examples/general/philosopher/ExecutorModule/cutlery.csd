<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://cif.sourceforge.net/softpkg.dtd" >

<softpkg name="cutlery_softpkg" version="1,0">
  
    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author> <company>HU</company> </author>
    <description>the cutlery component implementation</description>
    <license href="http://www.foo.com/license.html" />
    <idl id="IDL:dinner/CutleryHome:1.0" ><fileinarchive name="philosophers.idl"/></idl>

    <implementation id="cutlery_win">
        <os name="Win2000" />
        <processor name="x86" />
        <compiler name="VC++" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtc.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="philosopherE.dll"/>
            <entrypoint>create_CutleryHomeE</entrypoint>
        </code>
    </implementation>

    <implementation id="cutlery_sol">
        <os name="solaris" />
        <compiler name="gcc" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="libjtc.so"/></dependency>
        <dependency type="DLL"><localfile name="libobd.so"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libCutleryExecutor.so"/>
            <entrypoint>create_CutleryHomeE</entrypoint>
        </code>
    </implementation>
    
</softpkg>
