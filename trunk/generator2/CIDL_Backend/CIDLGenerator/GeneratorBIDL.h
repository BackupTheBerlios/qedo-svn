#ifndef __GENERATOR_BIDL_H__
#define __GENERATOR_BIDL_H__

#include "IDLBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>


using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorBIDL : public virtual IDLBase
{

	string filename_;
	Printer out;
	
	void open_module(IR__::Contained* cur_cont);
	void close_module(IR__::Contained* cur_cont);
	void doComposition(CIDL::CompositionDef_ptr composition);

public:

	GeneratorBIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBIDL();

	void generate(std::string target, std::string fileprefix);

};

} // namespace QEDO_CIDL_Generator

#endif

