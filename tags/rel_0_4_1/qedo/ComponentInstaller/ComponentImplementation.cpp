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

#include "ComponentImplementation.h"
#include "CSDReader.h"


static char rcsid[] UNUSED = "$Id: ComponentImplementation.cpp,v 1.14 2003/09/09 17:34:51 boehme Exp $";


namespace Qedo {


ComponentImplementation::ComponentImplementation
(ComponentImplementationData data, std::string installationDirectory, std::string package)
{
	data_ = data;
	build_dir_ = installation_path_ + "build";
	build_path_ = getPath(build_dir_);
	installation_dir_ = getPath(installationDirectory) + data.uuid;
	installation_path_ = getPath(installation_dir_);
	package_ = package;
	installation_count_ = 0;
}


ComponentImplementation::ComponentImplementation (ComponentImplementationData data)
{
	data_=data;
	installation_count_=1;
}


ComponentImplementation::~ComponentImplementation
()
{
}


bool
ComponentImplementation::operator == 
( ComponentImplementation id )
{
    if (data_.uuid == id.data_.uuid) 
	{
        return true;
	}

	return false;
}


bool
ComponentImplementation::install ()
{
    //
	// if already installed increment counter only
	//
	if (installation_count_)
	{
		installation_count_++;
		return true;
	}

	//
	// create directories for the component implementation
	//
	makeDir(installation_dir_);
    makeDir(build_dir_);

	//
	// get info from the software package
    //
	CSDReader reader;
	try 
	{
		reader.readCSD( package_, &data_, build_path_ );
	}
	catch( CSDReadException ) 
	{
		removeFileOrDirectory(installation_dir_);
		removeFileOrDirectory(build_dir_);
        return false;
	}

    //
	// install code for servants and executors
	//
    try	
	{
		installCode();
	}
	catch( Components::CreateFailure )
	{
		removeFileOrDirectory(installation_dir_);
		removeFileOrDirectory(build_dir_);
        return false;
	}

	// increment installation counter ( to 1 )
	installation_count_++;

	return true;
}


bool 
ComponentImplementation::uninstall()
{
    installation_count_--;

	if (installation_count_ == 0) 
	{
		//
		// remove installed code
		//
		removeFileOrDirectory(installation_dir_);
	}

	return true;
}


void
ComponentImplementation::installCode()
throw(Components::CreateFailure)
{
	//
	// install valuetype factories
	//
	std::string code;
	std::string installation;
	std::vector < ValuetypeData >::iterator value_iter;
	for(value_iter = data_.valuetypes.begin();
		value_iter != data_.valuetypes.end();
		value_iter++)
	{
		code = (*value_iter).location.file;
		installation = installation_path_ + getFileName(code);
		if (copyFile(code, installation) == 0) 
		{
			std::cerr << "Error during installing valuetype factory " << code << std::endl;
			throw Components::CreateFailure();
		}
		(*value_iter).location.file = installation;
	}

	//
	// install artifacts
	//
	std::vector < std::string >::iterator iter;
	for (iter = data_.artifacts.begin(); 
		iter != data_.artifacts.end();
		iter++)
	{
		code = *iter;
		installation = installation_path_ + getFileName(code);
		if (copyFile(code, installation) == 0) 
		{
			std::cerr << "Error during installing artifact " << code << std::endl;
			throw Components::CreateFailure();
		}
		*iter = installation;
	}

	//
	// install business code files
    //
	installation = installation_path_ + getFileName(data_.executor_module);
    if (copyFile(data_.executor_module, installation) == 0) 
	{
		std::cerr << "Error during installing executor code " << data_.executor_module << std::endl;
        throw Components::CreateFailure();
	}
	data_.executor_module = installation;

	//
	// servant code files have to be extracted from the archive or to be build
    //
	if ((data_.servant_module != "") && (data_.servant_entry_point != ""))
	{
		installation = installation_path_ + getFileName(data_.servant_module);
		if (copyFile(data_.servant_module, installation) == 0) 
		{
			std::cerr << "Error during installing servant code " << data_.servant_module << "; try to generate" << std::endl;
		}
		else 
		{
			data_.servant_module = installation;
			return;
		}
	}

	//
	// build servant code
	//
	buildServants();
}


void
ComponentImplementation::buildServants()
throw(Components::CreateFailure)
{
	data_.servant_module = installation_path_ + data_.uuid + "_servants." + DLL_EXT;
	data_.servant_entry_point = "create_" + data_.home_name + "S";

#ifdef _WIN32
	makefile_ = g_qedo_dir + "\\etc\\makefile";
#else
	makefile_ = g_qedo_dir + "/etc/makefile";
#endif

	if ( !checkExistence(makefile_, IS_FILE)) 
	{
		std::cerr << "missing makefile : " << makefile_ << std::endl;
		throw Components::CreateFailure();
	}

#ifdef _WIN32
	std::string command = "nmake /f " + makefile_;
	command += " SOURCE=" + data_.idl.location.file;
	command += " TARGET=" + data_.home_repid;
	command += " DLL=" + data_.servant_module;
	std::cout << command << std::endl;

	{
	char* command_line = strdup(command.c_str());
	char* command_dir = strdup(build_path_.c_str());

	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        command_line,     // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        command_dir,      // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
    {
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf, 0, NULL);
		std::cerr << "CreateProcess failed: " << (LPCTSTR)lpMsgBuf << std::endl;
		
		// Free the buffer.
		LocalFree( lpMsgBuf );
		throw Components::CreateFailure();
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    //
    // get exit code
    //
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        if (exitCode)
        {
			std::cerr << "Servant code generation failed !!!" << std::endl;
            throw Components::CreateFailure();
        }
    }
    else 
    {
        std::cerr << "GetExitCodeProcess() failed !!!" << std::endl;
        throw Components::CreateFailure();
    }

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	delete command_line;
	delete command_dir;
	}
#else
	std::string command = "cd " + build_dir_ + ";make -f " + makefile_;
	command += " SOURCE=" + data_.idl.location.file;
	command += " TARGET=" + data_.servant_module;
	std::cout << command << std::endl;
	int ret=system(command.c_str());
	if(!WIFEXITED(ret))
	{
		std::cerr << "Error while making: "  << ret << std::endl;
        throw Components::CreateFailure();
	}
#endif
}


}

