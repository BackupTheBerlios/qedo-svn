
#include "SoftpkgStructures.h"
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>

class InstallationSAXHandler : public HandlerBase 
{
  private:
	//enum ParseType {PKGNAME , CODEF}; // The value of this attribute is PKGNAME or CODEF
	//ParseType parsetype;

    int XMLerror; // Error code. Used in the InstallationParser class.

	bool softpkgfound;

    bool uuidfound; // Used in startElement and endElement procedures.

    bool implfound; // Used in startElement and endElement procedures.

    bool codefound; // Used in startElement and endElement procedures.

	bool entrypointfound;

    //std::string uuid; // Id whose code files are sought.
	std::string _uuid;
	std::string _code_type;
	std::string _file_name;
	std::string _entry_point;

	CodeList implementations; // List of the names of code files of the
                              // component implementation.

    std::string pkgname; // to store the name of the component package.
	std::string pkgUUID;
	std::string pkgversion;

  public:
    InstallationSAXHandler(); // Constructor.
	~InstallationSAXHandler();

    //InstallationSAXHandler(std::string); // Constructor. The string parameter is
                                    // used to set the uuid attribute.

	void get_implementations( CodeList& ); // Returns the list of the code files. //get_code_files
                                    // Used in the InstallationParser class.

    void get_pkgname( std::string& ); // Returns the pkgname attribute.
	void get_pkgversion (std::string&);
	void get_pkgUUID (std::string&);

    int get_error(); // Returns the XMLerror attribute.

    // Re-definition of four SAX procedures.

	void characters(const XMLCh* const , const unsigned int );

    void startElement(const XMLCh* const, AttributeList&);

    void endElement(const XMLCh* const);

    void error(const SAXParseException&);

    void fatalError(const SAXParseException&);

};
