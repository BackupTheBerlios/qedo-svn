#include "Printer.h"


namespace QEDO_CIDL_Generator {


Printer& 
Printer::operator<<(int text)
{
	stream_ << text;

	return *this;
}


Printer& 
Printer::operator<<(std::string text)
{
	if(new_line_)
	{
		for(int i = 0; i < indent_; i++)
		{
			stream_ << "    ";
		}
		new_line_ = false;
	}

	std::string::size_type pos = text.find("\n");
	if(pos == std::string::npos)
	{
		stream_ << text;
	}
	else
	{
		/*
		string::size_type start_index = 0;
		for(; pos != string::npos; pos = text.find("\n", pos))
		{
			if(new_line_)
			{
				for(int i = 0; i < indent_; i++)
				{
					stream_ << "  ";
				}
				new_line_ = false;
			}
			stream_ << text.substr(start_index, pos - start_index);
			stream_ << std::endl;
			new_line_ = true;
			pos++;
			start_index = pos;
		}
		if(new_line_)
		{
			for(int i = 0; i < indent_; i++)
			{
				stream_ << "  ";
			}
			new_line_ = false;
		}
		stream_ << text.substr(start_index, pos - start_index);
		*/
		stream_ << text.substr(0, pos) << std::endl;
		new_line_ = true;
		if(++pos < text.size())
		{
			operator<<(text.substr(pos));
		}
	}
	return *this;
}


Printer& 
Printer::operator<<(std::ifstream& text)
{
	stream_ << text.rdbuf();

	return *this;
}


void 
Printer::open(const char* name)
{ 
	stream_.open(name); indent_ = 0;
}


void 
Printer::close()
{
	stream_.close(); 
}


void 
Printer::indent() 
{ 
	indent_++; 
}


void 
Printer::unindent() 
{
	indent_--; 
}


void 
Printer::initUserSections(const char* name) 
{
	user_sections_.clear();
	std::ifstream in_file(name);
	if(!in_file) {
		return;
	}

	std::string section;
	std::string section_name;
	char line[256];
	while(in_file.getline(line, 256)) {
		if(!strncmp(line, "// BEGIN USER INSERT SECTION ", 29))	{
			section_name = line + 29;
		
			while(in_file.getline(line, 256)) {
				if(!strncmp(line, "// END USER INSERT SECTION ", 27)) {
					user_sections_[section_name] = section;
					section = "";
					break;
				}
				section.append(line);
				section.append("\n");
			}
		}
	}

	in_file.close();
}


void 
Printer::insertUserSection(std::string name, int blank_lines) 
{
	stream_ << "// BEGIN USER INSERT SECTION " << name << std::endl;
	std::map < std::string, std::string > ::iterator i = user_sections_.find(name);
	if(i != user_sections_.end())
	{
		stream_ << user_sections_[name];
		user_sections_.erase(i);
	}
	stream_ << "// END USER INSERT SECTION " << name << std::endl;
	
	for(int ii = 0; ii < blank_lines; ii++) {
		stream_ << std::endl;
	}
}


} // namespace QEDO_CIDL_Generator
