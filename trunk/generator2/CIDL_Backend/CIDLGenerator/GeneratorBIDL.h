#ifndef __GENERATOR_BIDL_H__
#define __GENERATOR_BIDL_H__

#include "IDLBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


//
//
//
class GeneratorBIDL : public virtual IDLBase
{

private:

	std::set<std::string> m_recursion_set;
	std::string filename_;
	
	void doComposition(CIDL::CompositionDef_ptr composition);

protected:

	void check_for_generation(IR__::Contained_ptr item);

public:

	GeneratorBIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBIDL();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

