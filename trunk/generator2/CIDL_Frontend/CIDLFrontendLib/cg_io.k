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
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include "lexana.h"

typedef enum comment { 
    comment_C=0,
    comment_Makefile=1,
    comment_None=2,
    comment_H=3
} comment_t;


/* this structure represents the actual file which is used by the
   printer functions
*/
struct outfile_S {
    char      name [256] ;           /* name of the file                */
    char      new_name [256] ;       /* temporare name                  */
    FILE*     handle;               /* file descriptor                 */
    unsigned long pos;                  /* temporare position mark         */
    long      empty_mark;           /* position after header stuff     */
    bool      changed;              /* real new code                   */
    bool      backup;               /* create backup file flag         */
    output_file kc_node;            /* pointer to the enclosing phylum */
    int       ref_count;            /* reference counter               */
    comment_t type;                 /* file type                       */
    int       indent;               /* indent for that file */
};

typedef struct outfile_S kc_outfile_type;

/* the actual file used by the printers */
extern struct outfile_S outfile;

/* the kind of header which is written if the file is opend */
extern comment_t io_c_comment;

#include "cg_io.h"
%}

%{
static char id[] UNUSED = "";
struct outfile_S outfile;
static bool empty_definition_recorde = false;
static bool empty_definition = false;
static std::string empty_def;
static int empty_def_indent=0;
%}

%{ HEADER
#ifdef _MSC_VER
#include <io.h>
#ifndef TAO_ORB
#define mode_t int
#else
typedef unsigned short mode_t;
#endif
#define unlink _unlink
#define fchmod _fchmod
#define fileno _fileno
#define S_IFDIR _S_IFDIR
#define S_IRUSR _S_IREAD
#define S_IWUSR _S_IWRITE
#define S_IXUSR _S_IEXEC
#define S_IFREG _S_IFREG
#define O_RDONLY _O_RDONLY
#define stat _stat
#endif
%}

/* Define an output file stack: 
     - each file is represented one and only one as element (uniq)
     - an existing file is initilized readonly
     - write initialization is done (if the file does not exist)
       with an temporary file (new_name)
*/
output_file {uniq} :
    OutputFile( casestring )
{ kc_outfile_type attr;
  {
    with($0) {
      OutputFile(name) : {
        assert(strlen(name->name) < sizeof(outfile.name));
        strcpy(outfile.name, name->name);
        outfile.pos = 0L;
        outfile.ref_count = 0;
        outfile.indent = 0;
        outfile.changed = false;
        outfile.empty_mark = -1;

        /* On MSVC++, opening the code files binary is more correct
           and more efficient. On Unix, it does not harm. */
        outfile.handle = fopen (outfile.name, "rb");
        if (outfile.handle == NULL) {
          assert( strlen(outfile.name)+4 < sizeof outfile.new_name );
          strcat (strcpy (outfile.new_name, outfile.name), ".new");
          outfile.handle = fopen (outfile.new_name,"wb");
          if (outfile.handle == NULL) {
              fprintf(stderr,"ERROR: can't open file %s for writing\n",outfile.name);
              exit(-1);
          }
          outfile.changed = true;
        } else 
          outfile.new_name[0] = 0;
        PrintFileComment();
      }
      default : {}
    }

    outfile.kc_node=$0;
    $0->attr = outfile;
  }
};

file_stack : list output_file;


%{ KC_UNPARSE
#include "cg_io.h"
%}

/* some macros, and I need unpk.h for the printer args */
%{ HEADER
#include "unpk.h"

#define Print(str) MyPrinter (str, base_uview)
#define Print2(s1, s2) Print (s1), Print (s2)
#define Print3(s1, s2, s3) Print2 (s1, s2), Print (s3)
#define Print4(s1, s2, s3, s4) Print2 (s1, s2), Print2 (s3, s4)
#define Print5(s1, s2, s3, s4, s5) Print2 (s1, s2), Print3 (s3, s4, s5)

#define INDENT   prettyprint.indent ++;
#define UNINDENT prettyprint.indent --;
%}


%{
#ifndef _MSC_VER
#include <unistd.h>
#else
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "error.h"
#include "printer.h"
#include "options.h"

    /* kind of file header to generate */
    comment_t io_c_comment;

    /* list of all generated files */
    idl_name_list  gen_file_list = NULL;

    /* the output file stack, function interface! */
    static file_stack TheFileStack = NULL;
%}


/******************** stack managment ********************/

void
init_outfile(kc_outfile_type* val)
{
    /* the error handler and current output file name */
    *val->name = '\0';
    *val->new_name = '\0';
    val->handle = stderr;
    val->pos = 0L;
    val->empty_mark = -1L;
    val->changed = true;
    val->backup = false;
    val->kc_node = NULL;  /* Stack element */
    val->ref_count = 0;     /* no reference */
    val->indent = 0;     /* indent of 0*/
}

/* has to be called on start */
void
init_stack() 
{ init_outfile(&outfile); TheFileStack = Nilfile_stack(); }


/* Push: base name, extension of the file, kind of header to generate
   - get the first (actual) stack element, if exists
     outfile.kc_node -> push was used
     outfile.kc_node -> stack empty or push was not used (old file stuff)
   - save the current state of the output file, this is a structure
     copy for all stack elements with the same name, believe me!
   - the real push
   - set up the new file
   - the actual element is NOT in the stack
*/
void 
PushOutFile(const char* filename,const char* extension,comment_t c_comment )
{
  output_file new_outfile;
  output_file old_outfile;
  io_c_comment=c_comment;

  /* get the unique phylum of the current file */
  if (outfile.kc_node) 
    old_outfile = outfile.kc_node;
  else
    old_outfile=NULL;

  /* save the state of the current file */
  if(old_outfile) {
      assert( old_outfile);
      old_outfile->attr = outfile;
      /* save the old indent */
      old_outfile->attr.indent = prettyprint.indent;
      TheFileStack = Consfile_stack( old_outfile, TheFileStack);
  }

  /* set the new file */
  sprintf (outfile.name, "%s/%s.%s", options.code_dir, filename, extension);
  new_outfile = OutputFile(mkcasestring(outfile.name));
  assert(new_outfile);
  outfile = new_outfile->attr;
  outfile.ref_count++;
  outfile.type=c_comment;
  /* set the new indent */
  prettyprint.indent = outfile.indent;
  
  /* reopening of former closed file */
  if(outfile.handle == stderr) {
    fprintf(stderr,"ERROR: reopening of former closed file %s\n",outfile.name);
  }
}

/* pop only if pushed, no backward stuff...
   - take the first stack element
   - update the attributes, this is unique for all stack elements with the
     same name
   - do pop
*/
void 
PopOutFile()
{
  output_file old_outfile = outfile.kc_node;
  /* stack empty (init_outfile) or pop without push */
  assert(old_outfile);
  /* save the state of the current file */
  if (--(outfile.ref_count)<=0) {
    PrintFileEndComment();
    CloseOutFile();
  }

  old_outfile->attr = outfile;

  /* set the new file */
  with (TheFileStack) {
    Nilfile_stack() : { 
      init_outfile(&outfile);
    }
    Consfile_stack( new_outfile, stack ) : {
      TheFileStack = stack;
      outfile = new_outfile->attr;
  } }

  /* set the new indent */
  prettyprint.indent = outfile.indent;
}


/* print the header information, the function is called by the initialization
   of the unique outfile structure (kc attribute init) if the file
   is opened
*/
void 
PrintFileComment() {
  char buff[1024] ;
  char *s;
  switch(io_c_comment) {
    case comment_H :
      s=strrchr(outfile.name,'/');
      if(s) s++;
      else s=buff;
      strcpy(buff,s);
      s=buff;
      while(*s) {
        switch(*s) {
          case '.': *s= '_'; break;
          default :
            if(*s>='a' && *s<='z') {
              *s=toupper(*s);
            }
        }
        s++;
      }
      Print3 ("#ifndef _", buff, "_ \n");
      Print3 ("#define _", buff, "_ \n");
      break;
    case comment_C: 
      Print3 ("/* ===== ",strrchr(outfile.name,'/')+1, " ===== */\n\n");
      break;
    case comment_Makefile:
      Print3 ("# ===== ",strrchr(outfile.name,'/')+1, " =====\n\n");
    case comment_None:
    default: ;
  }
}



void 
PrintFileEndComment() {
  char buff[1024] ;
  char *s;
  switch(outfile.type) {
    case comment_H: 
      s=strrchr(outfile.name,'/');
      if(s) s++;
      else s=buff;
      strcpy(buff,s);
      s=buff;
      while(*s) {
        switch(*s) {
          case '.': *s= '_'; break;
          default :
            if(*s>='a' && *s<='z') {
              *s=toupper(*s);
            }
        }
        s++;
      }
      Print3 ("#endif /* _", buff, "_ */\n");
      break;
    case comment_None:
    default: ;
  }
}



/***************************************************************************
**
** Procedure definition
**     IntelliWrite
**
** Description
**     This procedure is used for all C++ source output. If the file to
**     write to does already exist, IntelliWrite first begins comparing
**     the desired output with the contents of the file. If there are no
**     differences, the file will remain unchanged and untouched. Thus it
**     will not be regarded as new by subsequent make calls. This shall
**     avoid recompilation of all generated C++ sources if only some of them
**     have changed due to minor changes in the SDL sources.
**
** Remarks
**     No other output procedures than this shall be called in the whole
**     code generator.
**
***************************************************************************/

%{
#include "global.h"
#include "util.h"

/* support to find positions of diffuse code with gdb */
char debug_name[4096] = "";
unsigned int  debug_pos = 0;
%}

void 
dummy() {}

static void 
IntelliWrite (const char* str,unsigned int len)
{
    static char buffer [4096] ;
    unsigned int i;

    assert (/*len>=0 &&*/ len <= strlen (str));
    if(debug_name[0] && outfile.pos >= debug_pos && !strcmp(outfile.name,debug_name)) dummy();
    if (outfile.changed)
    {
        /* write to the new outfile */
        i = fwrite (str, 1, len, outfile.handle);
        if (i != len) {
          static int count = 0;
          if (!count) Error("<debug>write error to file '%s', disk full?\n",
                            outfile.name);
          if (count++>10) {
            Error("<debug>to many write errors, stop!\n",0);
            exit(1);
        } }
        outfile.pos += len;
        return;
    }
    /* else */
    /* compare with the contents of the old outfile */
    assert (len < sizeof (buffer));
    i = fread (buffer, 1, len, outfile.handle);
    if (i == len && strncmp (str, buffer, len) == 0)
    {
        outfile.pos += len;
        return;
    }
    switch_outfile();
    IntelliWrite (str, len);
}

static void
switch_outfile()
{
  unsigned int i;
  static char buffer [4096] ;
  FILE* old_handle = outfile.handle;
  long l;
  OpenNewOutFile(true);
  l = fseek (old_handle, 0L, SEEK_SET);

  if (l != 0) InternalError (__FILE__, __LINE__);
  /* copy the old outfile to the new up to the current position */
  while (outfile.pos > sizeof (buffer)) {
    i = fread (buffer, 1, sizeof (buffer), old_handle);
    if (i != sizeof (buffer)) InternalError (__FILE__, __LINE__);
    i = fwrite (buffer, 1, sizeof (buffer), outfile.handle);
    if (i != sizeof (buffer)) InternalError (__FILE__, __LINE__);
    outfile.pos -= sizeof (buffer);
  }
  i = fread (buffer, 1, (unsigned) outfile.pos, old_handle);
  if (i != outfile.pos) InternalError (__FILE__, __LINE__);
  i = fwrite (buffer, 1, (unsigned) outfile.pos, outfile.handle);
  if (i != outfile.pos) InternalError (__FILE__, __LINE__);
  i = fclose (old_handle);
  if (i != 0) InternalError (__FILE__, __LINE__);
  outfile.pos = 0;
} /* IntelliWrite */



/****************** non stack file functions ********************/
static void 
OpenNewOutFile (bool backup)
{
    assert(strlen(outfile.name)>0);
    if (strlen(outfile.name)+5>=sizeof(outfile.new_name)) {
      Error("<impl>name '%s' exceeded file name limit %d, sorry - stop!\n",
            0,outfile.name,sizeof(outfile.new_name)-5);
      exit(-1);
    }
    strcat (strcpy (outfile.new_name, outfile.name), ".new");
    outfile.handle = fopen (outfile.new_name,"wb");
    if (outfile.handle == NULL) {
      perror("fopen");
      Error("<debug>cannot open file '%s' for writing - stop!\n",
            outfile.new_name);
      exit(-1);
    }
    outfile.changed = true;
    outfile.backup = backup;
} /* OpenNewOutFile */


static void 
CloseOutFile()
{
  int ret;
  if (outfile.handle && outfile.handle!=stdout && outfile.handle!=stderr) {
    /* it's not NULL, and it's not, stdout or stderr */
    if (!outfile.changed) {
      fread(&ret,1,1,outfile.handle);
      /* old file is equal to new file except additional lines */
      if (!feof(outfile.handle)) {
        switch_outfile();
    } }
    ret = fclose(outfile.handle);
    if (ret) {
      Error("<debug>error on close of file '%s'\n",
            outfile.changed?outfile.new_name:outfile.name);
      perror("fclose");
    }
    if (outfile.changed) {
      /* old file and new file differ */
      if (outfile.backup) {
        char* buf=new char [strlen( outfile.name)+5];
        sprintf(buf,"%s.bak",outfile.name);
        /* On NT, first remove the target file. */
        unlink(buf);
        rename(outfile.name, buf);
        delete [] buf;
        outfile.backup=false;
      }
      else
        unlink(outfile.name);
      ret = rename (outfile.new_name, outfile.name);
      if (ret != 0) {
        Error("<debug>unable to rename file '%s' to '%s'\n",
               outfile.new_name, outfile.name);
        perror("rename");
    } }
    if (outfile.empty_mark>=0 && ((unsigned long) outfile.empty_mark)==outfile.pos)
      unlink(outfile.name);
    else register_filename(outfile.name);
  }
  outfile.handle = stderr;
  outfile.changed = true;
} /* CloseOutFile */

void 
begin_empty_definition()
{
  empty_definition_recorde = true;
  empty_definition = true;
  empty_def_indent = prettyprint.indent;
}

void
end_empty_definition()
{
  empty_definition_recorde = false;
}

bool
is_empty_definition()
{
  return empty_definition;
}

void
finish_empty_definition()
{
  empty_definition = false;
  empty_def = "";
}

void 
MyPrinter (const char* str,uview v)
{
    unsigned indentation;
    static char spaces [] = "                                             ";
    static unsigned length_of_spaces = sizeof (spaces) - 1;
    static int length_of_line = 0;
    static bool last_line_was_empty = false;
    unsigned length;

#if defined(DEBUG_UNPARSE) || defined(DEBUG_FUNCTIONS)
    printer(str,v);
#endif

    length = strlen (str);
    if (length == 0)
        return;

    if(empty_definition_recorde) {
      empty_def += str;
      return;
    }

    if(empty_definition) {
      int ii = prettyprint.indent;
      prettyprint.indent = empty_def_indent;
      empty_definition = false;
      MyPrinter(empty_def.c_str(),v);
      prettyprint.indent = ii;
      empty_def = "";
    }

    /* else */
    if (length_of_line == 0)
    {
        if (str[0] == '\n')
        {
            if(length>1) {
                IntelliWrite (str, length);
                last_line_was_empty=false;
                return;
            }
            if (last_line_was_empty)
                /* do not allow two consecutive empty lines */
                return;
            last_line_was_empty = true;
        }
        else
            last_line_was_empty = false; /* now text is following */

        if(prettyprint.indent<0)
            Warning("<debug>negative indent\n",0);

        indentation = 4 * (
          prettyprint.indent<0 ? 0 : prettyprint.indent);
        length_of_line = indentation;
        if (indentation > 0)
        {
            while (indentation > length_of_spaces)
            {
                IntelliWrite (spaces, length_of_spaces);
                indentation -= length_of_spaces;
            }
            IntelliWrite (spaces, indentation);
        }
    }

    IntelliWrite (str, length);

    if (str [length - 1] == '\n')
    {
        length_of_line = 0;
        if (length >= 2 && str [length - 2] == '\n')
            last_line_was_empty = true;
    }
    else
        length_of_line += length;
} /* MyPrinter */

void 
PrintInt (int i)
{
    char int_string [32] ;
    sprintf (int_string, "%d", i);
    Print (int_string);
} /* PrintInt */


void 
DummyPrinter (const char* str,uview v)
{
    /* ERROR  this procedure should never be called */
} /* DummyPrinter */

void 
StderrPrinter (const char* str,uview v)
{
  if(str) {
    fprintf(stderr,"%s",str);
    fflush(stderr);
  }
}

void 
SetEmptyMark() 
{
}

void
SetMode(mode_t mode)
{
  if(outfile.handle && outfile.changed) {
#if !defined(_MSC_VER) && !defined(__MINGW32__)
    fchmod(fileno(outfile.handle),mode);
#endif
  }
}

/**************** file managment ******************/
static void
register_filename(char* name_v)
{
  static int code_dir_len = 0;
  if (!gen_file_list) {
    gen_file_list = Nilidl_name_list();
    if (options.code_dir)
      code_dir_len = strlen(options.code_dir)+1; /* the '/' */
  }
  gen_file_list = AddNameToSet(
    Name(mkcasestring(name_v+code_dir_len)),gen_file_list);
}

void
mk_gen_file_list(char* file)
{
  if (!gen_file_list) {
    Error("<impl>mk_gen_file_list: no file list\n");
    return;
  }
  PushOutFile(file,"",comment_None);
  foreach(Name(name_v); idl_name_list gen_file_list) {
    Print2(name_v->name,"\n");
  }
  PopOutFile();
}

/* error messages with generated code information */

void 
InternalError (char* srcfile,int srcline)
{
  Error("<internal>internal error in file %s, line %d\n",
         0,srcfile, srcline);
  Print3 ("\n", "/* CIDL: Internal error in file ", srcfile);
  Print (", line ");
  PrintInt (srcline);
  Print (" */\n");
} /* InternalError */

void 
InternalErrorNotImplemented (
  char * srcfile,
  int srcline,
  char * what,
  int view_1,
  abstract_phylum p)
{
  if(p) {
    if (view_1>=0) 
      Error("<impl>internal error in file %s, line %d, view %v: %s[%s] %s\n",
          0,srcfile,srcline,view_1,kc_PhylumInfo[p->phylum()].name,
          kc_OperatorInfo[p->prod_sel()].name,what);
    else 
      Error("<impl>internal error in file %s, line %d: %s[%s] %s\n",
          0,srcfile,srcline,kc_PhylumInfo[p->phylum()].name,
          kc_OperatorInfo[p->prod_sel()].name,what);
  }
  else {
    if (view_1>=0) 
      Error("<impl>internal error in file %s, line %d, view %v: %s\n",
          0,srcfile,srcline,view_1,what);
    else 
      Error("<impl>internal error in file %s, line %d: %s\n",
          0,srcfile,srcline,what);
  }
  Print3 ("\n", "/* CIDL: Internal error in file ", srcfile);
  Print (", line ");
  PrintInt (srcline);
  if(view_1>=0) {
    Print2(", view ",kc_uviews[view_1].name);
  }
  Print3(": ",what," */\n");
} /* InternalErrorNotImplemented */

bool
check_code_dir()
{
  struct stat buf;
  if (stat(options.code_dir,&buf)) {
    Error("<msg>access to code directory '%s' failed, system reports '%s'\n",
          options.code_dir,strerror(errno));
    return false;
  }
  if (!(buf.st_mode&S_IFDIR)) {
    Error("<msg>code directory '%s' is no directory\n",options.code_dir);
    return false;
  }
  if (!(buf.st_mode&(S_IRUSR|S_IWUSR)) && (buf.st_mode&S_IFDIR)) {
    Error("<msg>unable to read or write files in the code directory '%s'\n",
          options.code_dir);
    return false;
  }
  return true;
}


