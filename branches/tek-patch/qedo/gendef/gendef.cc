/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

static char rcsid[] = "$Id: gendef.cc,v 1.1 2003/07/16 19:42:58 tom Exp $";


#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main(int argc,char** argv)
{
  if (argc < 4) {
	  cerr << "Usage: " << argv[0] << " <def-file-name> <dll-base-name> <obj-file> ...." << endl;
	  return 2;
  }

  string dumpbin = "dumpbin /SYMBOLS";
  int i = 3;

  for(;i<argc;) {
	  dumpbin += " ";
	  dumpbin += argv[i++];
  }

  FILE * dump; 
  
  if( (dump = _popen( dumpbin.c_str(),"r")) == NULL ) {
	  cerr << "could not popen dumpbin" << endl;
	  return 3;
  }

  ofstream def_file(argv[1]);

  def_file << "LIBRARY " << argv[2] << endl;
  def_file << "EXPORTS" << endl;

  i=0;
  while( !feof(dump)) {
	  char buf [65000]; 
	  
	  if( fgets( buf, 64999, dump ) != NULL ) {
		  if(!strstr(buf," UNDEF ") && strstr(buf," External ")) {
			  char *s = strchr(buf,'|') + 1;
			  while(*s == ' ' || *s == '\t') s++;
			  char *e=s;
			  while(*e != ' ' && *e != '\t' && *e != '\0' && *e!= '\n') e++;
			  *e = '\0';
			  if(strchr(s,'?')!=0 && strncmp(s,"??_G",4)!=0 && strncmp(s,"??_E",4)!=0) {
				  def_file << "    " << s << endl;
			  }
		  }
	  }
  }

  cout << dumpbin.c_str() << endl;
}
