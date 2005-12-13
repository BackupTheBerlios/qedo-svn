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


%uview print_node;

%{
static char id[] UNUSED = "";
%}

UsesDcl
->[ print_node : "uses" ];

ProvidesDclN
->[ print_node : "provides" ];

PublishesDclN
->[ print_node : "publishes" ];

EmitsDclN
->[ print_node : "emits" ];

ConsumesDclN
->[ print_node : "consumes" ];

KeyN
->[ print_node : "key" ];

FactoryN
->[ print_node : "factory" ];

InterfaceN
->[ print_node : "interface" ];

StorageTypeN
->[ print_node : "storagetype" ];

AbstractStorageTypeN
->[ print_node : "abstract storagetype" ];

AbstractStorageHomeN
->[ print_node : "abstract storagehome" ];

ValueTypeN
->[ print_node : "valuetype" ];

OpN
->[ print_node : "operation" ];

TypeN
->[ print_node : "type" ];


GlobalName(ident_v)
->[ print_node : "::" ident_v ];

Considl_name_list(name_v,Nilidl_name_list())
->[ print_node : name_v ];

Considl_name_list(name_v,tail)
->[ print_node : tail "::" name_v ];

TableItem(nflag,name,*),
TableItemDcl(nflag,name)
->[ print_node : nflag " " name ];

StorageType(StorageTypeHeader(name_v,*,*),*)
->[ print_node : name_v->symtab_entry ];


