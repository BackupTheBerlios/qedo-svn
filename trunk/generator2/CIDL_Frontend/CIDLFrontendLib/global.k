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
/* this section is copied into k.h */

    typedef enum {
        OTHER
    } entity_kind_T;

#define file cr_filename  /* used by error.k */
%}

%{ KC_UNPARSE
#ifdef _MSC_VER
#pragma warning ( once : 4049 )
#pragma warning ( once : 4112 )
#endif
#include "global.h"
%}

%{ HEADER

    struct prettyprint_S {
        int                   indent;
    };

    extern struct prettyprint_S prettyprint;
#include "unpk.h"

#include <CORBA.h>
#include <IFR.h>
#include <CIDL_Extension.h>

extern CIDL::CIDLRepository_ptr g_repository;
extern CORBA::ORB_ptr g_orb;
%}

%{
#ifndef _MSC_VER
#include <unistd.h>    /* read, write, close */
#else
#endif
#include <string.h>    /* strcat, strcmp, strcasecmp */
#include <fcntl.h>     /* O_* macros, open, creat */
#include <stdlib.h>
#include <stdio.h>


#include "options.h"
#include "version.h"
#include "error.h"

#include "cg_io.h"


struct prettyprint_S prettyprint;
cidl_specification Spec;
string current_prefix;
CIDL::CIDLRepository_ptr g_repository;
CORBA::ORB_ptr g_orb;

static char id[] UNUSED = "";

%}
