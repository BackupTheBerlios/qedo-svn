#ifndef __GENERATOR_CCD_H__
#define __GENERATOR_CCD_H__

#include "GeneratorBase.h"
#include "Printer.h"

#include <fstream>
#include <string>
#include <iostream>


using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorCCD : public virtual GeneratorBase {

	string filename_;
	Printer out;

	void doComposition(CIDL::CompositionDef_ptr composition);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

	GeneratorCCD(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorCCD();

	void generate(string target);

};

} // namespace QEDO_CIDL_Generator

#endif
