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
#include <CORBA.h>
#include <IFR.h>
#include <CIDL_Extension.h>

typedef CORBA::Any ANYTYPE;
typedef CORBA__::IRObject_ptr IROBJ;
%}


table_item : {
  // the IFRObject
  IROBJ irobj = CORBA__::IRObject::_nil();
  // expression value
  ANYTYPE value;
};

definition : {
  // the IFRObject
  IROBJ irobj = CORBA__::IRObject::_nil();
};

const_expression : {
  ANYTYPE value;
};
