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

#ifndef __CAD_READER_H__
#define __CAD_READER_H__


#include "Package.h"
#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "AssemblyData.h"
#include "DestinationData.h"
#include <string>


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


/**
 * exception
 */
class CADReadException
{
};


/**
 * read component assembly descriptor
 */
class QEDOUTIL_API CADReader
{

private:

    /** the parsed assembly descriptor */
	DOMDocument*								cad_document_;
	/** assembly data */
	AssemblyData*								data_;
	/** the Software Package */
	Package*									package_;
	/** the path to drop files from the package*/
	std::string									path_;

	/**
	 * action
	 */
	ScriptData action (DOMElement*)
		throw(CADReadException);

	/**
	 * activation
	 */
	ReferenceData activation (DOMElement*)
		throw(CADReadException);

	/**
	 * binding
	 */
	void binding (DOMElement*)
		throw(CADReadException);

	/**
	 * componentassembly
	 */
	void componentassembly (DOMElement*)
        throw(CADReadException);

	/**
	 * componentfile
	 */
	void componentfile (DOMElement*)
		throw(CADReadException);

	/**
	 * componentfiles
	 */
	void componentfiles (DOMElement*)
		throw(CADReadException);

	/**
	 * componentfileref
	 */
	std::string componentfileref (DOMElement*)
		throw(CADReadException);

	/**
	 * componentimplref
	 */
	std::string componentimplref (DOMElement*)
		throw(CADReadException);

	/**
	 * componentinstantiation
	 */
	ComponentInstanceData componentinstantiation (DOMElement*)
		throw(CADReadException);

	/*
	 * componentinstantiation_two
	 */
	ComponentInstanceData componentinstantiation_two (DOMElement*)
		throw(CADReadException);

	/**
	 * componentinstantiationref
	 */
	std::string componentinstantiationref (DOMElement*)
		throw(CADReadException);

	/**
	 * componentproperties
	 */
	std::string componentproperties (DOMElement*)
		throw(CADReadException);

	/* 
	 * componentproperties_two
	 * is need for qedo controller
	 */
	std::string componentproperties_two (DOMElement*)
		throw(CADReadException);

	/**
	 * componentsupportedinterface
	 */
	ReferenceData componentsupportedinterface (DOMElement*)
		throw(CADReadException);

	/**
	 * condition
	 */
	ScriptData condition (DOMElement*)
		throw(CADReadException);

	/**
	 * connectevent
	 */
	void connectevent (DOMElement*)
		throw(CADReadException);

	/**
	 * connecthomes
	 */
	void connecthomes (DOMElement*)
		throw(CADReadException);

	/**
	 * connectinterface
	 */
	void connectinterface (DOMElement*)
		throw(CADReadException);

	/**
	 * connections
	 */
	void connections (DOMElement*)
		throw(CADReadException);

	/**
	 * consumesidentifier
	 */
	std::string consumesidentifier (DOMElement*)
		throw(CADReadException);

	/**
	 * consumesport
	 */
	PortData consumesport (DOMElement*)
		throw(CADReadException);

	/**
	 * description
	 */
	std::string description (DOMElement*)
		throw(CADReadException);

    /**
	 * return the destination for placement
	 */
	DestinationData destination (DOMElement*)
        throw(CADReadException);

	/*
	 * destination_two need for qedo controller
	 */
	DestinationData destination_two (DOMElement*)
        throw(CADReadException);


	/**
	 * emitsidentifier
	 */
	std::string emitsidentifier (DOMElement*)
		throw(CADReadException);

	/**
	 * emitsport
	 */
	PortData emitsport (DOMElement*)
		throw(CADReadException);

	/**
	 * executableplacement
	 */
	void executableplacement (DOMElement*)
		throw(CADReadException);

	/**
	 * existinginterface
	 */
	ReferenceData existinginterface (DOMElement*)
		throw(CADReadException);

	/**
	 * extension elements
	 */
    void extension (DOMElement*)
        throw(CADReadException);

	/**
	 * extension_two is need for qedo controller
	 */
	Extension extension_two(DOMElement*)
		throw(CADReadException);

	/**
	 * fileinarchive
	 */
	FileData fileinarchive (DOMElement*)
        throw(CADReadException);

	/**
	 * fileinarchive_two
	 * is need for qedo controller
	 */
	FileData fileinarchive_two (DOMElement*)
		throw(CADReadException);


    /**
	 * findby
	 */
    ReferenceData findby (DOMElement*)
        throw(CADReadException);

	/**
	 * get the HomeInstanceData - need for qedo controller
	 */

	std::vector <HomeInstanceData> findHomeInstanceData(DOMElement*)
		throw(CADReadException);

	/**
	 * get the Hostcollocation - need for qedo controller
	 */
	std::vector <HostData> findHostData (DOMElement*)
		throw(CADReadException);

	/**
	 * get the Processcollocation - need for qedo controller
	 */
	std::vector <ProcessData> findProcessData(DOMElement*)
		throw(CADReadException);

	/**
	 * get Partitioning Data - need for qedo controller
	 */
	Qedo::Partitioning findPartitioningData(DOMElement*)
		throw(CADReadException);

	/**
	 * homefinder
	 */
	std::string homefinder (DOMElement*)
        throw(CADReadException);

	/**
	 * homeinterface
	 */
	ReferenceData homeinterface (DOMElement*)
        throw(CADReadException);

	/**
	 * homeplacement
	 */
	HomeInstanceData homeplacement (DOMElement*)
        throw(CADReadException);

	/**
	 * homeplacement_two need for qedo controller
	 */
	HomeInstanceData homeplacement_two (DOMElement*)
        throw(CADReadException);

	/**
	 * homeplacementref
	 */
	std::string homeplacementref (DOMElement*)
        throw(CADReadException);

	/**
	 * homeproperties
	 */
	std::string homeproperties (DOMElement*)
        throw(CADReadException);

	/**
	 * hostcollocation
	 */
	HostData hostcollocation (DOMElement*)
        throw(CADReadException);

	/**
	 * hostcollocation_two is need for qedo controller
	 */
	HostData hostcollocation_two (DOMElement*)
		throw(CADReadException);
	/**
	 * installation
	 */
	ReferenceData installation (DOMElement*)
		throw(CADReadException);

	/**
	 * link
	 */
	std::string link (DOMElement*)
        throw(CADReadException);

	/**
	 * namingservice
	 */
	std::string namingservice (DOMElement*)
        throw(CADReadException);

	/**
	 * node
	 */
	std::string node (DOMElement*)
        throw(CADReadException);

	/**
	 * partitioning
	 */
	void partitioning (DOMElement*)
        throw(CADReadException);

	/**
	 * partitioning data - is need for qedo controller
	 */
	//Partitioning partitioning_data(DOMElement*)
	//	throw(CADReadException);


	/**
	 * find homeplacement for qedo controller
	 */
	std::vector <HomeInstanceData> partitioning_homeplacement (DOMElement*)
		throw(CADReadException);

	/*
	 * find hostcollocation for qedo controller
	 */
	std::vector <HostData> partitioning_hostdata(DOMElement*)
		throw(CADReadException);
	/*
	 * find processcollocation for qedo controller
	 */
	std::vector <ProcessData> partitioning_processdata(DOMElement*)
		throw(CADReadException);

	/**
	 * processcollocation
	 */
	ProcessData processcollocation (DOMElement*)
        throw(CADReadException);

	/*
	 * processcollocation_two need for qedo controller
	 */
	ProcessData processcollocation_two (DOMElement*)
        throw(CADReadException);


	/**
	 * providesidentifier
	 */
	std::string providesidentifier (DOMElement*)
        throw(CADReadException);

	/**
	 * providesport
	 */
	PortData providesport (DOMElement*)
        throw(CADReadException);

	/**
	 * publishesidentifier
	 */
	std::string publishesidentifier (DOMElement*)
        throw(CADReadException);

	/**
	 * publishesport
	 */
	PortData publishesport (DOMElement*)
		throw(CADReadException);

	/**
	 * registercomponent
	 */
	void registercomponent (DOMElement*, ComponentInstanceData&)
        throw(CADReadException);

	/**
	 * registerwithhomefinder
	 */
	std::string registerwithhomefinder (DOMElement*)
        throw(CADReadException);

	/**
	 * registerwithnaming
	 */
	std::string registerwithnaming (DOMElement*)
        throw(CADReadException);

	/**
	 * registerwithtrader
	 */
	std::string registerwithtrader (DOMElement*)
        throw(CADReadException);

	/**
	 * rule
	 */
	RuleData rule (DOMElement*)
        throw(CADReadException);

	

	/**
	 * scriptcode
	 */
	std::string scriptcode (DOMElement*)
        throw(CADReadException);

	/**
	 * sinkport
	 */
	PortData sinkport (DOMElement*)
		throw(CADReadException);
	 

	/**
	 * sourceport
	 */
	PortData sourceport (DOMElement*)
		throw(CADReadException);
	 

	/**
	 * stringifiedobjectref
	 */
	std::string stringifiedobjectref (DOMElement*)
        throw(CADReadException);

	/**
	 * traderquery
	 */
	void traderquery (DOMElement*)
        throw(CADReadException);

	/**
	 * usagename
	 */
	std::string usagename (DOMElement*)
        throw(CADReadException);

	/**
	 * usesidentifier
	 */
	std::string usesidentifier (DOMElement*)
        throw(CADReadException);

	/**
	 * usesport
	 */
	PortData usesport (DOMElement*)
        throw(CADReadException);

public:

	/**
	 * constructor
	 */
	CADReader();

	/**
	 * destructor
	 */
	virtual ~CADReader();

	/**
	 * read CAD
	 */
	void readCAD(std::string package, AssemblyData* data, std::string path)
		throw(CADReadException);



	/*
	 **************************************************
	 * need for qedo controller to edit the destination
	 **************************************************
	 */

	Qedo::Partitioning getPartitioning(std::string cadfile)
		throw(CADReadException);

	std::vector <HostData> getHostcollocations(std::string cadfile)
		throw(CADReadException);

	std::vector <ProcessData> getProcesscollocations(std::string cadfile)
		throw(CADReadException);

	std::vector <HomeInstanceData> getHomeplacements(std::string cadfile)
		throw(CADReadException);

};

/** @} */

}

#endif

