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
ComponentImplementation::author (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("author"));
    if (nodeList->getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::code (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("code"));
    if (nodeList->getLength() > 0)
    {
        DOMElement* codeEl = (DOMElement*)(nodeList->item(0));
		if (!XMLString::compareString(codeEl->getAttribute(X("type")), X("DLL")))
		{
		    // set file name
			DOMNodeList* aNodeList = codeEl->getElementsByTagName(X("fileinarchive"));
			DOMElement* subElement = (DOMElement*)(aNodeList->item(0));
			executor_module_ = XMLString::transcode(subElement->getAttribute(X("name")));

			// set entry point
			aNodeList = codeEl->getElementsByTagName(X("entrypoint"));
			subElement = (DOMElement*)(aNodeList->item(0));
			executor_entry_point_ = XMLString::transcode(subElement->getFirstChild()->getNodeValue());
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
ComponentImplementation::corbacomponent (DOMDocument* document)
throw(Components::CreateFailure)
{
    std::string repid_of_home;
	DOMNode* xxx = document->getDocumentElement();
    DOMNode* child = document->getDocumentElement()->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// homerepid
			//
			if (!XMLString::compareString(child->getNodeName(), X("homerepid")))
			{
				repid_of_home = XMLString::transcode(((DOMElement*)child)->getAttribute(X("repid")));
			}

			//
			// homefeatures
			//
			else if (!XMLString::compareString(child->getNodeName(), X("homefeatures")))
			{
				if (repid_of_home == XMLString::transcode(((DOMElement*)child)->getAttribute(X("repid"))))
				{
					mHomeName = XMLString::transcode(((DOMElement*)child)->getAttribute(X("name")));
				}
			}
		}

        // get next child
		child = child->getNextSibling();
    }
}


/**
 *
 */
void
ComponentImplementation::dependency (DOMElement* element)
throw(Components::CreateFailure)
{
    std::string orb;
    DOMNodeList* nodeList = element->getElementsByTagName(X("dependency"));
    for (unsigned int i = 0; i < nodeList->getLength(); ++i)
    {
        DOMElement* dependencyEl = (DOMElement*)(nodeList->item(i));
		std::string type = XMLString::transcode(dependencyEl->getAttribute(X("type")));

        //
    	// ORB
		//
		if (type == "ORB")
		{
		    DOMNodeList* aNodeList = dependencyEl->getElementsByTagName(X("name"));
			DOMElement* orbname = (DOMElement*)(aNodeList->item(0));
			orb = XMLString::transcode(orbname->getFirstChild()->getNodeValue());
	    }
    }
}


/**
 *
 */
void
ComponentImplementation::description (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("description"));
    if (nodeList->getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
DOMDocument* 
ComponentImplementation::descriptor (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMDocument* document;
    DOMNodeList* nodeList = element->getElementsByTagName(X("descriptor"));
    if (nodeList->getLength() > 0)
    {
        std::string cfile;
        DOMNode* child = nodeList->item(0)->getFirstChild();
	    while (child != 0)
	    {
			if (child->getNodeType() == DOMNode::ELEMENT_NODE)
			{
				//
				// link
				//
				if (!XMLString::compareString(child->getNodeName(), X("link")))
				{
					cfile = link((DOMElement*)(child), mBuildPath);
				}

				//
				// fileinarchive
				//
				else if (!XMLString::compareString(child->getNodeName(), X("fileinarchive")))
				{
					cfile = fileinarchive((DOMElement*)(child), mBuildPath);
				}
			}

            // get next child
		    child = child->getNextSibling();
        }

        //
        // parse file
        //
        static DOMXMLParser* parser = new DOMXMLParser;
        char* xmlfile = strdup((getPath(mBuildPath) + cfile).c_str());
        if (parser->parse(xmlfile) != 0) 
        {
			std::cerr << "Error during XML parsing" << std::endl;
            delete(xmlfile);
            throw Components::CreateFailure();
	    }
	    document = parser->getDocument();
    }

    return document;
}


/**
 *
 */
void
ComponentImplementation::extension(DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("extension"));
    for (unsigned int i = 0; i < nodeList->getLength(); ++i)
    {
        // TODO
    }
}


/**
 *
 */
std::string
ComponentImplementation::fileinarchive(DOMElement* element, std::string destination)
throw(Components::CreateFailure)
{
	std::string fileName = XMLString::transcode(element->getAttribute(X("name")));

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
ComponentImplementation::idl (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("idl"));
    if (nodeList->getLength() > 0)
    {
		DOMElement* idl_element = (DOMElement*)(nodeList->item(0));
		// TODO the attribute id refers to the home instead to the component !!!
		mIdlTarget = XMLString::transcode(idl_element->getAttribute(X("id")));
        DOMNode* child = idl_element->getFirstChild();
	    while (child != 0)
	    {
			if (child->getNodeType() == DOMNode::ELEMENT_NODE)
			{
				//
				// link
				//
				if (!XMLString::compareString(child->getNodeName(), X("link")))
				{
					mIdlFile = link((DOMElement*)(child), mBuildPath);
				}

				//
				// fileinarchive
				//
				if (!XMLString::compareString(child->getNodeName(), X("fileinarchive")))
				{
					mIdlFile = fileinarchive((DOMElement*)(child), mBuildPath);
				}

				//
				// repository
				//
				if (!XMLString::compareString(child->getNodeName(), X("repository")))
				{
					// TODO
				}
			}

			// get next child
		    child = child->getNextSibling();
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
ComponentImplementation::implementation (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNode* child = element->getFirstChild();
	DOMElement* child_element = 0;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			child_element = (DOMElement*)(child);

			//
			// get the right implementation
			//
			if ((!XMLString::compareString(child->getNodeName(), X("implementation"))) &&
				(!XMLString::compareString(child_element->getAttribute(X("id")), X(uuid_.c_str()))))
			{
				// handle dependencies
				dependency(child_element);

				// handle descriptor
				mComponentDescriptor = descriptor(child_element);

				// handle code
				code(child_element);

				// handle os
				os(child_element);

				break;
			}
		}

        // next child
		child = child->getNextSibling();
	}
}


/**
 *
 */
void
ComponentImplementation::license (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("license"));
    if (nodeList->getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
std::string
ComponentImplementation::link (DOMElement* element, std::string destination)
throw(Components::CreateFailure)
{
    XMLURL uri(element->getAttribute(X("href")));
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
ComponentImplementation::os (DOMElement* element)
throw(Components::CreateFailure)
{
    std::string os;
    DOMNodeList* nodeList = element->getElementsByTagName(X("os"));
    if (nodeList->getLength() > 0)
    {
		os = XMLString::transcode(((DOMElement*)nodeList->item(0))->getAttribute(X("name")));
    }
}


/**
 *
 */
void
ComponentImplementation::pkgtype (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("pkgtype"));
    if (nodeList->getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::propertyfile (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("propertyfile"));
    if (nodeList->getLength() > 0)
    {
        // TODO
    }
}


/**
 *
 */
void
ComponentImplementation::title (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("title"));
    if (nodeList->getLength() > 0)
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
    DOMElement* rootElement = mDocument->getDocumentElement();

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