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
#include "CADReader.h"
#include "Output.h"
#include <fstream>


static char rcsid[] UNUSED = "$Id: ComponentImplementation.cpp,v 1.20 2004/02/12 15:05:38 neubauer Exp $";


namespace Qedo {


ComponentImplementation::ComponentImplementation
( ComponentImplementationData data 
, std::string package
, CosNaming::NamingContext_ptr nameContext)
{
	data_ = data;
	installation_path_ = getPath(data_.installation_dir);
	build_dir_ = installation_path_ + "build";
	build_path_ = getPath(build_dir_);
	package_ = package;
	installation_count_ = 0;
	nameService_ = CosNaming::NamingContext::_duplicate(nameContext);
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


void
ComponentImplementation::install()
throw(Components::CreateFailure)
{
    //
	// if already installed increment counter only
	//
	if (installation_count_)
	{
		installation_count_++;
		DEBUG_OUT3( "..... already installed (", installation_count_, ")" );
		return;
	}

	//
	// if without package increment counter only
	//
	if (package_.empty())
	{
		installation_count_++;
		return;
	}

	//
	// create directories for the component implementation
	//
	makeDir(data_.installation_dir);
    makeDir(build_dir_);

	//
	// package may be component or composition
	//
	Package archive = Package( package_ );
    std::string xmlfile_name = archive.getFileNameWithSuffix( ".cad" );
    if ( xmlfile_name != std::string( "" ) )
	{
		//
		// get info from the assembly package
		//
		CADReader reader;
		try 
		{
			reader.readCAD( package_, &(data_.assembly), build_path_ );
		}
		catch( CADReadException ) 
		{
			std::cerr << "!!!!! Error during reading .cad" << std::endl;
			removeFileOrDirectory(data_.installation_dir);
			removeFileOrDirectory(build_dir_);
			throw Components::CreateFailure();
		}
		data_.assembly.cad = getFileName( xmlfile_name );
	}
	else
	{
		xmlfile_name = archive.getFileNameWithSuffix( ".csd" );

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
			std::cerr << "!!!!! Error during reading .csd" << std::endl;
			removeFileOrDirectory(data_.installation_dir);
			removeFileOrDirectory(build_dir_);
			throw Components::CreateFailure();
		}
		data_.csd = getFileName( xmlfile_name );
	}

    //
	// install any code
	//
    try	
	{
		installCode();
	}
	catch( Components::CreateFailure )
	{
		removeFileOrDirectory(data_.installation_dir);
		removeFileOrDirectory(build_dir_);
        throw Components::CreateFailure();
	}

	// increment installation counter ( to 1 )
	installation_count_++;
}


void 
ComponentImplementation::uninstall()
throw (Components::RemoveFailure)
{
    installation_count_--;

	if (installation_count_ == 0) 
	{
		//
		// remove installed code
		//
		removeFileOrDirectory(data_.installation_dir);
	}
}


ComponentImplementationData
ComponentImplementation::getData()
{
	return data_;
}


void
ComponentImplementation::installAssembly()
throw( Components::CreateFailure )
{
	//
	// for each hostcollocation
	//
	std::vector < HostData > ::const_iterator host_iter;
	for(host_iter = data_.assembly.hosts_.begin(); 
		host_iter != data_.assembly.hosts_.end(); 
		host_iter++)
	{
		Qedo_Components::Deployment::ComponentInstallation_var componentInstallation;
		CORBA::Object_var obj;
		std::string host = (*host_iter).host;

		//
		// get ComponentInstallation for destination
		//
		obj = resolveName(COMPONENT_INSTALLATION_CONTEXT + host);
		if ( CORBA::is_nil(obj))
		{
			std::cerr << "..... no ComponentInstallation for " << host << std::endl;
			throw Components::CreateFailure();
		}
    
		componentInstallation = Qedo_Components::Deployment::ComponentInstallation::_narrow(obj.in());
		if ( CORBA::is_nil(componentInstallation.in()))
		{
			std::cerr << "..... no ComponentInstallation for " << host << std::endl;
			throw Components::CreateFailure();
		}

		//
		// for each processcollocation
		//
		std::vector < ProcessData > ::const_iterator process_iter;
		for(process_iter = (*host_iter).processes.begin(); 
			process_iter != (*host_iter).processes.end();
			process_iter++)
		{
			//
			// for each homeplacement
			//
			std::vector < HomeInstanceData > ::const_iterator iter;
			for(iter = (*process_iter).homes.begin();
				iter != (*process_iter).homes.end(); 
				iter++)
			{
				HomeInstanceData data = *iter;
				std::string package_file_ref = data.file;
				std::string package_file = data_.assembly.implementationMap_[package_file_ref].archiv;
				std::string impl_id = data.impl_id;

				std::cout << "..... install implementation " << std::endl;
				std::cout << ".......... destination is " << data.dest << std::endl;
				std::cout << ".......... implementation id is " << std::endl;
				std::cout << ".......... package is " << package_file << std::endl;

				//
				// install
				//
				std::string location = std::string("PACKAGE=") + getFileName(package_file);
				try
				{
					componentInstallation->install(impl_id.c_str(), location.c_str());
				}
				catch(Components::Deployment::InvalidLocation&)
				{
					std::cout << ".......... upload required" << std::endl;
					CORBA::OctetSeq_var octSeq = new CORBA::OctetSeq();
					struct stat statbuff;
					int rt = stat(package_file.c_str(), &statbuff);
					long size = statbuff.st_size;
					octSeq->length(size);
       
					std::ifstream package_stream(package_file.c_str(), std::ios::binary|std::ios::in);
					package_stream.read((char*)octSeq->get_buffer(), size);
					package_stream.close();
        
					//
					// upload first and install afterwards
					//
					try
					{
						location = componentInstallation->upload(impl_id.c_str(), octSeq);
						std::cout << ".......... upload done, install now" << std::endl;
						componentInstallation->install(impl_id.c_str(), location.c_str());
					}
					catch(Components::Deployment::InstallationFailure&)
					{
						throw Components::CreateFailure();
					}
				}
				catch ( CORBA::SystemException& )
				{
					std::cerr << ".......... CORBA system exception during install()" << std::endl;
					std::cerr << ".......... is ComponentInstallation running?" << std::endl;
					throw Components::CreateFailure();
				}
			}
		}
	}

    //
    // remove extracted packages
    //
#if 0
	std::map < std::string, std::string > ::iterator iter2;
	for(iter2 = data_.assembly.implementationMap_.begin();
		iter2 != data_.assembly.implementationMap_.end();
		iter2++)
	{
        removeFileOrDirectory((*iter2).second);
    }
#endif
}


void
ComponentImplementation::installCode()
throw(Components::CreateFailure)
{
	std::string name;

	//
	// install subcomponents (if existing)
	//
	if(data_.assembly.cad.length())
	{
		installAssembly();
		name = data_.assembly.cad;
		copyFile( build_path_ + name, installation_path_ + name );
	}

	if(data_.csd.empty())
	{
		return;
	}
	name = data_.csd;
	copyFile( build_path_ + name, installation_path_ + name );

	//
	// install valuetype factories
	//
	std::vector < ValuetypeData >::iterator value_iter;
	for(value_iter = data_.valuetypes.begin();
		value_iter != data_.valuetypes.end();
		value_iter++)
	{
		name = (*value_iter).location.file;
		if (copyFile( build_path_ + name, installation_path_ + name ) == 0) 
		{
			std::cerr << "Error during installing valuetype factory " << name << std::endl;
			throw Components::CreateFailure();
		}
	}

	//
	// install artifacts
	//
	std::vector < std::string >::iterator iter;
	for (iter = data_.artifacts.begin(); 
		iter != data_.artifacts.end();
		iter++)
	{
		name = *iter;
		if (copyFile( build_path_ + name, installation_path_ + name ) == 0) 
		{
			std::cerr << "Error during installing artifact " << name << std::endl;
			throw Components::CreateFailure();
		}
	}

	//
	// install implementation code
	//
	if(data_.executor_module.length())
	{
		//
		// install business code files
		//
		name = data_.executor_module;
		if (copyFile( build_path_ + name, installation_path_ + name ) == 0) 
		{
			std::cerr << "Error during installing executor code " << name << std::endl;
			throw Components::CreateFailure();
		}

		//
		// servant code files have to be extracted from the archive or to be build
		//
		if ((data_.servant_module.length()) && (data_.servant_entry_point.length()))
		{
			name = data_.servant_module;
			if (copyFile( build_path_ + name, installation_path_ + name ) == 0) 
			{
				std::cerr << "Error during installing servant code " << name << "; try to generate" << std::endl;
			}
			else 
			{
				return;
			}
		}

		//
		// build servant code
		//
		buildServants();
	}
}


void
ComponentImplementation::buildServants()
throw(Components::CreateFailure)
{
	data_.servant_module = data_.uuid + "_servants." + DLL_EXT;
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
	command += " SOURCE=" + build_path_ + data_.idl.location.file;
	command += " TARGET=" + data_.home_repid;
	command += " DLL=" + installation_path_ + data_.servant_module;
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
	command += " TARGET=" + installation_path_ + data_.servant_module;
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

