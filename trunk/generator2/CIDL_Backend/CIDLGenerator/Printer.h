#ifndef __PRINTER_H__
#define __PRINTER_H__

#ifdef _MSC_VER
#pragma warning ( disable:4786 )
#endif

#include <fstream>
#include <string>
#include <map>


namespace QEDO_CIDL_Generator {


//
//
//
class Printer
{

	long indent_;
	std::ofstream stream_;
	bool new_line_;
	std::map < std::string, std::string > user_sections_;

public:

	Printer() : indent_(0), new_line_(true) {}
	~Printer() {}

	Printer& operator<<(std::string text);
	Printer& operator<<(std::ifstream& text);

	void open(const char* name);
	void close();

	void indent();
	void unindent();

	void initUserSections(const char* name);
	void insertUserSection(std::string name, int blank_lines = 1);
};

} // namespace QEDO_CIDL_Generator

#endif
