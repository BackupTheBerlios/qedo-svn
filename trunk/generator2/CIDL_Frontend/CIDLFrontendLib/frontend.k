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
#include <errno.h>
#include <string>
#ifdef _MSC_VER
#include <io.h>
#define fdopen     _fdopen
#define open       _open
#define dup        _dup
#define dup2       _dup2
#define close      _close
#define O_WRONLY   _O_WRONLY
#define O_CREAT    _O_CREAT
#define O_TRUNC    _O_TRUNC
#else
#include <unistd.h>
#endif

#include "frontend.h"
#include "lexana.h"
#include "options.h"
#include "error.h"
#include "symtab.h"
#include "resolve_symtab.h"
#include "printer.h"
#include "cg_io.h"
#include "unpk.h"

#include "global.h"
#include <CORBA.h>
#include <IFR.h>
#include <CIDL_Extension.h>
#include <CIDLRepository_impl.h>

#ifdef ORBACUS
#include <JTC/JTC.h>
#endif 

#include "repository.h"
#include "resolve_symtab.h"
#include <iostream>

char *  global_input_file_name;

#if _WIN32
#define popen _popen
#endif
%}

%{ KC_TYPES_HEADER
#include <set>
#include <CORBA.h>
#include <CIDL_Extension.h>
typedef CIDL::CIDLRepository_ptr REPOSITORYOBJ;
%}

int
frontend_feed ( 
  int argc,
  char** argv,
  REPOSITORYOBJ repository )
{
  int i;
#ifdef WIN32
  std::string command = "CL -E -C ";
#else
  std::string command = "gcc -E --language=c ";
#endif
  std::string filename;

  g_orb = CORBA::ORB_init ( argc, argv );

  //
  // parse options
  //
  init_options();
  ParseCommandLineOptions(argc,argv);

  if (!options.filename)
  {
    filename = "";
  }
  else
  {
    filename = options.filename;
  }
  global_input_file_name = new char[filename.length() + 1];
  strcpy(global_input_file_name, filename.c_str());
  
  init_symtab();
  init_lexer(true);

  // defines
  foreach(name_v;idl_name_list options.defines)
  {
    command += (std::string)"-D" + name_v->get_name() + " ";
  }
  // include dirs
  foreach(name_v;idl_name_list options.include_dirs)
  {
    command += (std::string)"-I" + name_v->get_name() + " ";
  }
  command += filename;

  std::cout << "precompiling : " << command << std::endl;
  if ( !(yyin = popen( command.c_str(), "r")) ) {
    fprintf( stderr, "can not open input file <%s>\n", filename.c_str());
    return (2);
  }


  //
  // parse specification
  //

  i = yyparse();


  //
  // semantic analysis
  //

  if(!i){
    start_view(Spec,printer,my_symtab_ref);
  }

  if(get_errors()) {
    Error("<msg> %d syntax/semantic errors\n",get_errors());
    return get_errors()+1;
  }

  init_stack();

  g_repository = repository;

  // propagate the prefixes
  Spec->set_prefix(global_prefix);

  //
  // feed into repository
  //
  feed_class my_feed (repository);
  try {
    start_view (Spec, printer, my_feed);
  }
  catch (const CORBA::Exception& ex) {
    cerr << ex << endl;
    exit(1);
  }
  
  return options.ignore_errors ? 0 : get_errors();
}

%{
%}

void 
start_view(cidl_specification spec,printer_function p,uview v)
{
  if (options.verbose&V_NORMAL) Warning("<debug>start view '%v'\n",(uview_enum)v);
    spec->unparse(p,v);
  if (options.cr_print == v) {
    spec->print();
  }
}
