#ifndef __GENERATOR_CCD_H__
#define __GENERATOR_CCD_H__


#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorCCD : public CPPBase
{

private:

	std::set<std::string> m_recursion_set;
	std::string filename_;
	Printer out;

	void doModule(IR__::ModuleDef_ptr module);
	void doComposition(CIDL::CompositionDef_ptr composition);

protected:

	void check_for_generation(IR__::Contained_ptr item);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	GeneratorCCD(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorCCD();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

