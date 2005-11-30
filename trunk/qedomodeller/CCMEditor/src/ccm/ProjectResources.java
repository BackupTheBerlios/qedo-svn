/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 */
package ccm;

import org.eclipse.swt.graphics.Image;

import CCMModel.AbstractItfDerivedRelation;
import CCMModel.AttributeDef;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.EmitsDef;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.FactoryDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.PortLocation;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.Relation;
import CCMModel.StructDef;
import CCMModel.Typed;
import CCMModel.TypedefDef;
import CCMModel.UnionDef;
import CCMModel.UsesDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueMemberDef;


/**
 * @author eduardw
 *
 *constant refrences to the images
 */
public class ProjectResources {
    
	 public static final String HOMEIMPL="icons/homeImpl_m.gif";
	 public static final String HOMEIMPL_S="icons/homeImpl_s.gif";
	 //public static final String HOMEIMPL_S="icons/component.gif";
	 public static final String HOMEINSTANCE="icons/homeInstance_m.gif";
	 public static final String HOMEINSTANCE_S="icons/homeInstance_s.gif";
	 //public static final String HOMEINSTANCE_S="icons/component.gif";
	 public static final String COMPONENTIMPL="icons/componentImpl.gif";
	 public static final String COMPONRNTINSTANCE="icons/componentInstance.gif";
	 public static final String COMPOSITION="icons/composition_m.gif";
	 public static final String COMPOSITION_S="icons/composition_s.gif";
	 
    public static final String HOME_S="icons/home_s.gif";
	 //public static final String HOME_S="icons/component.gif";
    public static final String HOME_M= "icons/home_m.bmp";
    public static final String COMPONENT_S= "icons/component.gif";			  
    public static final String ITF_S= "icons/itf_s.bmp";
    public static final String ITF_M="icons/itf_m.bmp";						  

    public static final String MODULE_S= "icons/module_s.gif";
    public static final String MODULE_M="icons/module_m.bmp";								  
    public static final String VALUE_S="icons/value_s.bmp";
    public static final String VALUE_M="icons/value_m.bmp";						  
    public static final String EXCEPTION_S="icons/exception_s.bmp";
    public static final String EXCEPTION_M="icons/exception_m.bmp";		
    public static final String CONST_S="icons/const_s.bmp";
    public static final String CONST_M="icons/const_m.bmp";		
    public static final String ENUM_S="icons/enum_s.bmp";
    public static final String ENUM_M="icons/enum_m.bmp";	
    public static final String VALUEBOX_S="icons/valuebox_s.bmp";
    public static final String VALUEBOX_M="icons/valuebox_m.bmp";	
    public static final String TYPEDEF_S= "icons/typedef_s.bmp";
    public static final String TYPEDEF_M="icons/typedef_m.bmp";	
    public static final String STRUCT_S="icons/struct_s.bmp";
    public static final String STRUCT_M="icons/struct_m.bmp";	
    public static final String UNION_S= "icons/union_s.bmp";
    public static final String UNION_M="icons/union_m.bmp";	
    public static final String OPERATION_S="icons/op_s.bmp";	
    public static final String MEMBER_S="icons/member_s.bmp";
    public static final String ATTRIBUE_S="icons/attribute_s.bmp";
    public static final String PRIMITIVE_S="icons/primitive_s.bmp";
    public static final String DERIVED_S="icons/derived_s.bmp";
    public static final String ABSTRACT_DERIVED_S="icons/abstractderived_s.bmp";
    public static final String FINDER_S="icons/finder_s.bmp";
    public static final String FACTORY_S="icons/factory_s.bmp";
    public static final String EVENT_S="icons/event_s.gif";
    
    
    public static final String FACET_ALL = "icons/facet.gif"; 

    public static final String RECEPTACLE_TOP = "icons/receptacle_top.gif"; 
    public static final String RECEPTACLE_BOTTOM = "icons/receptacle_bottom.gif"; 
    public static final String RECEPTACLE_RIGHT = "icons/receptacle_right.gif"; 
    public static final String RECEPTACLE_LEFT = "icons/receptacle_left.gif"; 

    public static final String RECEPTACLE_TOP1 = "icons/receptacle_top1.gif"; 
    public static final String RECEPTACLE_BOTTOM1 = "icons/receptacle_bottom1.gif"; 
    public static final String RECEPTACLE_RIGHT1 = "icons/receptacle_right1.gif"; 
    public static final String RECEPTACLE_LEFT1 = "icons/receptacle_left1.gif"; 
    
    public static final String EVENTSOURCE_TOP = "icons/eventsource_top.gif"; 
    public static final String EVENTSOURCE_BOTTOM = "icons/eventsource_bottom.gif"; 
    public static final String EVENTSOURCE_RIGHT = "icons/eventsource_right.gif"; 
    public static final String EVENTSOURCE_LEFT = "icons/eventsource_left.gif"; 

    public static final String EMITTERSOURCE_TOP = "icons/emittersource_top.gif"; 
    public static final String EMITTERSOURCE_BOTTOM = "icons/emittersource_bottom.gif"; 
    public static final String EMITTERSOURCE_RIGHT = "icons/emittersource_right.gif"; 
    public static final String EMITTERSOURCE_LEFT = "icons/emittersource_left.gif"; 

    public static final String EVENTSINK_TOP = "icons/eventsink_top.gif"; 
    public static final String EVENTSINK_BOTTOM = "icons/eventsink_bottom.gif"; 
    public static final String EVENTSINK_RIGHT = "icons/eventsink_right.gif"; 
    public static final String EVENTSINK_LEFT = "icons/eventsink_left.gif"; 

    
    
    public static final String OUTLINE = "icons/outline.gif";
    public static final String OVERVIEW = "icons/overview.gif";

    
    
	public static String getPortIconPath(Contained obj, int location){

		if(obj instanceof ProvidesDef) {
			return FACET_ALL;
		}
		else if(obj instanceof UsesDef) {
			switch (location) {
				case PortLocation.TOP : 	return RECEPTACLE_TOP;
				case PortLocation.RIGHT : 	return RECEPTACLE_RIGHT;
				case PortLocation.BOTTOM :	return RECEPTACLE_BOTTOM;
				case PortLocation.LEFT : 	return RECEPTACLE_LEFT;
			}
		}
		else if (obj instanceof PublishesDef) {
			switch (location) {
				case PortLocation.TOP : 	return EVENTSOURCE_TOP;
				case PortLocation.RIGHT : 	return EVENTSOURCE_RIGHT;
				case PortLocation.BOTTOM :	return EVENTSOURCE_BOTTOM;
				case PortLocation.LEFT : 	return EVENTSOURCE_LEFT;
			}	
		}
		else if(obj instanceof EmitsDef) {
			switch (location) {
				case PortLocation.TOP : 	return EMITTERSOURCE_TOP;
				case PortLocation.RIGHT : 	return EMITTERSOURCE_RIGHT;
				case PortLocation.BOTTOM :	return EMITTERSOURCE_BOTTOM;
				case PortLocation.LEFT : 	return EMITTERSOURCE_LEFT;
			}	
		}
		else if(obj instanceof ConsumesDef) {
			switch (location) {
				case PortLocation.TOP : 	return EVENTSINK_TOP;
				case PortLocation.RIGHT : 	return EVENTSINK_RIGHT;
				case PortLocation.BOTTOM :	return EVENTSINK_BOTTOM;
				case PortLocation.LEFT : 	return EVENTSINK_LEFT;
			}
		}

		return null;
	}
	
	
	
	
	public static Image getIcon(Object o) {

		String res = null;
		
		if (o instanceof ModuleDef) res = MODULE_S;
		else if (o instanceof AttributeDef) res = ATTRIBUE_S;
		else if (o instanceof ConstantDef) res = CONST_S;
		else if (o instanceof AbstractItfDerivedRelation) res = ABSTRACT_DERIVED_S;
		else if (o instanceof ComponentDef) res = COMPONENT_S;
		else if (o instanceof ConsumesDef) res = EVENTSINK_RIGHT;
		else if (o instanceof Diagram) res = OUTLINE;
		else if (o instanceof EmitsDef) res = EMITTERSOURCE_RIGHT;
		else if (o instanceof EnumDef) res = ENUM_S;
		else if (o instanceof EventDef) res = EVENT_S;
		else if (o instanceof ExceptionDef) res = EXCEPTION_S;
		else if (o instanceof FactoryDef) res = FACTORY_S;
		else if (o instanceof HomeDef) res = HOME_S;
		//****************************************************
		else if (o instanceof HomeImplDef) res = HOMEIMPL_S;
		else if (o instanceof HomeInstantiation) res = HOMEINSTANCE;
		else if (o instanceof ComponentImplDef) res = COMPONENTIMPL;
		else if (o instanceof ComponentInstantiation) res = COMPONRNTINSTANCE;
		else if (o instanceof Composition) res = COMPOSITION_S;
		//****************************************************
		else if (o instanceof InterfaceDef) res = ITF_S;	     
		else if (o instanceof ProvidesDef) res = FACET_ALL;
		else if (o instanceof PublishesDef) res = EVENTSOURCE_RIGHT;
		else if (o instanceof Relation) res = DERIVED_S;
		else if (o instanceof OperationDef) res = OPERATION_S;
		else if (o instanceof StructDef) res = STRUCT_S;
		else if (o instanceof UnionDef) res = UNION_S;
		else if (o instanceof UsesDef){
			if(((UsesDef)o).isMultipleItf())
			  res = RECEPTACLE_RIGHT;
			else
				res = RECEPTACLE_RIGHT1;
		}
		else if (o instanceof ValueBoxDef) res = VALUEBOX_S;
		else if (o instanceof ValueDef) res = VALUE_S;
		else if (o instanceof ValueMemberDef) res = VALUE_S;
		else if (o instanceof Typed) res = MEMBER_S;
		else if (o instanceof TypedefDef) res = TYPEDEF_S;
		
		else return null;
		
		return new Image(null, CCMEditorPlugin.class.getResourceAsStream(res));

	}
}


