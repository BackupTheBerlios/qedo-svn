#ifndef __GENERATOR_CCD_H__
#define __GENERATOR_CCD_H__

#include "CPPBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorCCD : public CPPBase {

	std::string filename_;
	Printer out;

	void doModule(IR__::ModuleDef_ptr module);

	void doComposition(CIDL::CompositionDef_ptr composition);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	GeneratorCCD(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorCCD();

	void generate(std::string target, std::string fileprefix);

};

} // namespace QEDO_CIDL_Generator

#endif

