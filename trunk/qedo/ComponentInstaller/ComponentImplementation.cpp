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
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


namespace Qedo {


/**
 * Constructor for new implementation.
 */
ComponentImplementation::ComponentImplementation (const char* uuid, std::string installationDirectory, std::string package)
: uuid_ (uuid)
{
    mCounter = 0;
    mPackage = new Package(package);
    mPath = getPath(installationDirectory) + uuid_;
    mBuildPath = getPath(mPath) + "build";
    mComponentDescriptor = 0;
}


/**
 * Constructor for implementation read from DeployedComponents file.
 */
ComponentImplementation::ComponentImplementation (std::string uuid, std::string servant_module, 
												  std::string servant_entry_point, std::string executor_module,
												  std::string executor_entry_point)
: uuid_ (uuid), servant_module_ (servant_module), servant_entry_point_ (servant_entry_point),
  executor_module_ (executor_module), executor_entry_point_ (executor_entry_point)
{
	description_ = servant_module_; description_ += ":";
	description_ += servant_entry_point; description_ += ":";
	description_ += executor_module_; description_ += ":";
	description_ += executor_entry_point_;

	mCounter = 1;
    mPackage = 0;
    mPath = "";
    mBuildPath = "";
}


/**
 *
 */
ComponentImplementation::~ComponentImplementation
()
{
}


/**
 *
 */
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


/**
 *
 */
void
ComponentImplementation::author (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("author");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::code (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("code");
    if (nodeList.getLength() > 0)
    {
        DOM_Element codeEl = (const DOM_Element&)(nodeList.item(0));
		if ( std::string(codeEl.getAttribute("type").transcode()) == "DLL" )
		{
		    // set file name
			DOM_NodeList aNodeList = codeEl.getElementsByTagName("fileinarchive");
			DOM_Element subElement = (const DOM_Element&)aNodeList.item(0);
			executor_module_ = std::string(subElement.getAttribute("name").transcode());

			// set entry point
			aNodeList = codeEl.getElementsByTagName("entrypoint");
			subElement = (const DOM_Element&)aNodeList.item(0);
			executor_entry_point_ = std::string(subElement.getFirstChild().getNodeValue().transcode());
		}
    }
    else
    {
		std::cerr << "Missing implementation for " << uuid_ << std::endl;
		throw Components::CreateFailure();
    }
}


/**
 *
 */
void
ComponentImplementation::corbacomponent (DOM_Document document)
throw(Components::CreateFailure)
{
    std::string repid_of_home;
    DOM_Node child = document.getDocumentElement().getFirstChild();
	while (child != 0)
	{
		//
		// homerepid
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("homerepid")))
        {
            repid_of_home = ((const DOM_Element&)child).getAttribute("repid").transcode();
        }

        //
		// homefeatures
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("homefeatures")))
        {
            if (repid_of_home == ((const DOM_Element&)child).getAttribute("repid").transcode())
            {
                mHomeName = ((const DOM_Element&)child).getAttribute("name").transcode();
            }
        }

        // get next child
		child = child.getNextSibling();
    }
}


/**
 *
 */
void
ComponentImplementation::dependency (DOM_Element element)
throw(Components::CreateFailure)
{
    std::string orb;
    DOM_NodeList nodeList = element.getElementsByTagName("dependency");
    for (unsigned int i = 0; i < nodeList.getLength(); ++i)
    {
        DOM_Element dependencyEl = (const DOM_Element&)nodeList.item(i);
        std::string type = dependencyEl.getAttribute("type").transcode();

        //
    	// ORB
		//
		if (type == "ORB")
		{
		    DOM_NodeList aNodeList = dependencyEl.getElementsByTagName("name");
			DOM_Element orbname = (const DOM_Element&)aNodeList.item(0);
			orb = orbname.getFirstChild().getNodeValue().transcode();
	    }
    }
}


/**
 *
 */
void
ComponentImplementation::description (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("description");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
DOM_Document 
ComponentImplementation::descriptor (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_Document document;

    DOM_NodeList nodeList = element.getElementsByTagName("descriptor");
    if (nodeList.getLength() > 0)
    {
        std::string cfile;
        DOM_Node child = nodeList.item(0).getFirstChild();
	    while (child != 0)
	    {
            //
	        // link
	        //
	        if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
	            (child.getNodeName().equals("link")))
            {
                cfile = link((const DOM_Element&)child, mBuildPath);
            }

            //
		    // fileinarchive
		    //
		    if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		        (child.getNodeName().equals("fileinarchive")))
            {
                cfile = fileinarchive((const DOM_Element&)child, mBuildPath);
            }

            // get next child
		    child = child.getNextSibling();
        }

        //
        // parse file
        //
        DOMXMLParser parser;
        char* xmlfile = strdup((getPath(mBuildPath) + cfile).c_str());
        if (parser.parse(xmlfile) != 0) 
        {
			std::cerr << "Error during XML parsing" << std::endl;
            delete(xmlfile);
            throw Components::CreateFailure();
	    }
	    document = parser.getDocument();
    }

    return document;
}


/**
 *
 */
void
ComponentImplementation::extension(DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("extension");
    for (unsigned int i = 0; i < nodeList.getLength(); ++i)
    {
        // TODO
    }
}


/**
 *
 */
std::string
ComponentImplementation::fileinarchive(DOM_Element element, std::string destination)
throw(Components::CreateFailure)
{
    std::string fileName = element.getAttribute("name").transcode();

	// extract the file
    if (mPackage->extractFile(fileName, getPath(destination) + fileName) != 0)
	{
		std::cerr << "Error during extracting file" << std::endl;
        throw Components::CreateFailure();
	}

    return fileName;
}


/**
 *
 */
void
ComponentImplementation::idl (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("idl");
    if (nodeList.getLength() > 0)
    {
		DOM_Element idl_element = (const DOM_Element&)(nodeList.item(0));
		// TODO the attribute id refers to the home instead to the component !!!
		mIdlTarget = idl_element.getAttribute("id").transcode();
        DOM_Node child = idl_element.getFirstChild();
	    while (child != 0)
	    {
	        //
            // link
	        //
	        if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
	            (child.getNodeName().equals("link")))
            {
                mIdlFile = link((const DOM_Element&)child, mBuildPath);
            }

            //
		    // fileinarchive
		    //
		    if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		        (child.getNodeName().equals("fileinarchive")))
            {
                mIdlFile = fileinarchive((const DOM_Element&)child, mBuildPath);
            }

            //
		    // repository
		    //
		    if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		        (child.getNodeName().equals("repository")))
            {
                // TODO
            }

            // get next child
		    child = child.getNextSibling();
        }
    }
    else
    {
		std::cerr << "ComponentImplementation : missing exactly one idl element!" << std::endl;
        throw Components::CreateFailure();
    }
}


/**
 *
 */
void
ComponentImplementation::implementation (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_Node child = element.getFirstChild();
	while (child != 0)
	{
		//
		// get the right implementation
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("implementation")) &&
            (((const DOM_Element&)child).getAttribute("id").transcode() == uuid_))
        {
            // handle dependencies
            dependency((const DOM_Element&)child);

            // handle descriptor
            mComponentDescriptor = descriptor((const DOM_Element&)child);

            // handle code
            code((const DOM_Element&)child);

            // handle os
            os((const DOM_Element&)child);
		}

        // next child
		child = child.getNextSibling();
	}
}


/**
 *
 */
void
ComponentImplementation::license (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("license");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
std::string
ComponentImplementation::link (DOM_Element element, std::string destination)
throw(Components::CreateFailure)
{
    XMLURL uri(element.getAttribute("href").transcode());
    std::string name = XMLString::transcode(uri.getPath());
    std::string::size_type pos = name.find_last_of("/");
    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
    }
    
    std::string fileName = getPath(destination) + name;
    URLInputSource inputSource(uri);
    BinInputStream* inputStream = inputSource.makeStream();
    if (!inputStream)
    {
        throw Components::CreateFailure();
    }
        
	std::ofstream aFile;
	aFile.open(fileName.c_str(), std::ios::binary|std::ios::app);
	if (!aFile)
	{
		std::cerr << "Cannot open file " << fileName << std::endl;
		throw Components::CreateFailure();
	}
    unsigned char* buf = (unsigned char*)malloc(4096);
    unsigned int len = inputStream->readBytes(buf, 4096);
    while (len)
    {
        aFile.write((const char*)buf, len);
        len = inputStream->readBytes(buf, 4096);
    }
    free(buf);
	aFile.close();

    return name;
}


/**
 *
 */
void
ComponentImplementation::os (DOM_Element element)
throw(Components::CreateFailure)
{
    std::string os;
    DOM_NodeList nodeList = element.getElementsByTagName("os");
    if (nodeList.getLength() > 0)
    {
        os = ((const DOM_Element&)nodeList.item(0)).getAttribute("name").transcode();
    }
}


/**
 *
 */
void
ComponentImplementation::pkgtype (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("pkgtype");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::propertyfile (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("propertyfile");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::title (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("title");
    if (nodeList.getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
bool
ComponentImplementation::install ()
{
    //
	// if already installed increment counter only
	//
	if (mCounter)
	{
		mCounter++;
		return true;
	}

	// create directories for the component implementation
	makeDir(mPath);
    makeDir(mBuildPath);
	
    //
	// find and extract the software package descriptor
	//
    std::string csdfile = mPackage->getFileNameWithSuffix( ".csd" );
    if ( csdfile == std::string( "" ) )
	{
		std::cerr << "Missing a csd file!" << std::endl;
        return false;
	}
    if (mPackage->extractFile(csdfile, getPath(mBuildPath) + csdfile) != 0)
	{
		std::cerr << "Error during extracting the descriptor file" << std::endl;
        return false;
	}

	//
	// parse the software package descriptor file
    //
	mParser = new DOMXMLParser();
	char* xmlfile = strdup((getPath(mBuildPath) + csdfile).c_str());
    if ( mParser->parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        return false;
	}
	mDocument = mParser->getDocument();
    DOM_Element rootElement = mDocument.getDocumentElement();

    // handle title
    title(rootElement);

    // handle package type
    pkgtype(rootElement);

    // handle author
    author(rootElement);

    // handle description
    description(rootElement);

    // handle license
    license(rootElement);

    // handle idl
    idl(rootElement);

    // handle propertyfile
    propertyfile(rootElement);

    // handle dependency
    dependency(rootElement);

    // handle implementation
	implementation(rootElement);

    // handle descriptor
    if (mComponentDescriptor == 0)
    {
        mComponentDescriptor = descriptor(rootElement);
        if (mComponentDescriptor == 0)
        {
			std::cerr << "ComponentImplementation : missing component descriptor for " << uuid_ << std::endl;
	        throw Components::CreateFailure();
        }
    }
    corbacomponent(mComponentDescriptor);

    // handle extension
    extension(rootElement);

    // build servant code
    buildServantCode();

	//
	// business code files have to be extracted from the archive
    //
    if (mPackage->extractFile(executor_module_, getPath(mPath) + executor_module_) != 0) 
	{
		std::cerr << "Error during extracting one of the code files" << std::endl;
        return false;
	}
	executor_module_ = getPath(mPath) + executor_module_;

	// increment installation counter ( to 1 )
	mCounter++;

	return true;
}


/**
 * compile the servant code for the component
 */
void
ComponentImplementation::buildServantCode()
throw(Components::CreateFailure)
{
	servant_module_ = getPath(mPath) + uuid_ + "_servants." + DLL_EXT;
	servant_entry_point_ = "create_" + mHomeName + "S";

#ifdef _WIN32
	TCHAR tchBuffer[256];
	LPTSTR lpszSystemInfo = tchBuffer;
	DWORD dwResult = ExpandEnvironmentStrings("%QEDO%", lpszSystemInfo, 256); 
    mMakeFile.append(lpszSystemInfo);
	mMakeFile.append("\\etc\\makefile");
#else
	TODO
#endif

	if ( !checkExistence(mMakeFile, IS_FILE)) 
	{
		std::cerr << "missing makefile : " << mMakeFile << std::endl;
		throw Components::CreateFailure();
	}

#ifdef _WIN32
	std::string command = "nmake /f " + mMakeFile;
	command += " SOURCE=" + mIdlFile;
	command += " TARGET=" + mIdlTarget;
	command += " DLL=" + servant_module_;
	std::cout << command << std::endl;

	{
	char* command_line = strdup(command.c_str());
	char* command_dir = strdup(mBuildPath.c_str());

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
	std::string command = "cd " + mBuildPath + ";make -f " + mMakeFile + " SOURCE=" + mIdlFile + " TARGET=" + servant_module_;
	DEBUG_OUT( command );
	int ret=system(command.c_str());
	if(!WIFEXITED(ret))
	{
		std::cerr << "Error while making: "  << ret << std::endl;
        throw Components::CreateFailure();
	}
#endif

	// remove temporary directory
	if (removeFileOrDirectory(mBuildPath))
    {
		std::cout << "removal of build directory failed! : " << mBuildPath << std::endl;
    }
}


/**
 *
 */
void 
ComponentImplementation::uninstall()
{
    mCounter--;

	//
    // remove installed code
	//
    if (mCounter == 0) 
	{
        //TODO
	}
}


/**
 *
 */
int 
ComponentImplementation::get_counter()
{
    return mCounter;
}


}