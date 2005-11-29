/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 * 
 */

package ccm.editors;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.gef.palette.MarqueeToolEntry;
import org.eclipse.gef.palette.PaletteDrawer;
import org.eclipse.gef.palette.PaletteEntry;
import org.eclipse.gef.palette.PaletteGroup;
import org.eclipse.gef.palette.PaletteRoot;
import org.eclipse.gef.palette.PaletteSeparator;
import org.eclipse.gef.palette.SelectionToolEntry;
import org.eclipse.gef.palette.ToolEntry;
import org.eclipse.jface.resource.ImageDescriptor;

import CCMModel.AliasDef;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.Implementation;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.ExternalInstance;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.ProcessCollocation;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;
import ccm.editors.tools.CCMConnectionCreationToolEntry;
import ccm.editors.tools.CCMCreationToolEntry;
import ccm.model.ModelCreationFactory;
import ccm.model.template.RelationTemplate;

public class CCMPaletteRoot extends PaletteRoot {
	
	

    /**
     * Creates a new CCMPaletteRoot instance for the TypedPage.
     */
    public CCMPaletteRoot(){
        // create root
        super();      
        // a group of default control tools
        PaletteGroup controls = new PaletteGroup("Controls");
        // the selection tool
        ToolEntry tools = new SelectionToolEntry();
        controls.add(tools);
        // use selection tool as default entry
        setDefaultEntry(tools);
		// the marquee selection tool
		controls.add(new MarqueeToolEntry());
		
		List entries = new ArrayList();
		entries.add(tools);
			
		PaletteDrawer drawer = new PaletteDrawer("instances");
		
		entries = new ArrayList();
		
		ToolEntry tool =new CCMCreationToolEntry(
				  "Home",
				  "Creates a home",
				  new ModelCreationFactory(HomeDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOME_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOME_M));
		entries.add(tool);

	
		
		tool =new CCMCreationToolEntry(
						  "Component",
						  "Creates a Component",
						  new ModelCreationFactory(ComponentDef.class),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONENT_S),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONENT_S));				  
		entries.add(tool);
		
		tool =new CCMCreationToolEntry(
						  "Interface",
						  "Creates a Interface",
						  new ModelCreationFactory(InterfaceDef.class),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ITF_S),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ITF_M));						  
		entries.add(tool);
				
		
		tool =new CCMCreationToolEntry(
						  "Module",
						  "Creates a module",
						  new ModelCreationFactory(ModuleDef.class),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.MODULE_S),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.MODULE_M));								  
		entries.add(tool);	
		
		tool =new CCMCreationToolEntry(
				  "Event",
				  "Creates an event",
				  new ModelCreationFactory(EventDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,  ProjectResources.EVENT_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.EVENT_S));						  
		entries.add(tool);	
		
		
		tool =new CCMConnectionCreationToolEntry(
				"component_home",
				"Creates a component_home",
				new ModelCreationFactory(RelationTemplate.class,2),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool);
		
		tool =new CCMConnectionCreationToolEntry(
				"supports",
				"Creates a supports",
				new ModelCreationFactory(RelationTemplate.class,13),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool);
		
		tool =new CCMConnectionCreationToolEntry(
				"ports_itf",
				"Creates a ports_itf",
				new ModelCreationFactory(RelationTemplate.class,3),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool);
		
		tool =new CCMConnectionCreationToolEntry(
				"event_type",
				"Creates a event_type",
				new ModelCreationFactory(RelationTemplate.class,4),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool);
		tool =new CCMConnectionCreationToolEntry(
				"home_key",
				"Creates a home_key",
				new ModelCreationFactory(RelationTemplate.class,10),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool);
		tool =new CCMConnectionCreationToolEntry(
				"derived",
				"Creates a derived",
				new ModelCreationFactory(RelationTemplate.class),
				 ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.DERIVED_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.DERIVED_S));	
										
		entries.add(tool);
		
		tool =new CCMConnectionCreationToolEntry(
				"abstractDerived",
				"Creates a abstractDerived",
				new ModelCreationFactory(RelationTemplate.class,1),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		entries.add(tool); 
		
		
		
		drawer.addAll(entries);
		add(controls);
		add(drawer);
		
		
		drawer = new PaletteDrawer("Implementation");
		entries = new ArrayList();
		tool =new CCMCreationToolEntry(
				  "HomeImpl",
				  "Creates a homeImpl",
				  new ModelCreationFactory(HomeImplDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEIMPL_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEIMPL));
		entries.add(tool);

		tool =new CCMCreationToolEntry(
						  "ComponentImpl",
						  "Creates a ComponentImpl",
						  new ModelCreationFactory(ComponentImplDef.class),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONENTIMPL),
						  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONENTIMPL));
						  
		entries.add(tool);	
		tool =new CCMCreationToolEntry(
				  "Composition",
				  "Creates a Composition",
				  new ModelCreationFactory(Composition.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPOSITION_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPOSITION));
				  
       entries.add(tool);	
       tool =new CCMConnectionCreationToolEntry(
		"composite",
		"Creates a composite relation",
		new ModelCreationFactory(RelationTemplate.class,5),
		ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
		ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
								
        entries.add(tool);
        tool =new CCMConnectionCreationToolEntry(
        		"manages",
        		"Creates a manage relation",
        		new ModelCreationFactory(RelationTemplate.class,6),
        		ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
        		ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
        								
                entries.add(tool);
		drawer.addAll(entries);
		add(drawer);
		
		drawer = new PaletteDrawer("Deployment");
		entries = new ArrayList();
		tool =new CCMCreationToolEntry(
				  "SoftwarePackage",
				  "Creates a SoftwarePackage",
				  new ModelCreationFactory(SoftwarePackage.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE));
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "Implementation",
				  "Creates a Implementation",
				  new ModelCreationFactory(Implementation.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE));
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "HomeInstance",
				  "Creates a homeInstance",
				  new ModelCreationFactory(HomeInstantiation.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.HOMEINSTANCE));
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "ComponentInstance",
				  "Creates a ComponentInstance",
				  new ModelCreationFactory(ComponentInstantiation.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONRNTINSTANCE),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.COMPONRNTINSTANCE));
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "ExternalInstance",
				  "Creates a ExternalInstance",
				  new ModelCreationFactory(ExternalInstance.class),
				  null,
				 null);
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "ProcessCollocation",
				  "Creates a ProcessCollocation",
				  new ModelCreationFactory(ProcessCollocation.class),
				  null,
				  null);
		entries.add(tool);
		tool =new CCMConnectionCreationToolEntry(
				"interfaceConnection",
				"Creates a interfacecConnection",
				new ModelCreationFactory(RelationTemplate.class,7),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
										
		        entries.add(tool);
	    tool =new CCMConnectionCreationToolEntry(
		        "eventConnection",
		        "Creates a eventConnection",
		        new ModelCreationFactory(RelationTemplate.class,8),
		        ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
		        ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	
		        entries.add(tool);
		tool =new CCMConnectionCreationToolEntry(
		          "streamConnection",
		          "Creates a streamConnection",
		          new ModelCreationFactory(RelationTemplate.class,9),
		          ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
		          ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	    								
		          entries.add(tool);
	    tool =new CCMConnectionCreationToolEntry(
				  "impl_by",
				   "deployment unit impl_by composition",
				   new ModelCreationFactory(RelationTemplate.class,11),
				   ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S),
				   ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ABSTRACT_DERIVED_S));	    								
				   entries.add(tool);
		
		drawer.addAll(entries);
		add(drawer);
		
		
		
		add(createTypes());
		
		PaletteSeparator sep = new PaletteSeparator("Class"); 
		sep.setUserModificationPermission(PaletteEntry.PERMISSION_NO_MODIFICATION);
		entries.add(sep);
		//drawer.addAll(entries);
		//add(drawer);
    }
	
	private PaletteDrawer createTypes(){
		PaletteDrawer drawer = new PaletteDrawer("corba types");
		List entries = new ArrayList();
		ToolEntry tool =new CCMCreationToolEntry(
				  "Value",
				  "Creates a value",
				  new ModelCreationFactory(ValueDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,  ProjectResources.VALUE_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.VALUE_M));						  
		entries.add(tool);	
		
		
		tool =new CCMCreationToolEntry(
				  "Exception",
				  "create an exception",
				  new ModelCreationFactory(ExceptionDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.EXCEPTION_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.EXCEPTION_M));		
		entries.add(tool);
		
		tool =new CCMCreationToolEntry(
				  "Constant",
				  "create an constant",
				  new ModelCreationFactory(ConstantDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.CONST_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.CONST_M));		
		entries.add(tool);
		
		
		tool =new CCMCreationToolEntry(
				  "Enum",
				  "create an enum",
				  new ModelCreationFactory(EnumDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ENUM_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.ENUM_M));	
		entries.add(tool);
		
		tool =new CCMCreationToolEntry(
				  "ValueBox",
				  "create an value box",
				  new ModelCreationFactory(ValueBoxDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.VALUEBOX_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.VALUEBOX_M));	
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "Alias",
				  "create an alias",
				  new ModelCreationFactory(AliasDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.TYPEDEF_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class, ProjectResources.TYPEDEF_M));	
		entries.add(tool);
		
		tool =new CCMCreationToolEntry(
				  "Struct",
				  "create an struct",
				  new ModelCreationFactory(StructDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.STRUCT_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.STRUCT_M));	
		entries.add(tool);
		tool =new CCMCreationToolEntry(
				  "Union",
				  "create an union",
				  new ModelCreationFactory(UnionDef.class),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.UNION_S),
				  ImageDescriptor.createFromFile(CCMEditorPlugin.class,ProjectResources.UNION_M));	
		entries.add(tool);

		drawer.addAll(entries);
		return drawer;
	}
	
}
