<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="CutleryImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:DiningPhilosophers/ForkHome:1.0">
        <fileinarchive name="dinner.cidl"/>
    </idl>

    <implementation id="UUID-CC2EC6CB-D995-4580-B994-9435168EAA67">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="dinner_CutleryImpl.dll"/>
            <entrypoint>create_ForkHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="dinner_CutleryImpl_SERVANT.dll"/>
            <entrypoint>create_ForkHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

    <implementation id="UUID-cb134dfc-e678-4eca-8e45-305e2587a80b">
        <os name="linux" />
        <processor name="" />
        <compiler name="" version="" />
        <programminglanguage name="C++" />
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/dinner_CutleryImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="libdinner_CutleryImpl.so"/>
            <entrypoint>create_ForkHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="libdinner_CutleryImpl_SERVANT.so"/>
            <entrypoint>create_ForkHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>

</softpkg>
