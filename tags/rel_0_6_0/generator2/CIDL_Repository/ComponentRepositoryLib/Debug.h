/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>

#ifdef __DEBUG__
#define DEBUG_OUTLINE(o) std::cout << o << std::endl;
#define DEBUG_OUT(o) std::cout << o;
#define DEBUG_ERRLINE(e) std::cerr << e << std::endl;
#define DEBUG_ERR(e) std::cerr << e;
#else
#define DEBUG_OUT(o) ;
#define DEBUG_OUTLINE(o) ;
#define DEBUG_ERR(e) ;
#define DEBUG_ERRLINE(e) ;
#endif


#endif

