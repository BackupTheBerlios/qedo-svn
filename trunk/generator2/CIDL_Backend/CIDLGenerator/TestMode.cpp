#include "TestMode.h"

void
frontend_replacement_feed
( QEDO_ComponentRepository::CIDLRepository_impl *repository )
{
	// Component IDL constructs for our example

	// module LooneyToons
	IR__::ModuleDef_var root_module =
		repository -> create_module ( "IDL:LooneyToons:1.0", "LooneyToons", "1.0" );

	// interface LooneyToons::Movie
	IR__::InterfaceDef_var movie_interface =
		root_module -> create_interface (
			"IDL:LooneyToons/Movie:1.0",
			"Movie", "1.0", IR__::InterfaceDefSeq(0),
			false );

	// operation LooneyToons::Movie::play
	// first the parameters
	IR__::ParDescriptionSeq movie_play_parameters;
	movie_play_parameters.length ( 1 );
	movie_play_parameters[0].name = CORBA::string_dup ( "frame_rate" );
	movie_play_parameters[0].type = repository->get_primitive(IR__::pk_ushort)->type();
	movie_play_parameters[0].type_def = repository->get_primitive(IR__::pk_long);
	movie_play_parameters[0].mode = IR__::PARAM_IN;

	IR__::OperationDef_var movie_play_operation =
		movie_interface -> create_operation (
			"IDL:LooneyToons/Movie/play:1.0",
			"play", "1.0", repository->get_primitive(IR__::pk_ushort),
			IR__::OP_NORMAL, movie_play_parameters,
			IR__::ExceptionDefSeq(0),
			IR__::ContextIdSeq(0) );

	// interface LooneyToons::Bird
	IR__::InterfaceDef_var bird_interface =
		root_module -> create_interface (
			"IDL:LooneyToons/Bird:1.0",
			"Bird", "1.0", IR__::InterfaceDefSeq(0),
			false );

	// operation LooneyToons::Bird::fly
	// first the parameters
	IR__::ParDescriptionSeq bird_fly_parameters;
	bird_fly_parameters.length ( 1 );
	bird_fly_parameters[0].name = CORBA::string_dup ( "how_long" );
	bird_fly_parameters[0].type = repository->get_primitive(IR__::pk_long)->type();
	bird_fly_parameters[0].type_def = repository->get_primitive(IR__::pk_long);
	bird_fly_parameters[0].mode = IR__::PARAM_IN;

	IR__::OperationDef_var bird_fly_operation =
		bird_interface -> create_operation (
			"IDL:LooneyToons/Bird/fly:1.0",
			"fly", "1.0", repository->get_primitive(IR__::pk_void),
			IR__::OP_NORMAL, bird_fly_parameters,
			IR__::ExceptionDefSeq(0),
			IR__::ContextIdSeq(0) );

	// interface LooneyToons::Cat
	IR__::InterfaceDef_var cat_interface =
		root_module -> create_interface (
			"IDL:LooneyToons/Cat:1.0",
			"Cat", "1.0", IR__::InterfaceDefSeq(0),
			false );

	// operation LooneyToons::Cat::eat
	// first the parameters
	IR__::ParDescriptionSeq cat_eat_parameters;
	cat_eat_parameters.length ( 1 );
	cat_eat_parameters[0].name = CORBA::string_dup ( "lunch" );
	cat_eat_parameters[0].type = bird_interface -> type();
	cat_eat_parameters[0].type_def = IR__::IDLType::_duplicate ( bird_interface );
	cat_eat_parameters[0].mode = IR__::PARAM_IN;

	IR__::OperationDef_var cat_eat_operation =
		cat_interface -> create_operation (
			"IDL:LooneyToons/Cat/eat:1.0",
			"eat", "1.0", repository->get_primitive(IR__::pk_void),
			IR__::OP_NORMAL, cat_eat_parameters,
			IR__::ExceptionDefSeq(0),
			IR__::ContextIdSeq(0) );

	// interface LooneyToons::Status
	IR__::InterfaceDef_var status_interface =
		root_module -> create_interface (
			"IDL:LooneyToons/Status:1.0",
			"Status", "1.0", IR__::InterfaceDefSeq(0),
			false );

	// operation LooneyToons::Status::length
	IR__::OperationDef_var status_length_operation =
		status_interface -> create_operation (
			"IDL:LooneyToons/Status/length:1.0",
			"length", "1.0", repository->get_primitive(IR__::pk_long),
			IR__::OP_NORMAL, IR__::ParDescriptionSeq(0),
			IR__::ExceptionDefSeq(0),
			IR__::ContextIdSeq(0) );

	// Create the Components module
	IR__::ModuleDef_var components_module =
		repository -> create_module ( "IDL:Components:1.0", "Components", "1.0" );

	// Create the EventBase value
	IR__::ValueDef_var event_base =
		components_module -> create_value (
			"IDL:Components/EventBase:1.0", "EventBase", "1.0",
			false, true, IR__::ValueDef::_nil(),
			false, IR__::ValueDefSeq(0), IR__::InterfaceDefSeq(0),
			IR__::InitializerSeq(0) );

	// Create the LooneyToons::Notice value
	// First the sequence of abstract interfaces
	IR__::ValueDefSeq notice_abstract_base_values;
	notice_abstract_base_values.length ( 1 );
	notice_abstract_base_values[0] = event_base;

	IR__::ValueDef_var notice =
		root_module -> create_value (
			"IDL:LooneyToons/Notice:1.0", "Notice", "1.0",
			false, false, IR__::ValueDef::_nil(),
			false, notice_abstract_base_values, IR__::InterfaceDefSeq(0),
			IR__::InitializerSeq(0) );

	// Component Toon
	// First the supported interface sequence
	IR__::InterfaceDefSeq toon_supported_interfaces_seq;
	toon_supported_interfaces_seq.length ( 1 );
	toon_supported_interfaces_seq[0] = movie_interface;

	IR__::ComponentDef_var toon = root_module -> create_component (
		"IDL:LooneyToon/Toon:1.0", "Toon", "1.0",
		IR__::ComponentDef::_nil(), toon_supported_interfaces_seq );

	// Provide tweety
	IR__::ProvidesDef_var toon_tweety =
		toon -> create_provides ( "IDL:LooneyToon/Toon/tweety:1.0", "tweety", "1.0",
		bird_interface );

	// Provide sylvester
	IR__::ProvidesDef_var toon_sylvester =
		toon -> create_provides ( "IDL:LooneyToon/Toon/sylvester:1.0", "sylvester", "1.0",
		cat_interface );

	// Emits call
	IR__::EmitsDef_var toon_call =
		toon -> create_emits ( "IDL:LooneyToon/Toon/call:1.0", "call", "1.0",
		notice );

	// Home ToonTown
	IR__::HomeDef_var home_toon_town = root_module -> create_home (
		"IDL:LooneyToon/ToonTown:1.0", "ToonTown", "1.0",
		IR__::HomeDef::_nil(), toon, toon_supported_interfaces_seq, IR__::ValueDef::_nil() );

	// Create a normal operation on the home
	IR__::OperationDef_var home_setup_operation = home_toon_town -> create_operation (
		"IDL:LooneyToons/ToonTown/setup:1.0",
		"setup", "1.0", repository->get_primitive(IR__::pk_boolean),
		IR__::OP_NORMAL, IR__::ParDescriptionSeq(0),
		IR__::ExceptionDefSeq(0),
		IR__::ContextIdSeq(0) );

	// Create a factory operation on the home
	IR__::ParDescriptionSeq home_factory_parameters;
	home_factory_parameters.length ( 2 );
	home_factory_parameters[0].name = CORBA::string_dup ( "key_string" );
	home_factory_parameters[0].type = repository->get_primitive(IR__::pk_string)->type();
	home_factory_parameters[0].type_def = repository->get_primitive(IR__::pk_string);
	home_factory_parameters[0].mode = IR__::PARAM_IN;
	home_factory_parameters[1].name = CORBA::string_dup ( "instance_number" );
	home_factory_parameters[1].type = repository->get_primitive(IR__::pk_ulong)->type();
	home_factory_parameters[1].type_def = repository->get_primitive(IR__::pk_ulong);
	home_factory_parameters[1].mode = IR__::PARAM_IN;

	IR__::FactoryDef_var home_factory_operation = home_toon_town -> create_factory (
		"IDL:LooneyToons/ToonTown/create_single_toon:1.0",
		"create_single_toon", "1.0",
		home_factory_parameters,
		IR__::ExceptionDefSeq(0) );

	// Create a finder operation on the home
	IR__::ParDescriptionSeq home_finder_parameters;
	home_finder_parameters.length ( 1 );
	home_finder_parameters[0].name = CORBA::string_dup ( "key" );
	home_finder_parameters[0].type = repository->get_primitive(IR__::pk_string)->type();
	home_finder_parameters[0].type_def = repository->get_primitive(IR__::pk_string);
	home_finder_parameters[0].mode = IR__::PARAM_IN;

	IR__::FinderDef_var home_finder_operation = home_toon_town -> create_finder (
		"IDL:LooneyToons/ToonTown/find_my_toon:1.0",
		"find_my_toon", "1.0",
		home_finder_parameters,
		IR__::ExceptionDefSeq(0) );

	// Component Story
	// first the supported interfaces
	IR__::InterfaceDefSeq story_supported_interfaces;
	story_supported_interfaces.length ( 1 );
	story_supported_interfaces[0] = status_interface;

	IR__::ComponentDef_var story = root_module -> create_component (
		"IDL:LooneyToon/Story:1.0", "Story", "1.0",
		IR__::ComponentDef::_nil(), story_supported_interfaces );

	// Uses the_bird
	IR__::UsesDef_var story_the_Bird =
		story -> create_uses ( "IDL:LooneyToon/Story/the_Bird:1.0", "the_Bird", "1.0",
		bird_interface, false );

	// Uses sylvester
	IR__::UsesDef_var story_the_Cat =
		story -> create_uses ( "IDL:LooneyToon/Story/the_Cat:1.0", "the_Cat", "1.0",
		cat_interface, false );

	// Consumes call
	IR__::ConsumesDef_var story_call =
		story -> create_consumes ( "IDL:LooneyToon/Story/call:1.0", "call", "1.0",
		notice );

	// Home StoryHome
	IR__::HomeDef_var home_story = root_module -> create_home (
		"IDL:LooneyToon/StoryHome:1.0", "StoryHome", "1.0",
		IR__::HomeDef::_nil(), story, story_supported_interfaces ,IR__::ValueDef::_nil() );

	// CIDL constructs for our example

	// Composition ToonImpl
	CIDL::CompositionDef_var composition_toon =
		repository -> create_composition (
		"IDL:Studio/ToonImpl:1.0", "ToonImpl", "1.0",
		CIDL::lc_Session, home_toon_town );

	// The Home Executor ToonTownImpl
	CIDL::HomeExecutorDef_var home_executor_toon_town =
		composition_toon -> create_home_executor (
		"IDL:Studio/ToonImpl/ToonTownImpl:1.0", "ToonTownImpl", "1.0" );

	// The Executor ToonSessionImpl
	CIDL::ExecutorDef_var executor_toon_session =
		composition_toon -> create_executor (
		"IDL:Studio/ToonImpl/ToonSessionImpl:1.0", "ToonSessionImpl", "1.0" );

	// The sequence of provided facets for the segments
	IR__::ProvidesDefSeq provided_facets;

	// The first segment of ToonSessionImpl
	provided_facets.length ( 1 );
	provided_facets[0] = toon_tweety;
	CIDL::SegmentDef_var seg1 =
		executor_toon_session -> create_segment (
		"IDL:Studio/ToonImpl/ToonSessionImpl/Seg1:1.0", "Seg1", "1.0",
		provided_facets );

	// The second segment of ToonSessionImpl
	provided_facets.length ( 1 );
	provided_facets[0] = toon_sylvester;
	CIDL::SegmentDef_var seg2 =
		executor_toon_session -> create_segment (
		"IDL:Studio/ToonImpl/ToonSessionImpl/Seg2:1.0", "Seg2", "1.0",
		provided_facets );

	// Composition StoryImpl
	CIDL::CompositionDef_var composition_story =
		repository -> create_composition (
		"IDL:Studio/StoryImpl:1.0", "StoryImpl", "1.0",
		CIDL::lc_Session, home_story );

	// The Home Executor StoryHomeImpl
	CIDL::HomeExecutorDef_var home_executor_story =
		composition_story -> create_home_executor (
		"IDL:Studio/StoryImpl/StoryHomeImpl:1.0", "StoryHomeImpl", "1.0" );

	// The Executor ToonSessionImpl
	CIDL::ExecutorDef_var executor_story =
		composition_story -> create_executor (
		"IDL:Studio/StoryImpl/StorySessionImpl:1.0", "StorySessionImpl", "1.0" );
}

