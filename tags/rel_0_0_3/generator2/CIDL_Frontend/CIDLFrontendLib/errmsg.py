#! /bin/env python
"""
This program parses the verbose bison output in order to extract the states
and their corresponding rules. For example, the snippet
state 258

    parameter_dcls  ->  '(' param_dcl_list . ')'   (rule 168)
    param_dcl_list  ->  param_dcl_list . ',' param_dcl   (rule 171)
is translated to a C array that has, at index 258, the string
"parameter_dcls  ->  '(' param_dcl_list . ')'\n"
"param_dcl_list  ->  param_dcl_list . ',' param_dcl\n"
This array, in turn, can be used for error reporting in the generated
bison parser.

This program is invoked with the name of the bison output foo.output.
It then generates a file foo-output.c

The following assumptions are made about the input:
- the individual state listings start at column 0 with "state"
- the rules inside a state have a "->" and end with (rule number)
"""

import sys,string,os,re

def usage():
    print "Usage:%s <y.output >errmsg.c" % sys.argv[0]
    sys.exit()

if len(sys.argv)!=1:
    usage()

# base,ext=os.path.splitext(sys.argv[1])
# if ext!=".output":
#     usage()

states={}
curstate=None

uses_escapes=0

#for l in open(sys.argv[1],"rt").readlines():
for l in sys.stdin.readlines():
    if l[:6]=="state " and l[6] in string.digits:
        curstate=string.atoi(l[6:])
        states[curstate]=[]
        continue
    if curstate is None:
        # we have not seen state 0, yet
        continue
    if string.find(l,"->")==-1:
        # inside a state, but this line is not a rule
        continue
    if string.find(l,"error")!=-1:
        # this is an error stabilization rule
        continue
    # Now we have a rule. Split off the rule
    l=string.strip(string.split(l,"(rule")[0])
    # the rule might contain funny characters. Not all are supported, here.
    if not uses_escapes:
	# Recent bison versions escape those characters themselves
	if string.find(l, '\\"')>=0:
	    uses_escapes = 1
	else:
	    l=re.sub('"','\\"',l)
    states[curstate].append(l)

#out=open(base+"-output.c","w")
out=sys.stdout
out.write("char *error_message[]={\n")

for i in xrange(0,max(states.keys())+1):
    if states.has_key(i):
        if len(states[i])>6:
            l=string.join(states[i][:6],"\\n")
            l=l+"\\n... more rules ..."
        else:
            l=string.join(states[i],"\\n")
        assert(len(l)<2048) #MSVC limitation
        out.write('"%s",\n' % l)
    else:
        out.write('"",\n');

out.write("0};\n");
out.close()
    
