/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#include "PSSHelper.h"

namespace Qedo
{

string 
PSSHelper::convertPidToString( const Pid& rPid )
{
	string strPid;
	int iLength = rPid.length();

    for(int i=0; i<iLength; i++)
		strPid.push_back(rPid[i]);

	return strPid;
}

string 
PSSHelper::convertSpidToString( const ShortPid& rSpid )
{
	string strSpid;
	int iLength = rSpid.length();

    for(int i=0; i<iLength; i++)
		strSpid.push_back(rSpid[i]);

	return strSpid;
}

string 
PSSHelper::convertPidToString( const Pid* rPid )
{
	string strPid;
	int iLength = rPid->length();

    for(int i=0; i<iLength; i++)
		strPid.push_back((*rPid)[i]);

	return strPid;
}

string 
PSSHelper::convertSpidToString( const ShortPid* rSpid )
{
	string strSpid;
	int iLength = rSpid->length();

    for(int i=0; i<iLength; i++)
		strSpid.push_back((*rSpid)[i]);

	return strSpid;
}

void
PSSHelper::convertStringToPid( const char* szPid, Pid& rPid )
{
	int iLength = strlen(szPid);
	rPid.length(iLength);
	
	for(int i=0; i<iLength; i++)
		rPid[i] = szPid[i];
}

void
PSSHelper::convertStringToSpid( const char* szSpid, ShortPid& rSpid )
{
	int iLength = strlen(szSpid);
	rSpid.length(iLength);
	
	for(int i=0; i<iLength; i++)
		rSpid[i] = szSpid[i];
}

bool 
PSSHelper::comparePid(const Pid& rSrc, const Pid& rDest)
{
	string strSrc = convertPidToString(rSrc);
	string strDest = convertPidToString(rDest);

	if(strSrc.compare(strDest)==0)
        return TRUE;
	else
		return FALSE;
}

bool 
PSSHelper::compareShortPid(const ShortPid& rSrc, const ShortPid& rDest)
{
	string strSrc = convertSpidToString(rSrc);
	string strDest = convertSpidToString(rDest);

	if(strSrc.compare(strDest)==0)
        return TRUE;
	else
		return FALSE;
}

string 
PSSHelper::convertBool2String(bool bc)
{
	if(bc)
		return "true";
	else
		return "false";
	//(bc) ? return ("true") : return ("false");
}

}