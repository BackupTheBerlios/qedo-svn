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


static char rcsid[] UNUSED = "$Id: ComponentImplementation.cpp,v 1.10 2003/08/27 06:48:34 neubauer Exp $";


namespace Qedo {


ComponentImplementation::ComponentImplementation (const char* uuid, std::string installationDirectory, std::string package)
: uuid_ (uuid)
{
    installation_count_ = 0;
    package_ = new Package(package);
	installation_dir_ = getPath(installationDirectory) + uuid_;
    installation_path_ = getPath(installation_dir_);
	build_dir_ = installation_path_ + "build";
    build_path_ = getPath(build_dir_);
}


ComponentImplementation::ComponentImplementation (std::string uuid, std::string servant_module, 
												  std::string servant_entry_point, std::string executor_module,
												  std::string executor_entry_point)
: uuid_ (uuid), servant_module_ (servant_module), servant_entry_point_ (servant_entry_point),
  executor_module_ (executor_module), executor_entry_point_ (executor_entry_point), installation_count_(1),
  installation_dir_(""), installation_path_(""), build_dir_(""), build_path_(""), package_(0)
{
}


ComponentImplementation::ComponentImplementation (std::string uuid) 
: uuid_ (uuid), servant_module_ (""), servant_entry_point_ (""),
  executor_module_ (""), executor_entry_point_ (""), installation_count_(1),
  installation_dir_(""), installation_path_(""), build_dir_(""), build_path_(""), package_(0)
{
}


ComponentImplementation::~ComponentImplementation
()
{
}


bool
ComponentImplementation::operator == 
( ComponentImplementation id )
{
    if (uuid_ == id.uuid_) 
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
	// find and extract the software package descriptor
	//
    std::string csdfile = package_->getFileNameWithSuffix( ".csd" );
    if ( csdfile == std::string( "" ) )
	{
		std::cerr << "..... Missing a csd file!" << std::endl;
		removeFileOrDirectory(installation_dir_);
		removeFileOrDirectory(build_dir_);
        return false;
	}
    if (package_->extractFile(csdfile, build_path_ + csdfile) != 0)
	{
		std::cerr << "..... Error during extracting the descriptor file" << std::endl;
		removeFileOrDirectory(installation_dir_);
		removeFileOrDirectory(build_dir_);
        return false;
	}

	//
	// parse the software package descriptor file
    //
	CSDReader reader;
	reader.readCSD( build_path_ + csdfile, this );

    // install code for servants and executors
    try	{
		installCode();
	}
	catch( Components::CreateFailure ) {
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
	for(value_iter = valuetypes_.begin();
		value_iter != valuetypes_.end();
		value_iter++)
	{
		code = (*value_iter).file_name;
		installation = installation_path_ + getFileName(code);
		if (copyFile(code, installation) == 0) 
		{
			std::cerr << "Error during installing valuetype factory " << code << std::endl;
			throw Components::CreateFailure();
		}
		(*value_iter).file_name = installation;
	}

	//
	// install artifacts
	//
	std::vector < std::string >::iterator iter;
	for (iter = artifacts_.begin(); iter != artifacts_.end(); iter++)
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
	installation = installation_path_ + getFileName(executor_module_);
    if (copyFile(executor_module_, installation) == 0) 
	{
		std::cerr << "Error during installing executor code " << executor_module_ << std::endl;
        throw Components::CreateFailure();
	}
	executor_module_ = installation;

	//
	// servant code files have to be extracted from the archive or to be build
    //
	if ((servant_module_ != "") && (servant_entry_point_ != ""))
	{
		installation = installation_path_ + getFileName(servant_module_);
		if (copyFile(servant_module_, installation) == 0) 
		{
			std::cerr << "Error during installing servant code " << servant_module_ << "; try to generate" << std::endl;
		}
		else 
		{
			servant_module_ = installation;
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
	servant_module_ = installation_path_ + uuid_ + "_servants." + DLL_EXT;
	servant_entry_point_ = "create_" + home_name_ + "S";

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
	command += " SOURCE=" + idl_file_;
	command += " TARGET=" + home_repid_;
	command += " DLL=" + servant_module_;
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
	std::string command = "cd " + build_dir_ + ";make -f " + makefile_ + " SOURCE=" + idl_file_ + " TARGET=" + servant_module_;
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

