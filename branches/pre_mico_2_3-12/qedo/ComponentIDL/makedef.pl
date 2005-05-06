#!/bin/perl
# **********************************************************************
#
# Copyright (c) 1999
# Object Oriented Concepts, Inc.
# Billerica, MA, USA
#
# All Rights Reserved
#
# **********************************************************************

$def = $ARGV[0];
shift @ARGV;
$lib = $ARGV[0];
shift @ARGV;
$dumpbin = "dumpbin /symbols @ARGV";

open(DUMP, "$dumpbin |")
    || die "Can't run `$dumpbin': $!.\n";

open(DEF, "> $def")
    || die "Can't open `$def': $!.\n";

# print DEF "LIBRARY $lib\n";	# Excluded to avoid this warning: Drive/Directory component ignored in "LIBRARY" statement
print DEF "EXPORTS\n";

while(<DUMP>)
{
    if(!/\bUNDEF\b/ && /\bExternal\b/)
    {
	s/^.*\|\s+//;
	split;
	$_ = $_[0];

	if(/\?/ && !/^\?\?_G/ && !/^\?\?_E/)
	{
	    print DEF "    $_\n";
	}
    }
}
