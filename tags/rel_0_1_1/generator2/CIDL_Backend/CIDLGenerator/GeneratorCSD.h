#ifndef __GENERATOR_CSD_H__
#define __GENERATOR_CSD_H__


#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorCSD : public CPPBase
{

private:

	std::set<std::string>	m_recursion_set;
	std::string				filename_;
	std::string				idlfilename_;
	Printer					out;

	void doComposition(CIDL::CompositionDef_ptr composition);

protected:

	void check_for_generation(IR__::Contained_ptr item);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	GeneratorCSD(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorCSD();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

