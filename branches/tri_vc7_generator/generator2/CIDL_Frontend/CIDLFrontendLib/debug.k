/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */ 
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/


%{
static char id[] UNUSED = "";
/* parts withib that definition are not generic, check it if you reuse
   this file
*/
#undef DEBUG_FUNCTIONS

#include "unpk.h"
#include <string.h>

int kc_debug = 0;
static int dg_unparse_indent=0;
static int dg_func=0;
static int dg_active=0;
static int dg_recurse=0;
static int dg_views[kc_last_uview] ;

/*
#define INIT         register char *sp = instring;
#define GETC()       (*sp++)
#define PEEKC()      (*sp)
#define UNGETC(c)    (--sp)
#define RETURN(c)    return c
#include <regexp.h> 
#define ESIZE 2048
*/
#include "error.h"


%}

%{ HEADER
#include "unpk.h"
%}

%{ KC_TYPES_HEADER
/* make a printer trace if 1 */
extern int kc_debug;

extern void debug_unparse();
extern void leave_debug_unparse();
extern void debug_function();


%}


/* for debugging change the internal values of these functions
   note, it works with our modified kc version only     */
void debug_unparse(char* s,char* o,uview v)
{
    if(dg_recurse && dg_active && dg_views[v]==0)
        dg_views[v]=1;
    if (kc_debug && dg_views[v]>0) {
        dg_active++;
        printf("%*s{ %s(%s,%s)\n",dg_unparse_indent%40,"",s,o,kc_uviews[v].name);
        dg_unparse_indent++;
    }
}

void leave_debug_unparse(uview v)
{
    if (kc_debug && dg_views[v]>0) {
        dg_unparse_indent--;
        printf("%*s}\n",dg_unparse_indent%40,"");
        dg_active--;
    }
}

void debug_function(char* s,char* f)
{
  if (kc_debug && dg_func && dg_active &&
        strcmp(s,"IntelliWrite") && strcmp(s,"MyPrinter")) {
      printf("%*sfunction: %s (file %s)\n",dg_unparse_indent%40,"",s,f);
  } 
}


%{
#if 0
#include "regexpr.h"
#endif
%}
bool
switch_debug(char* pattern)
{
#if 0
    struct re_pattern_buffer reg;
    char *error;
    int i;
    int negate=0;
    bool ret = false;
    if(*pattern =='!') {
        negate=1;
        pattern++;
    }

    reg.buffer=0;
    reg.translate=0;
    reg.allocated=0;
    re_set_syntax(RE_SYNTAX_AWK|RE_NO_GNU_EXTENSIONS);
    if((error=re_compile_pattern(pattern,strlen(pattern),&reg))) {
        Error("<msg>bad regular expression '%s':%s\n",pattern,error);
        return false;
    }

    if(re_match(&reg,"functions",9,0,0)>=0) {
        dg_func=1; ret=true;
    }
    if(re_match(&reg,"allfunctions",12,0,0)>=0) {
        dg_func=1; dg_active=1; ret=true;
    }
    if(re_match(&reg,"recurse",7,0,0)>=0) {
        dg_recurse=1; ret=true;
    }
    for(i=0;i<kc_last_uview;i++) {
        if (re_match(&reg,kc_view_names[i],strlen(kc_view_names[i]),0,0)>=0) {
            dg_views[i]=negate? -1:1;
            Warning("<msg>match '%s' with '%s'\n",pattern,kc_view_names[i]);
            ret = true;
        }
    }
    return ret;
#else
    return true;
#endif
}
