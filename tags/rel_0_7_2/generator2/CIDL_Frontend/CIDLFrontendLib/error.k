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

%{ KC_TYPES_HEADER
#ifdef _MSC_VER
#define strdup _strdup
#endif
%}

%{ HEADER

/* Error and warning functions with any phyla */
void Error (char *format, ...);
void Warning (char *format, ...);
%}

%{
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"
#include "printer.h"
#include "options.h"
#include "util.h"
#include "symtab.h"

int nr_errors=0;
int nr_warnings=0;
#define max_errors 30

/* Please, be careful adding new names here! */
char *error_types[] = {
  /* 0 */ "normal",
  /* 1 */ "internal",
  /* 3 */ "hub",
  /* 4 */ "impl",
  /* 5 */ "msg",
  /* 6 */ "debug",
  /* 8 */ "unused",
  0
};

static int no_error_print = 0;
static char id[] UNUSED = "";

%}

%{ HEADER
namespace kc {
typedef enum { normal, internal, hub, impl, msg, debug, 
               unused } error_types_t;
}
%}


void 
error_off() 
{ 
  no_error_print++;
}

void 
error_on() 
{ 
  if (no_error_print>0)
    no_error_print--;
  else {
    no_error_print = 0;
    Error("<msg>error_on called asymetric\n",0);
} }


error_types_t 
get_error_type(char** format)
{
  char *c,*type_string;
  int i;
  if (**format != '<') return normal;
  type_string = *format+1;
  for (c=type_string; *c && *c!= '>'; c++);
  if (!*c) {
    Error("<internal>get_error_type no closing '>'\n",0);
    return normal;
  }
  *c=0;
  *format = c+1;
  for(i=0; error_types[i] ; i++) 
    if (strcmp(error_types[i],type_string)==0) return (error_types_t)i;
  Error("<internal>get_error_type wrong format '%s'\n", 
         0, type_string);
  return normal;
}


void 
inc_errors() 
{
  nr_errors++;
  if (!options.ignore_errors && nr_errors>max_errors) {
    nr_errors = 0;
    Error("<msg>too many errors, bailing out\n");
    exit(1);
  }
}

void 
inc_warnings() 
{ 
  nr_warnings++; 
}

void 
error_stat()
{ 
  fprintf(stderr,"ERROR STATISTICS: %d errors; %d warnings\n",
          nr_errors, nr_warnings);
  if (!nr_errors) 
    fprintf(stderr,"Static semantics check succeeded for %s!\n",
            options.filename);
  else 
    fprintf(stderr,"Static semantics check failed for %s!\n",
            options.filename);
}

int 
get_errors() 
{
  return nr_errors;
}

%{
#define SCRATCH_LEN MSG_BUFF+1024

void 
Error( char *format, ...)
{
  int len;
  error_types_t err_type;
  abstract_phylum node;
  char *f,*new_format;
  char buff[SCRATCH_LEN] ;
  va_list vaArgs,vaArgs_new,vaArgs_print;

  va_start(vaArgs,format);
  va_start(vaArgs_new,format);

  format = new_format = strdup(format);
  err_type = get_error_type(&new_format);

  if (err_type==kc::internal && (options.verbose&V_NOINTERNAL)) {
    free(format); return; 
  }

  node = va_arg(vaArgs,abstract_phylum);

  switch(err_type) {
    case normal :
    case hub :
      if (no_error_print) return;
      if (!node) { 
        Error("<internal>Error (normal) has no path node\n",0);
      }
      fprintf(stderr,"\nerror:");
      inc_errors();
      break;
    case kc::internal :
      inc_errors();
      fprintf(stderr,"\ninternal error:\n");
      break;
    case impl :
      inc_errors();
      fprintf(stderr,"\nnot implemented:\n");
      break;
    case msg :
      if (no_error_print) return;
    case debug :
      vaArgs = vaArgs_new;
      node = 0;
      break;
    default : 
      Error("<internal>unsupported error type %d\n",0,err_type);
  }
  if (node ) {
    switch(node->phylum()) {
      case kc_phylum_idl_identifier :
      case kc_phylum_idl_name :
      case kc_phylum_table_item : {
        print_path(node);
        break;
      }
      default : {
      Error("<internal>unsupported node type %s\n",0,node->phylum_name());
      }
    }
  }

  vaArgs_print = vaArgs;
  init_msg_buf();
  for(f=new_format; *f;) {
    while (*f && *f++!='%'); /* skip to next % */
    switch(*f) {
      case '%': f++; break;
      case 'k':   /* kc node pretty printer */
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node) {
          Error("<internal>null argument for %%k format in Error(\"%s\",...)\n",
                0,format);
          return;
        } else {
          /* if the stack grows to lower adresses we have to use
             the temporary (vaArgs_new)
             else, e.g. hpux
          */
          if (vaArgs_new<vaArgs)
            *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
          else
            *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
          node->unparse(printer5, print_node);
        }
        put_msg_buf(0);
        break;
      case 'v':   /* kc view printer */
        if (sizeof(int) != sizeof(char*)) {
          *f = 'd';
          (void)va_arg(vaArgs,int);
        } else {
          int v;
          vaArgs_new = vaArgs;
          *f = 's';
          v = va_arg(vaArgs,int);
          if (vaArgs_new<vaArgs)
            *((const char**)vaArgs_new) = kc_uviews[v].name ;
          else
            *((const char**)vaArgs) = kc_uviews[v].name ;
        }
        break;
      case 's':   /* char string */
        (void)va_arg(vaArgs,char*);
        break;
      case 'X':   /* address value */
        (void)va_arg(vaArgs,void*);
        break;
      case 'c':   /* character value */
        //(void)va_arg(vaArgs,char);
        //break;
      case 'd':   /* integer value */
        (void)va_arg(vaArgs,int);
        break;
      case 't':   /* kc tree printer (tree to stdout) */
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node) {
          Error("<internal>null argument for %%k format in Error(\"%s\",...)\n",
                0,format);
          return;
        } else {
          /* info_tree(node); */ print(node);
        }
        /* if the stack grows to lower adresses we have to use
           the temporary (vaArgs_new)
           else, e.g. hpux
        */
        if (vaArgs_new<vaArgs)
          *((char**)vaArgs_new) = "";
        else
          *((char**)vaArgs) = "";
        break;
      case 'p':   /* table item path formatter */
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node)
          Error("<internal>null argument for %%p format in Error\n",0);
        else {
          switch(node->phylum()) {
            case kc_phylum_table_item:
              /* if the stack grows to lower adresses we have to use
                 the temporary (vaArgs_new)
                 else, e.g. hpux
              */
              if (vaArgs_new<vaArgs)
                *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
              else
                *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
              print_table_item_path((table_item)node);
              break;
            case kc_phylum_idl_name:
              /* if the stack grows to lower adresses we have to use
                 the temporary (vaArgs_new)
                 else, e.g. hpux
              */
              if (vaArgs_new<vaArgs)
                *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
              else
                *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
              printer4("file ",base_uview);
              ((idl_name)node)->filename->unparse(printer4,base_uview);
              printer4(", line ",base_uview);
              ((idl_name)node)->line->unparse(printer4,base_uview);
              break;
            default:
              Error("<internal>null argument for %%p format in Error\n",0);
              return;
          }
        }
        put_msg_buf(0);
        break;
      case 0 : break;  /* loop break */
      default:
        Error("<internal>wrong format string '%s'\n",0,format);
        return;
    }
  }

  len = vsprintf(buff, new_format, vaArgs_print);
  assert(len<=SCRATCH_LEN);
  free(format);
  va_end(vaArgs);

  if (err_type!=msg && err_type!=debug) {
    printer1("diagnostics:\n ",base_uview);
  } 
  printer7(buff,base_uview);

  free_msg_buf();
}

void 
Warning( char *format, ...)
{
  int i,len;
  error_types_t err_type;
  abstract_phylum node;
  char *f,*new_format;
  char buff[SCRATCH_LEN] ;
  va_list vaArgs,vaArgs_new,vaArgs_print;

  va_start(vaArgs,format);
  va_start(vaArgs_new,format);

  format = new_format = strdup(format);
  err_type = get_error_type(&new_format);
  
  if (err_type!=msg) {
    if (options.no_warnings) { free(format); return; }
  }
  if (err_type==kc::internal && (options.verbose&V_NOINTERNAL)) {
    free(format); return;
  }

  node = va_arg(vaArgs,abstract_phylum);

  switch(err_type) {
    case unused:
      if (options.no_unused) {
        free(format); return;
      }
      if (!node) {
        Error("<internal>Error (normal) has no path node\n",0);
      }
      inc_warnings();
      fprintf(stderr,"\nwarning:");
      break;
    case normal :
      if (no_error_print) return;
      if (!node) { 
        Error("<internal>Error (normal) has no path node\n",0);
      }
      inc_warnings();
      fprintf(stderr,"\nwarning:");
      break;
    case hub :
      if (no_error_print) return;
      inc_warnings();
      fprintf(stderr,"\nwarning, incompatible SITE tool feature:\n");
      break;
    case kc::internal :
      fprintf(stderr,"\ninternal warning:\n");
      break;
    case impl :
      fprintf(stderr,"\nnot implemented yet(ignored):\n");
      break;
    case msg :
      if (!options.verbose) { free(format); return; }
    case debug :
      if (no_error_print) return;
      vaArgs = vaArgs_new;
      node = 0;
      break;
    default : 
      Error("<internal>unsupported warning type %d\n",0,err_type);
  }

  if (node ) {
    switch(node->phylum()) {
      case kc_phylum_idl_identifier :
      case kc_phylum_idl_name :
      case kc_phylum_table_item : {
        print_path(node);
        break;
      }
      default : {
      Error("<internal>unsupported node type %s\n",0,node->phylum_name());
      }
    }
  }

  vaArgs_print = vaArgs;
  init_msg_buf();
  for(i=0,f=new_format; *f; i++) {
    while (1) {
      if (!*f) break;
      if (*f++!='%') continue;
      if (*f=='%') { f++; continue; }
      break;
    }
    switch(*f) {
      case 'k':
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node) 
          Error("<internal>null argument for %%k format in Error\n",0);
        else {
          /* if the stack grows to lower adresses we have to use
             the temporary (vaArgs_new)
             else, e.g. hpux
          */
          if (vaArgs_new<vaArgs)
            *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
          else
            *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
          node->unparse(printer5, print_node);
        }
        put_msg_buf(0);
        break;
      case 'v':
        if (sizeof(int) != sizeof(char*)) {
          *f = 'd';
          (void)va_arg(vaArgs,int);
        } else {
          int v;
          vaArgs_new = vaArgs;
          *f = 's';
          v = va_arg(vaArgs,int);
          if (vaArgs_new<vaArgs)
            *((const char**)vaArgs_new) = kc_uviews[v].name ;
          else
            *((const char**)vaArgs) = kc_uviews[v].name ;
        }
        break;
      case 's':
        (void)va_arg(vaArgs,char*);
        break;
      case 'c':
        //(void)va_arg(vaArgs,char);
        //break;
      case 'd':
        (void)va_arg(vaArgs,int);
        break;
      case 'X' :
        (void)va_arg(vaArgs,void*);
        break;
      case 't':
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node)
          Error("<internal>null argument for %%k format in Error\n",0);
        else {
          /* info_tree(node); */ print(node);
        }
        /* if the stack grows to lower adresses we have to use
           the temporary (vaArgs_new)
           else, e.g. hpux
        */
        if (vaArgs_new<vaArgs)
          *((char**)vaArgs_new) = "";
        else
          *((char**)vaArgs) = "";
        break;
      case 'p':   /* table item path formatter */
        *f = 's';
        vaArgs_new = vaArgs;
        node = va_arg(vaArgs,abstract_phylum);
        if (!node)
          Error("<internal>null argument for %%p format in Error\n",0);
        else {
          switch(node->phylum()) {
            case kc_phylum_table_item:
              /* if the stack grows to lower adresses we have to use
                 the temporary (vaArgs_new)
                 else, e.g. hpux
              */
              if (vaArgs_new<vaArgs)
                *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
              else
                *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
              print_table_item_path((table_item)node);
              break;
            case kc_phylum_idl_name:
              /* if the stack grows to lower adresses we have to use
                 the temporary (vaArgs_new)
                 else, e.g. hpux
              */
              if (vaArgs_new<vaArgs)
                *((char**)vaArgs_new) = get_msg_buf() + get_msg_pos();
              else
                *((char**)vaArgs) = get_msg_buf() + get_msg_pos();
              printer4("file ",base_uview);
              ((idl_name)node)->filename->unparse(printer4,base_uview);
              printer4(", line ",base_uview);
              ((idl_name)node)->line->unparse(printer4,base_uview);
              break;
            default:
              Error("<internal>null argument for %%p format in Error\n",0);
              return;
          }
        }
        put_msg_buf(0);
        break;
      case 0 : break; /* loop break */
      default:
        Error("<internal>wrong format string '%s'\n",0,new_format);
        return;
    }
  }

  len = vsprintf(buff, new_format, vaArgs_print);
  assert(len<=SCRATCH_LEN);

  free(format);
  va_end(vaArgs);

  if (err_type!=msg && err_type!=debug) {
    printer1("diagnostics:\n ",base_uview);
  }
  printer7(buff,base_uview);
  free_msg_buf();
}

%}


