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
#include "TableBuilder.h"
#include "PSDReader.h"
#include "QDDatabase.h"


namespace Qedo
{

bool 
TableBuilder::build( std::string descriptor, std::string path )
{
	QDDatabase pdb;
	PSDReader psd_reader;
	std::string strAll, strName, strSql, strConn;
	std::basic_string <char>::size_type idxBegin;

	// get the sql sentences to create tables
	std::list<std::string> lTable(psd_reader.readPSD( path+descriptor, path ));
	std::list<std::string>::iterator iter;
	
	// get database connection string
	strConn = psd_reader.getDBConn();
	
	// connect to database
	pdb.Init();
	if(!pdb.DriverConnect(strConn.c_str()))
	{
		std::cout << "Failed to connect to database!" << std::endl;
		return false;
	}

	for(iter=lTable.begin(); iter!=lTable.end(); iter++)
	{
		strAll = *iter;
		idxBegin = strAll.find("$$");
		
		strName.substr(0, idxBegin);
		strSql.substr(idxBegin+2, strAll.length()-idxBegin-1);
		
		// check whether table has been already created
		if(!pdb.IsTableExist(strName.c_str()))
			// if not, create it!
			if(!pdb.ExecuteSQL(strSql.c_str()))
			{
				std::cout << "Failed to build table in database!" << std::endl;
				return false;
			}
	}
	
	//close database
	pdb.close();

	return true;
}

}
