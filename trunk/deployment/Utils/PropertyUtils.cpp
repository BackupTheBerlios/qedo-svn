/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#include "PropertyUtils.h"
#include "PropertySimple.hpp"
#include "PropertyStructandSequence.hpp"
#include "ATParser.hpp"

void PropertyUtils::convert_prop_to_config_value ( XMLDOMParser::Property* prop, Components::ConfigValue** value )
{
	try{
	if ( prop -> proptype() == XMLDOMParser::Property::SIMPLE )
	{
		OBV_Components::ConfigValue* cv_ = new OBV_Components::ConfigValue;
		CORBA::Any member_;
		XMLDOMParser::PropertySimple* sprop_ = dynamic_cast <XMLDOMParser::PropertySimple*> (prop);

		cv_ -> name ( CORBA::string_dup ( (prop -> name()).c_str() ));
		if ( prop -> type() == "long")
		{
			CORBA::Long l_ = atoi ((sprop_->value()).c_str());
			member_ <<= l_;
		}
		if ( prop -> type() == "string")
		{
			CORBA::String_var s_ = CORBA::string_dup((sprop_->value()).c_str());
			member_ <<= s_;
		}

		cv_ ->value( member_);
		*value = cv_;
		return;
	}
	else if ( prop -> proptype() == XMLDOMParser::Property::STRUCT )
	{
		OBV_Components::ConfigValue* cv_ = new OBV_Components::ConfigValue;
		CORBA::Any member_;
		XMLDOMParser::PropertyStruct* sprop_ = dynamic_cast <XMLDOMParser::PropertyStruct*> (prop);
		cv_ -> name ( CORBA::string_dup ( (prop -> name()).c_str() ));
		
		XMLDOMParser::PropertyList *list_;
		XMLDOMParser::PropertyList::iterator i_;
		list_ = sprop_ ->proplist();

		Components::ConfigValues *cvlist_ = new Components::ConfigValues;
		long elem_ = 0;

		for ( i_ = list_->begin(); i_ != list_->end(); i_++)
		{
			Components::ConfigValue* mem_;
			convert_prop_to_config_value ((*i_), &mem_ );
			cvlist_->length (++elem_);
			(*cvlist_)[elem_-1] = mem_;	
			
		}
		member_ <<= cvlist_;
		cv_ ->value( member_ );
		*value = cv_;
		return ;
	}
	else if ( prop -> proptype() == XMLDOMParser::Property::SEQUENCE )
	{
		OBV_Components::ConfigValue* cv_ = new OBV_Components::ConfigValue;
		CORBA::Any member_;
		XMLDOMParser::PropertySequence* sprop_ = dynamic_cast <XMLDOMParser::PropertySequence*> (prop);
		cv_ -> name ( CORBA::string_dup ( (prop -> name()).c_str() ));
		
		XMLDOMParser::PropertySimpleList *simplelist_;
		XMLDOMParser::PropertySimpleList::iterator simplei_;
		simplelist_ = sprop_ ->simplelist();

		XMLDOMParser::PropertyStructList *structlist_;
		XMLDOMParser::PropertyStructList::iterator structi_;
		structlist_ = sprop_ ->structlist();

		XMLDOMParser::PropertySequenceList *sequencelist_;
		XMLDOMParser::PropertySequenceList::iterator sequencei_;
		sequencelist_ = sprop_ ->sequencelist();

		Components::ConfigValues *cvlist_ = new Components::ConfigValues;
		long elem_ = 0;
		if (simplelist_)
		{
			for ( simplei_ = simplelist_->begin(); simplei_ != simplelist_->end(); simplei_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*simplei_), &mem_ );
				cvlist_->length (++elem_);
				(*cvlist_)[elem_-1] = mem_;		
			}
		}
		if (structlist_)
		{
			for ( structi_ = structlist_->begin(); structi_ != structlist_->end(); structi_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*structi_), &mem_ );
				cvlist_->length (++elem_);
				(*cvlist_)[elem_-1] = mem_;		
			}
		}
		if (sequencelist_)
		{
			for ( sequencei_ = sequencelist_->begin(); sequencei_ != sequencelist_->end(); sequencei_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*sequencei_), &mem_ );
				cvlist_->length (++elem_);
				(*cvlist_)[elem_-1] = mem_;
			}
		}

		member_ <<= cvlist_;
		cv_ ->value( member_ );
		*value = cv_;
		return ;
	}
	}
	catch (...)
	{
		std::cerr <<"cannot transform properties to config values!!" <<"\n";
		value = 0;
	}
}

void PropertyUtils::parser_properties_and_convert ( const string& xmldoc, Components::ConfigValues& val)
{
	if ( xmldoc == "") 
		return;
	XMLDOMParser::ATParser* parser_;
	try
    {
         XMLPlatformUtils::Initialize();


		 parser_ = new XMLDOMParser::ATParser;
		parser_->initialize_Parser (true, true, DOMParser::Val_Auto );

    }
	catch(...)
	{
		std::cerr << "excpetion during Initializing of the parser!" << "\n";
	};


	string filename = "xmlxxxtmp.xml";
	ofstream str_;
	str_.open (filename.c_str());
	str_ << xmldoc;
	str_.close();


	XMLDOMParser::Properties* props = parser_->parse_properties(parser_->create_tree(filename.c_str()));
//	Utility_class::suppression(fileneame, true) 

	if (props)
	{
		XMLDOMParser::PropertySimpleList *simplelist_;
		XMLDOMParser::PropertySimpleList::iterator simplei_;
		simplelist_ = props ->simpleproperties();

		XMLDOMParser::PropertyStructList *structlist_;
		XMLDOMParser::PropertyStructList::iterator structi_;
		structlist_ = props ->structproperties();

		XMLDOMParser::PropertySequenceList *sequencelist_;
		XMLDOMParser::PropertySequenceList::iterator sequencei_;
		sequencelist_ = props ->sequenceproperties();
 		long elem_ = 0;

		if (simplelist_)
		{
			for ( simplei_ = simplelist_->begin(); simplei_ != simplelist_->end(); simplei_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*simplei_), &mem_ );
				val.length (++elem_);
				val[elem_-1] = mem_;		
			}
		}
		if (structlist_)
		{
			for ( structi_ = structlist_->begin(); structi_ != structlist_->end(); structi_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*structi_), &mem_ );
				val.length (++elem_);
				val[elem_-1] = mem_;		
			}
		}
		if (sequencelist_)
		{
			for ( sequencei_ = sequencelist_->begin(); sequencei_ != sequencelist_->end(); sequencei_++)
			{
				Components::ConfigValue* mem_;
				convert_prop_to_config_value ((*sequencei_), &mem_ );
				val.length (++elem_);
				val[elem_-1] = mem_;
			}
		}

	
	}

	
}

