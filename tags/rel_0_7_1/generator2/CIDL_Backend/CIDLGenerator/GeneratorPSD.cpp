/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/
#include "GeneratorPSD.h"


namespace QEDO_CIDL_Generator {

GeneratorPSD::GeneratorPSD
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}

GeneratorPSD::~GeneratorPSD
()
{
	if(!lValueTypes_.empty())
	{
		std::list<IR__::ValueDef_ptr>::iterator valuetype_iter;
	
		for(valuetype_iter = lValueTypes_.begin();
			valuetype_iter != lValueTypes_.end();
			valuetype_iter++)
		{
			//(dynamic_cast <IR__::ValueDef_ptr> (*valuetype_iter))->_remove_ref();
		}

		lValueTypes_.clear();
	}
}

void
GeneratorPSD::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }
	
	strFilename_ = file_prefix_ + ".psd";
	
	out.open(strFilename_.c_str());
	out << "<?xml version = '1.0' ?>\n";
	out << "<!DOCTYPE corbacomponent PUBLIC \"-//OMG//DTD CORBA Persistence Descriptor\">\n\n\n";
	out << "<corbapersistence>\n\n";
	out.indent();
	
	//Since a container is accessible only to one certain database, the database information in 
	//.psd is not neccessary anymore
	/*
	out << "<!-- database-info must be specified before all of storagehome's definition -->\n";
	out << "<database-info>\n";
	out.indent();
	out << "<dbname></dbname>\n\n";
	out << "<connection>\n";
	out.indent();
	out << "<param name=\"\" value=\"\"/>\n";
	out << "<param name=\"\" value=\"\"/>\n";
	out.unindent();
	out << "</connection>\n";
	out.unindent();
	out << "</database-info>\n\n";
	*/
	
	doGenerate();
	out.unindent();
	out << "</corbapersistence>\n";
	out.close();
}

void
GeneratorPSD::check_for_generation(IR__::Contained_ptr item)
{
	// check if item is already known
	if (item_well_known(item))
		return;

	// check if item is already in the list or currently processed
	if ((this->sRecursion_.find(item->id())) != sRecursion_.end() || this->already_included (item))
		return;
	else
		sRecursion_.insert(item->id());

	CORBA::ULong i;
	CORBA::ULong ulLen;

	switch (item->def_kind())
	{
	case CORBA__::dk_Module : 
	{
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(item);

		// modules
		IR__::ContainedSeq_var contained_seq = a_module->contents(CORBA__::dk_Module, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		// abstract storagehomes
		contained_seq = a_module->contents(CORBA__::dk_AbstractStorageHome, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		// storagehomes
		contained_seq = a_module->contents(CORBA__::dk_StorageHome, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		// valuetypes
		contained_seq = a_module->contents(CORBA__::dk_Value, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
		{
			IR__::ValueDef_ptr value = IR__::ValueDef::_narrow((*contained_seq)[i]);
			lValueTypes_.push_back(value);
		}

		break; 
	}
	case CORBA__::dk_AbstractStorageHome :
	{
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(item);
		
		IR__::InterfaceDefSeq_var abs_storagehome_seq = abs_storagehome->base_abstract_storagehomes();
		for(i=0; i<abs_storagehome_seq->length(); i++)
			check_for_generation((*abs_storagehome_seq)[i]);

		// insert this interface in generation list
		this->insert_to_generate(item);

		break;
	}
	case CORBA__::dk_StorageHome : 
	{
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(item);
		// insert this interface in generation list
		this->insert_to_generate(item);

		break;
	}
	default:
		break;
	};

	sRecursion_.erase(item->id());
};

IR__::AttributeDefSeq 
GeneratorPSD::collectStateMembers(IR__::InterfaceDef_ptr inf_def, CORBA__::CollectStyle style)
{
	IR__::AttributeDefSeq state_members;

	IR__::AbstractStorageTypeDef_var abs_storagetype =
		IR__::AbstractStorageTypeDef::_narrow(inf_def);
	if(!CORBA::is_nil(abs_storagetype))
		abs_storagetype->get_state_members(state_members, style);

	IR__::StorageTypeDef_var storagetype = 
		IR__::StorageTypeDef::_narrow(inf_def);
	if(!CORBA::is_nil(storagetype))
		storagetype->get_state_members(state_members, style);

	return state_members;
}

void 
GeneratorPSD::doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome)
{
	std::string table_name = string(abs_storagehome->name());
	IR__::AbstractStorageTypeDef_var abs_storagetype = abs_storagehome->managed_abstract_storagetype();
	IR__::AttributeDefSeq state_members = collectStateMembers(abs_storagetype, CORBA__::dk_Self);

	out << "<storagehome id=\"PSDL:" << table_name << ":1.0\">\n";
	IR__::AttributeDef_var attribute = 0;

	out.indent();
	CORBA::ULong i;
	for( i=0; i<state_members.length(); i++)
	{
		attribute = IR__::AttributeDef::_narrow(state_members[i]);
		if( attribute->type_def()->type()->kind() == CORBA::tk_value )
		{
			std::list<IR__::ValueDef_ptr>::iterator valuetype_iter;
			for(valuetype_iter = lValueTypes_.begin();
				valuetype_iter != lValueTypes_.end();
				valuetype_iter++)
			{
				IR__::ValueDef_var value = IR__::ValueDef::_narrow(*valuetype_iter);
				string attr_type_name = map_attribute_type(attribute->type_def());
				if(attr_type_name.find(mapName(value))!=std::string::npos)
				{
					IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, true);
					for(CORBA::ULong j=0; j<contained_seq->length(); j++)
					{
						IR__::ValueMemberDef_var vMember = IR__::ValueMemberDef::_narrow((*contained_seq)[j]);
						out << "<field name=\"" << mapName(vMember) << "\" type=\"" << map_direct_type(vMember->type_def()) << "\" isnull=\"no\"/>\n";
					}
					break;
				}
			}
		}
		else
			out << "<field name=\"" << mapName(attribute) << "\" type=\"" << map_direct_type(attribute->type_def()) <<  "\" isnull=\"yes\"/>\n";
	}

	out << "\n";
	out << "<primary-key>\n";
	out.indent();
	out << "<key name=\"\"/>\n";
	out.unindent();
	out << "</primary-key>\n";

	IR__::InterfaceDefSeq_var abs_storagehome_seq = abs_storagehome->base_abstract_storagehomes();
	if(abs_storagehome_seq->length()>0)
	{
		out << "\n";
		out << "<independency>\n";
		out.indent();
		for(i=0; i<abs_storagehome_seq->length(); i++)
			out << "<ancestor id=\"PSDL:" << ((*abs_storagehome_seq)[i])->name() << ":1.0\"/>\n";
		out.unindent();
		out << "</independency>\n";
	}
	
	out.unindent();
	out << "</storagehome>\n\n";
}

void 
GeneratorPSD::doStorageHome(IR__::StorageHomeDef_ptr storagehome)
{
	std::string table_name = string(storagehome->name());
	IR__::StorageTypeDef_var storagetype = storagehome->managed_storagetype();
	IR__::AttributeDefSeq state_members = collectStateMembers(storagetype, CORBA__::dk_Self);

	out << "<storagehome id=\"PSDL:" << table_name << ":1.0\">\n";
	IR__::AttributeDef_var attribute = 0;

	out.indent();
	CORBA::ULong i;
	for( i=0; i<state_members.length(); i++)
	{
		attribute = IR__::AttributeDef::_narrow(state_members[i]);
		if( attribute->type_def()->type()->kind() == CORBA::tk_value )
		{
			std::list<IR__::ValueDef_ptr>::iterator valuetype_iter;
			for(valuetype_iter = lValueTypes_.begin();
				valuetype_iter != lValueTypes_.end();
				valuetype_iter++)
			{
				IR__::ValueDef_var value = IR__::ValueDef::_narrow(*valuetype_iter);
				string attr_type_name = map_attribute_type(attribute->type_def());
				if(attr_type_name.find(mapName(value))!=std::string::npos)
				{
					IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, true);
					for(CORBA::ULong j=0; j<contained_seq->length(); j++)
					{
						IR__::ValueMemberDef_var vMember = IR__::ValueMemberDef::_narrow((*contained_seq)[j]);
						out << "<field name=\"" << mapName(vMember) << "\" type=\"" << map_direct_type(vMember->type_def()) << "\" isnull=\"no\"/>\n";
					}
					break;
				}
			}
		}
		else
			out << "<field name=\"" << mapName(attribute) << "\" type=\"" << map_direct_type(attribute->type_def()) << "\" isnull=\"yes\"/>\n";
	}
	
	out << "\n";
	out << "<primary-key>\n";
	out.indent();
	out << "<key name=\"\"/>\n";
	out.unindent();
	out << "</primary-key>\n";

	IR__::StorageHomeDef_var base_storagehome = storagehome->base_storagehome();
	IR__::InterfaceDefSeq_var supported_infs = storagehome->supported_interfaces();
	if(base_storagehome || supported_infs->length()>0)
	{
		out << "\n";
		out << "<independency>\n";
		out.indent();
		if(base_storagehome)
			out << "<ancestor id=\"PSDL:" << base_storagehome->name() << ":1.0\"/>\n";

		for(i=0; i<supported_infs->length(); i++)
			out << "<ancestor id=\"PSDL:" << ((*supported_infs)[i])->name() << ":1.0\"/>\n";
		out.unindent();
		out << "</independency>\n";
	}

	out.unindent();
	out << "</storagehome>\n\n";
}

} // namespace
