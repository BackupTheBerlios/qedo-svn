#ifndef __GENERATOR_VC7_H__
#define __GENERATOR_VC7_H__

#include "CPPBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorVC7 : public CPPBase {

	std::string filename_;
	Printer out;
	int uid_;

	void doModule(IR__::ModuleDef_ptr module);
	void doComposition(CIDL::CompositionDef_ptr composition);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	GeneratorVC7(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorVC7();

	void generate(std::string target, std::string fileprefix);

	std::string target_file_name_;

};


} // namespace


#endif

