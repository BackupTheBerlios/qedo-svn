#include "GeneratorBase.h"
#ifndef ORBACUS_ORB
#ifdef _WIN32
#include "objbase.h"
#else
#endif
#endif

#ifndef _WIN32
#include "config.h"
#endif

#ifdef HAVE_LIBUUID
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include "uuid/uuid.h"
#endif

namespace QEDO_CIDL_Generator {


GeneratorBase::GeneratorBase
(CIDL::CIDLRepository_ptr repository)
{
	repository_ = CIDL::CIDLRepository::_duplicate(repository);
	file_prefix_ = "";
	target_scope_id_ = "";
	target_id_ = "";
	target_ = IR__::Contained::_nil();

	m_to_generate_seq = new IR__::ContainedSeq();
	m_to_generate_seq->length(0);

	m_to_generate_interface_seq = new IR__::ContainedSeq();
	m_to_generate_interface_seq->length(0);
}


GeneratorBase::~GeneratorBase
()
{
}


void
GeneratorBase::destroy
()
{
	delete this;
}


/*
 * make a name from a RepId by replacing / with _
 */
std::string
GeneratorBase::getNameFromRepId(std::string id)
{
	std::string name = id;

	// remove "IDL:"
	name.replace(0, 4, "");

	// remove ":1.0"
	name.replace(name.length() - 4, std::string::npos, "");

	// replace "/" by "_"
	std::string::size_type pos = name.find("/");
	if (pos != std::string::npos)
	{
		name.replace(pos, 1 , "_");
		pos = name.find("/");
	}

	return name;
}


/**
 *
 */
std::string 
GeneratorBase::uuidgen()
{
	std::string uuid = "";
#ifdef _WIN32
	// create uuid
	GUID guid;
	CoCreateGuid(&guid);
	LPOLESTR lpolestr;
	StringFromCLSID(guid, &lpolestr);
	int i = wcstombs(NULL, lpolestr, 0);
	char *buf = (char *)malloc(i);
	wcstombs(buf, lpolestr, i);
	// remove { and }
	buf[i - 1] = '\0';
	uuid = buf;
	uuid.erase(0, 1);
	free(buf);
	CoTaskMemFree(lpolestr);
#else
	uuid_t guid;
	uuid_generate(guid);
	char buf[36+1];
	uuid_unparse(guid,buf);
	uuid=buf;
#endif
	return uuid;
}


void
GeneratorBase::initialize(std::string target, std::string fileprefix)
    throw (InitializeError)
{
	//
	// check whether Components.idl is in the repository
	//
	if(CORBA::is_nil(repository_->lookup_id("IDL:Components:1.0")))
	{
		std::cerr << "----- could not find IDL:Components:1.0 in the repository" << std::endl;
		std::cerr << "----- generation stopped !!!" << std::endl;
		throw InitializeError();
	}

	//
	// lookup the target
	//
	target_ = repository_->lookup_id(target.c_str());
	if(CORBA::is_nil(target_))
	{
		target_ =	repository_->lookup(target.c_str());
	}
	if(CORBA::is_nil(target_))
	{
		std::cerr << "----- could not find " << target << " in the repository" << std::endl;
		std::cerr << "----- generation stopped !!!" << std::endl;
		throw InitializeError();
	}
	target_id_ = target_->id();

	//
	// check whether target is of supported kind
	//
	switch(target_->def_kind())	{
	case CORBA__::dk_Home :
	case CORBA__::dk_Module : 
	case CORBA__::dk_Composition :
	case CORBA__::dk_AbstractStorageHome :
	case CORBA__::dk_AbstractStorageType :
	case CORBA__::dk_StorageHome :
	case CORBA__::dk_StorageType :
		break;
	// no other targets supported
	default :
		std::cerr << "----- kind for " << target << " not supported" << std::endl;
		std::cerr << "----- generation stopped !!!" << std::endl;
		throw InitializeError();
	}

	//
	// determine the file prefix
	//
	if (fileprefix.length())
	{
		file_prefix_ = fileprefix;
	}
	else
	{
		file_prefix_ = getNameFromRepId(target_id_);
	}

	//
	// determine the target set
	//
	check_for_generation(target_);
}


bool
GeneratorBase::already_included (IR__::Contained_ptr item)
{
	CORBA::ULong i;
	CORBA::ULong len;

	switch(item->def_kind()) {
	case CORBA__::dk_Interface :
	case CORBA__::dk_Home :
	case CORBA__::dk_Component :
		len = m_to_generate_interface_seq -> length();
		for (i = 0 ; i < len ; i++) {
			if (!strcmp((*m_to_generate_interface_seq)[i]->id(), item->id())) {
				return true;
			};
		};
		return false;
		break;
	default :
		len = m_to_generate_seq -> length();
		for (i = 0 ; i < len ; i++) {
			if (!strcmp((*m_to_generate_seq)[i]->id(), item->id())) {
				return true;
			};
		};
		return false;
		break;
	}
}


void 
GeneratorBase::insert_to_generate(IR__::Contained_ptr item) 
{
	// insert interfaces in another list
	switch(item->describe()->kind) {
	case CORBA__::dk_Interface :
	case CORBA__::dk_Home :
	case CORBA__::dk_Component :
	case CORBA__::dk_Composition :
	case CORBA__::dk_AbstractStorageHome :
	case CORBA__::dk_AbstractStorageType :
	case CORBA__::dk_StorageHome :
	case CORBA__::dk_StorageType :
		m_to_generate_interface_seq->length(m_to_generate_interface_seq->length()+1);
		m_to_generate_interface_seq[m_to_generate_interface_seq->length()-1] = IR__::Contained::_duplicate(item);
		break;
	default :
		m_to_generate_seq->length(m_to_generate_seq->length()+1);
		m_to_generate_seq[m_to_generate_seq->length()-1] = IR__::Contained::_duplicate(item);
		break;
	}
}


void
GeneratorBase::check_for_generation(IR__::Contained_ptr item) 
{
	insert_to_generate(item);
}


bool 
GeneratorBase::item_well_known(IR__::Contained_ptr item)
{
	//
	// check if item is well known
	//
	IR__::Contained_var restricted_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(restricted_contained )) 
	{
		std::string id = restricted_contained ->id();

		if ((!id.compare("IDL:Deployment:1.0")) ||
		    (!id.compare("IDL:omg.org/Components:1.0")) ||
		    (!id.compare("IDL:Components:1.0")) ||
		    (!id.compare("IDL:omg.org/CORBA:1.0")) ||
		    (!id.compare("IDL:CORBA:1.0")) ||
			(!id.compare("IDL:omg.org/CosPropertyService:1.0")))
		{
			return true;
		};
	}

	return false;
}


//
// start generation
//
void
GeneratorBase::doGenerate()
{
	if (CORBA::is_nil(target_))
	{
		std::cerr << "--- error - not initialized" << std::endl;
		return;
	}

	//
	// merge the two lists
	//
	CORBA::ULong start = m_to_generate_seq->length();
	CORBA::ULong end = start + m_to_generate_interface_seq->length();
	m_to_generate_seq->length(end);
	for(CORBA::ULong index = 0; start < end; start++, index++)
	{
		m_to_generate_seq[start] = IR__::Contained::_duplicate(m_to_generate_interface_seq[index]);
	}

	//
	// generate for all items of the generation list
	//
	CORBA::ULong len = m_to_generate_seq->length();
	for (CORBA::ULong i = 0; i < len ; i++) {
		generate_the_item ((*m_to_generate_seq)[i]);
	}
}


void
GeneratorBase::generate_the_item ( IR__::Contained_ptr item )
{
	std::cout << "Debug: item to generate: " << item->id() << std::endl;
	switch (item->describe()->kind) {
	case CORBA__::dk_Module: {
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(item);
		doModule(a_module);
		break; }
	case CORBA__::dk_Home: {
		IR__::HomeDef_var a_home = IR__::HomeDef::_narrow(item);
		doHome(a_home);
		break; }
	case CORBA__::dk_Component: {
		IR__::ComponentDef_var a_component = IR__::ComponentDef::_narrow(item);
		doComponent(a_component);
		break; }
	case CORBA__::dk_Interface: {
		IR__::InterfaceDef_var a_interface = IR__::InterfaceDef::_narrow(item);
		doInterface(a_interface);
		break; }
	case CORBA__::dk_Value: {
		IR__::EventDef_var a_event = IR__::EventDef::_narrow(item);
		if (!CORBA::is_nil (a_event)) {
			doEvent(a_event);
		} else {
			IR__::ValueDef_var a_value = IR__::ValueDef::_narrow(item);
			doValue(a_value);
		}
		break; }
	case CORBA__::dk_Alias: {
		IR__::AliasDef_var a_alias = IR__::AliasDef::_narrow(item);
		doAlias(a_alias);
		break; }
	case CORBA__::dk_Exception: {
		IR__::ExceptionDef_var a_exception = IR__::ExceptionDef::_narrow(item);
		doException(a_exception);
		break; }
	case CORBA__::dk_Enum: {
		IR__::EnumDef_var a_enum = IR__::EnumDef::_narrow(item);
		doEnum(a_enum);
		break; }
	case CORBA__::dk_Struct: {
		IR__::StructDef_var a_struct = IR__::StructDef::_narrow(item);
		doStruct(a_struct);
		break; }
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(item);
		doComposition(a_composition);
		break; }
    case CORBA__::dk_AbstractStorageHome : {
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(item);
		doAbstractStorageHome(abs_storagehome);
		break; }
	case CORBA__::dk_StorageHome : {
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(item);
		doStorageHome(storagehome);
		break; }
	case CORBA__::dk_AbstractStorageType : {
		IR__::AbstractStorageTypeDef_var abs_storagetype = IR__::AbstractStorageTypeDef::_narrow(item);
		doAbstractStorageType(abs_storagetype);
		break; }
	case CORBA__::dk_StorageType : {
		IR__::StorageTypeDef_var storagetype = IR__::StorageTypeDef::_narrow(item);
		doStorageType(storagetype);
		break; }
	default:
		break;
	};
}


//
// module
//
void 
GeneratorBase::handleModule(IR__::ModuleDef_ptr module)
{
	IR__::ContainedSeq_var contained_seq = module->contents(CORBA__::dk_Module, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(((*contained_seq)[i]));
		doModule(a_module);
	}
}


void
GeneratorBase::doModule(IR__::ModuleDef_ptr module)
{
}


//
// interface
//
void 
GeneratorBase::handleSupportedInterface(IR__::ComponentDef_ptr component)
{
	IR__::InterfaceDefSeq_var supported_seq = component->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		doInterface((*supported_seq)[i]);
	}
}


void 
GeneratorBase::handleSupportedInterface(IR__::StorageTypeDef_ptr storage_type)
{
	IR__::InterfaceDefSeq_var supported_seq = storage_type->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		doInterface((*supported_seq)[i]);
	}
}


void
GeneratorBase::doInterface(IR__::InterfaceDef_ptr intface)
{
}


//
// attribute
//
void 
GeneratorBase::handleAttribute(IR__::Container_ptr c)
{
	IR__::ContainedSeq_var contained_seq = c->contents(CORBA__::dk_Attribute, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		doAttribute(a_attribute);
	}
}


void
GeneratorBase::doAttribute(IR__::AttributeDef_ptr attribute)
{
}


//
// operation
//
void 
GeneratorBase::handleOperation(IR__::InterfaceDef_ptr intf)
{
	IR__::ContainedSeq_var contained_seq = intf->contents(CORBA__::dk_Operation, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::OperationDef_var a_operation = IR__::OperationDef::_narrow(((*contained_seq)[i]));
		doOperation(a_operation);
	}
}


void
GeneratorBase::doOperation(IR__::OperationDef_ptr operation)
{
}


//
// factory
//
void
GeneratorBase::handleFactory(IR__::HomeDef_ptr home)
{
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Factory, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FactoryDef_var a_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		doFactory(a_factory);
	}
}

void 
GeneratorBase::handleFactory(IR__::AbstractStorageHomeDef_ptr abs_storage_home)
{
	IR__::ContainedSeq_var contained_seq = abs_storage_home->contents(CORBA__::dk_Factory, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FactoryDef_var a_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		doFactory(a_factory, abs_storage_home);
	}
}

void 
GeneratorBase::handleFactory(IR__::StorageHomeDef_ptr storage_home)
{
	IR__::ContainedSeq_var contained_seq = storage_home->contents(CORBA__::dk_Factory, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FactoryDef_var a_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		doFactory(a_factory, storage_home);
	}
}

void
GeneratorBase::doFactory(IR__::FactoryDef_ptr factory)
{
}

void 
GeneratorBase::doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def)
{
}

//
// finder
//
void
GeneratorBase::handleFinder(IR__::HomeDef_ptr home)
{
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Finder, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FinderDef_var a_finder = IR__::FinderDef::_narrow(((*contained_seq)[i]));
		doFinder(a_finder);
	}
}


void
GeneratorBase::doFinder(IR__::FinderDef_ptr finder)
{
}


//
// event type
//
void
GeneratorBase::doEvent(IR__::EventDef_ptr event)
{
	IR__::ContainedSeq_var contained_seq = event->contents(CORBA__::dk_all, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		// contained members
		if (((*contained_seq)[i])->def_kind() == CORBA__::dk_ValueMember)
		{
			IR__::ValueMemberDef_var act_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
			doValueMember(act_member);
		}
	}
}


//
// value type
//
void
GeneratorBase::doValue(IR__::ValueDef_ptr value)
{
/*	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_all, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		// contained members
		if (((*contained_seq)[i])->def_kind() == CORBA__::dk_ValueMember)
		{
			IR__::ValueMemberDef_var act_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
			doValueMember(act_member);
		}
	}*/
}


//
// value member
//
void 
GeneratorBase::handleValueMember(IR__::ValueDef_ptr value)
{
	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ValueMemberDef_var act_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
		doValueMember(act_member);
	}
}


void
GeneratorBase::doValueMember(IR__::ValueMemberDef_ptr member)
{
}


//
// exception
//
void
GeneratorBase::handleException(IR__::Contained_ptr contained)
{
	IR__::ExceptionDefSeq_var exception_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	switch(contained->def_kind())
	{
	case CORBA__::dk_Attribute : {
		IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(contained);
		exception_seq = a_attribute->get_exceptions();
		len = exception_seq->length();
		for(i = 0; i < len; i++)
		{
			doException(exception_seq[i]);
		}
		break; }
	case CORBA__::dk_Factory :
	case CORBA__::dk_Finder :
	case CORBA__::dk_Key :
	case CORBA__::dk_Operation : {
		IR__::OperationDef_var a_operation = IR__::OperationDef::_narrow(contained);
		exception_seq = a_operation->exceptions();
		len = exception_seq->length();
		for(i = 0; i < len; i++)
		{
			doException(exception_seq[i]);
		}
		break; }
	default : {
		IR__::Container_var a_container = IR__::Container::_narrow(contained);
		IR__::ContainedSeq_var contained_seq = a_container->contents(CORBA__::dk_Exception, false);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			IR__::ExceptionDef_var a_exception = IR__::ExceptionDef::_narrow(((*contained_seq)[i]));
			doException(a_exception);
		}
		break; }
	}
}


void
GeneratorBase::doException(IR__::ExceptionDef_ptr except)
{
}


//
// enum
//
void
GeneratorBase::handleEnum(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Enum, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::EnumDef_var a_enum = IR__::EnumDef::_narrow(((*contained_seq)[i]));
		doEnum(a_enum);
	}
}


void
GeneratorBase::doEnum(IR__::EnumDef_ptr enumeration)
{
}


//
// constant
//
void
GeneratorBase::handleConstant(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Constant, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ConstantDef_var a_constant = IR__::ConstantDef::_narrow(((*contained_seq)[i]));
		doConstant(a_constant);
	}
}


void
GeneratorBase::doConstant(IR__::ConstantDef_ptr constant)
{
}


//
// typedef
//
void 
GeneratorBase::handleTypedef(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Typedef, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::TypedefDef_var a_typedef = IR__::TypedefDef::_narrow(((*contained_seq)[i]));
		doTypedef(a_typedef);
	}
}


void
GeneratorBase::doTypedef(IR__::TypedefDef_ptr tdef)
{
}

//
// alias
//
void
GeneratorBase::handleAlias(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Alias, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::AliasDef_var a_alias = IR__::AliasDef::_narrow(((*contained_seq)[i]));
		doAlias(a_alias);
	}
}


void
GeneratorBase::doAlias(IR__::AliasDef_ptr adef)
{
}


//
// struct
//
void
GeneratorBase::handleStruct(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Struct, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::StructDef_var a_struct = IR__::StructDef::_narrow(((*contained_seq)[i]));
		doStruct(a_struct);
	}
}


void
GeneratorBase::doStruct(IR__::StructDef_ptr sdef)
{
}


//
// union
//
void
GeneratorBase::handleUnion(IR__::Container_ptr container)
{
	IR__::ContainedSeq_var contained_seq = container->contents(CORBA__::dk_Union, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::UnionDef_var a_union = IR__::UnionDef::_narrow(((*contained_seq)[i]));
		doUnion(a_union);
	}
}


void
GeneratorBase::doUnion(IR__::UnionDef_ptr udef)
{
}


//
// home
//
void 
GeneratorBase::handleHome(IR__::Container_ptr cont)
{
	IR__::ContainedSeq_var contained_seq = cont->contents(CORBA__::dk_Home, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::HomeDef_var a_home = IR__::HomeDef::_narrow(((*contained_seq)[i]));
		doHome(a_home);
	}
}


void
GeneratorBase::doHome(IR__::HomeDef_ptr home)
{
}


//
// component
//
void
GeneratorBase::doComponent(IR__::ComponentDef_ptr component)
{
}


//
// provides
//
void 
GeneratorBase::handleProvides(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		doProvides(act_provides, component);
	}
}


void
GeneratorBase::doProvides(IR__::ProvidesDef_ptr provides, IR__::ComponentDef_ptr component)
{
}


//
// uses
//
void 
GeneratorBase::handleUses(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::UsesDef_var act_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		doUses(act_uses, component);
	}
}


void
GeneratorBase::doUses(IR__::UsesDef_ptr Uses, IR__::ComponentDef_ptr component)
{
}


//
// emits
//
void
GeneratorBase::handleEmits(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Emits, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::EmitsDef_var act_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
		doEmits(act_emits, component);
	}
}


void
GeneratorBase::doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component)
{
}


//
// publishes
//
void
GeneratorBase::handlePublishes(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Publishes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) 
	{
		IR__::PublishesDef_var act_publishes = IR__::PublishesDef::_narrow(((*contained_seq)[i]));
		doPublishes(act_publishes, component);
	}
}


void
GeneratorBase::doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component)
{
}


//
// consumes
//
void 
GeneratorBase::handleConsumes(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Consumes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ConsumesDef_var a_consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		doConsumes(a_consumes, component);
	}
}


void
GeneratorBase::doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component)
{
}


//
// sink
//
void 
GeneratorBase::handleSink(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Sink, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::SinkDef_var act_sink = IR__::SinkDef::_narrow(((*contained_seq)[i]));
		doSink(act_sink, component);
	}
}


void
GeneratorBase::doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component)
{
}


//
// source
//
void 
GeneratorBase::handleSource(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Source, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::SourceDef_var a_source = IR__::SourceDef::_narrow(((*contained_seq)[i]));
		doSource(a_source, component);
	}
}


void
GeneratorBase::doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component)
{
}

//
// composition
//
void 
GeneratorBase::handleComposition(CIDL::CIDLRepository_ptr repository)
{
	IR__::ContainedSeq_var contained_seq = repository_->contents(CORBA__::dk_Composition, true);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(((*contained_seq)[i]));
		doComposition(a_composition);
	}
}


void
GeneratorBase::doComposition(CIDL::CompositionDef_ptr composition)
{
}

//
// abstract storage home
//
void 
GeneratorBase::handleAbstractStorageHome(IR__::Container_ptr cont)
{
	IR__::ContainedSeq_var contained_seq = cont->contents(CORBA__::dk_AbstractStorageHome, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(((*contained_seq)[i]));
		doAbstractStorageHome(abs_storagehome);
	}
}

void 
GeneratorBase::doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storage_home)
{
}

//
// storage home
//
void 
GeneratorBase::handleStorageHome(IR__::Container_ptr cont)
{
	IR__::ContainedSeq_var contained_seq = cont->contents(CORBA__::dk_StorageHome, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(((*contained_seq)[i]));
		doStorageHome(storagehome);
	}
}

void 
GeneratorBase::doStorageHome(IR__::StorageHomeDef_ptr storage_home)
{
}

//
// abstract storage type
//
void 
GeneratorBase::doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storage_type)
{
}

//	
// storage type
//
void 
GeneratorBase::doStorageType(IR__::StorageTypeDef_ptr storage_type)
{
}

//
// Key
//
void 
GeneratorBase::handleKey(IR__::InterfaceDef_ptr inf_def)
{
	IR__::ContainedSeq_var contained_seq = inf_def->contents(CORBA__::dk_Key, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::KeyDef_var a_key = IR__::KeyDef::_narrow(((*contained_seq)[i]));
		doKey(a_key, inf_def);
	}
}

void 
GeneratorBase::doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def)
{
}

} // namespace
