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


%{ KC_UNPARSE
#include "options.h"
%}

%{
#define HAVE_getopt_h 1

#include <string.h>


#define HAVE_getopt_long
#include "getopt.h"

/* Format: {option[':']} where
   ':' is an option which expects an argument */
#define OPTIONS "d:D:hiI:o:s:SvVwx"


#ifdef HAVE_getopt_long
/* Format: { "long_option_name", arg, 0, 'short option' }
   arg: 0 - no argunemt
        1 - required argument
        2 - optional argument
   0 - yes, use 'short option' to map the long option
   'short option' the char of the short option
*/
static struct option long_opt[] = {
  { "debug-level", 1, 0, 'd' },
#if 0
  { "debug-view", 1, 0, 'D' },
#endif
  { "define", 1, 0, 'D' },
  { "information", 0, 0, 'i' },
  { "include-dir", 1, 0, 'I' },
  { "help", 0, 0, 'h' },
  { "code-dir", 1, 0, 'o' },
  { "statistics", 0, 0, 'S' },
  { "suffix", 1, 0, 's' },
  { "no-warnings", 0, 0, 'w' },
  { "version", 0, 0, 'V' },
  { "verbose", 0, 0, 'v' },
  { "no-exit", 0, 0, 'x' },
  { 0, 0, 0, 0 }
};

static int long_ind = 0;

#define getopt(argc, argv, opt) getopt_long(argc, argv, opt, long_opt, &long_ind)

#endif

#include "unpk.h"
#include "debug.h"
#include "version.h"

struct options_S options;

static char id[] UNUSED = "";

#ifdef WIN32
#include <windows.h>
#endif

%}

%{ HEADER
    typedef enum { no_coding, asn_coding } CodingType;

    struct options_S
    {
        char *  filename;
        char *  code_dir;
        char *  suffix;
        bool    debug;
        bool    no_unused;
        bool    statistics;
        bool    no_warnings;
        int     verbose;
        int     cr_print;
        int     dg_symtab;
        bool    ignore_errors;
        idl_name_list include_dirs;
        idl_name_list defines;
    };

extern struct options_S options;

/*** verbose levels, not implemented here (yet) ***/
#define V_NORMAL 0x1
#define V_SYMTAB 0x4
#define V_REFERENCES 0x8
#define V_UNRESOLVED 0x20
#define V_NOINTERNAL 0x800
#define V_HASH 0x8000

#ifdef YYDEBUG
extern int yydebug;
#endif
%}



static void 
print_help(char* prog)
{
  fprintf(stderr,"usage: %s { options } <IDL-file>\n\n",prog);
  exit(1);
}

void uprint(char* str)
{
#ifdef _WIN32
  char buf[200] ;
  assert(strlen(str)<200);
  CharToOem(str,buf);
  buf[strlen(str)] = '\0';
  fprintf(stderr, buf);
#else
  fprintf(stderr, str);
#endif
}


static void 
print_info(char* prog)
{
  uprint("Copyright (c) Qedo Team, Germany,\n");
  uprint("http://qedo.berlios.de\n");
}

static void 
print_usage(char* prog)
{
  int pos;
  const char *buff;
  static int called = 0;
  if (called) return;
  called = 1;
  fprintf(stderr, "usage: %s ", prog);
#ifdef HAVE_getopt_long
  fprintf( stderr,"\n");
  for( pos=0; long_opt[pos].name; pos++ ) {
    buff = long_opt[pos].has_arg
           ? (long_opt[pos].has_arg==1 ? "arg " : "[ arg ] ")
           : " ";
    fprintf( stderr, "\t\t[ -%c %s ] [ --%s %s ]\n",
       long_opt[pos].val, buff,
       long_opt[pos].name, buff
    );
  }
  fprintf( stderr, "\t\t[ file[.idl] ... ]\n");
#else
  for( buff=OPTIONS; *buff; ++buff ) {
    if ( buff[1] == ':' )
      fprintf(stderr, "[-%c arg] ", *buff++);
    else
      fprintf(stderr, "[-%c] ", *buff);
  }
  fprintf( stderr,"] [ file[.idl] ...]\n");
#endif
}


static void
print_views(char* prog_name,char option)
{
#ifndef KC_ORIGINAL
  int i;
  fprintf(stderr,"%s: use option -%c with views:\n",prog_name,option);
  for(i=1;i<kc_last_uview;i++) {
    fprintf(stderr,"\t%s\n",kc_uviews[i].name);
  }
#else
   fprintf(stderr,"%s: option -%c: sorry, no view references implemented\n",
           prog_name,option);
#endif
}


void 
ParseCommandLineOptions (int argc,char** argv)
{
    static char optstring[]=OPTIONS;
    int opt,i;
    int done=0;
    char *prog_name = argv[0] ;
    
    do {
        opt=getopt(argc,argv,optstring);
        /* fprintf(stderr,"opt %c opterr %d optarg %s optind %d\n",
            opt, opterr, optarg?optarg:"NULL", optind); */
        switch (opt)
        {
            case 'd': for(i=0;optarg[i] ;i++)
                      switch(optarg[i]) {
                        case '0': options.debug = true; break;
                        case '1': options.verbose |= V_NORMAL; break;
                        case '3': options.verbose |= V_SYMTAB; break;
                        case '4': options.verbose |= V_REFERENCES; break;
                        case 'o': 
#ifndef KC_ORIGINAL
                          if (optarg[1] == '?')
                          {
                            print_views(prog_name,'o');
                          } else
                          {
                            for (i=base_uview+1; i<kc_last_uview; i++) {
                              if (strcmp(optarg+1,kc_uviews[i].name) == 0) {
                                options.cr_print = i; i = 0; break;
                              }
                            }
                            if (i) {
                              fprintf(stderr,"%s: option -do view '%s' does not exists\n",
                                      prog_name, optarg);
                            } 
						  }
                          i = 0; optarg[1] = 0;
#else
                          fprintf(stderr,"%s: option -o not supported\n",prog_name);
#endif
                          break;
                        case 'y':
                          #ifdef YYDEBUG
                            { yydebug = 1; }
                          #else
                            fprintf(stderr,"%s: option -dy not supported\n",prog_name);
                          #endif
                          break;

						default:
                          fprintf(stderr,"wrong argument for option 'd',");
                        case '?':
                          fprintf(stderr,"use option 'd' with:\n");
                          fprintf(stderr,"\t0 turn on debug\n");
                          fprintf(stderr,"\t1 normal verbose level\n");
                          fprintf(stderr,"\t3 symbol table\n");
                          fprintf(stderr,"\t4 reference resolution\n");
                      }
                      break;
            case 'D': options.defines = Considl_name_list(Name(mkcasestring(optarg)), options.defines);
                      break;
            case 'i': print_info(prog_name);
                      break;
            case 'I': options.include_dirs->append(Name(mkcasestring(optarg)));
                      break;
            case 'S': options.statistics = true;
                      break;
            case 's': options.suffix = optarg;
                      break;
            case 'o': options.code_dir = optarg;
                      break;
            case 'w': options.no_warnings=options.no_warnings?false:true;/*negate*/
                      break;
            case 'V': fprintf( stderr, "IDL2IDL generator version %.2f\ncompiled at %s\non %s\nwith %s\n",__CIDL2CPP__,COMPILED_AT,COMPILED_ON,COMPILED_FLAGS);
                      break;
            case 'v': if(options.verbose) 
                        options.verbose=0;
                      else
                        options.verbose=V_NORMAL;
                      break;
            case EOF: switch(argc - optind) {
                        case 1 :
                          options.filename = argv[optind] ;
                          break;
                        case 0 : break;
                        default : fprintf(stderr,"%s: to many arguments\n",argv[0]);
                                  print_usage(prog_name);
                                  exit(1);
                      }
                      done=1;
                      break;
            case 'x': options.ignore_errors = true;
                      break;
            case 'h': print_help(prog_name);
                      break;
            default:  fprintf(stderr,"%s: Invalid command line option: %c\n",
                              argv[0],opt); 
            case '?': print_usage(prog_name);
                      exit(1);
        } /* switch */
    } while(!done);
} /* ParseCommandLineOption */


void
init_options()
{
    options.filename    = 0;
    options.code_dir       = ".";
    options.suffix       = "cxx";
    options.debug          = false;
    options.statistics=false;
    options.no_warnings=false;
    options.dg_symtab=0;
    options.ignore_errors=false;
    options.include_dirs=Nilidl_name_list();
    options.defines=Nilidl_name_list();
}
