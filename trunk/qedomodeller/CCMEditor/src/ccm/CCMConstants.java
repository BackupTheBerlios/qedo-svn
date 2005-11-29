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
package ccm;

import java.util.List;

import org.eclipse.emf.common.util.EList;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CCombo;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.widgets.Combo;

import CCMModel.AbstractDerivedRelation;
import CCMModel.AbstractItfDerivedRelation;
import CCMModel.AliasDef;
import CCMModel.ArrayDef;
import CCMModel.CCMModelFactory;
import CCMModel.CompHomeRelation;
import CCMModel.ComponentDef;
import CCMModel.EnumDef;
import CCMModel.EventPortEventRelation;
import CCMModel.FixedDef;
import CCMModel.HomeDef;
import CCMModel.IDLType;
import CCMModel.IDLTypeContainer;
import CCMModel.InterfaceDef;
import CCMModel.InterfaceRelation;
//import CCMModel.IpmlementsRelation;
import CCMModel.ManagersRelation;
import CCMModel.ModuleDef;
import CCMModel.PrimitiveDef;
import CCMModel.Relation;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.StructDef;
import CCMModel.SupportsRelation;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueDerivedRelation;
import CCMModel.WstringDef;
import ccm.model.CCMModelManager;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
 * @author eduardw
 *
*defiened constants for this project
 */
public class CCMConstants {

	/**
	 *<code>classColor</code> Color for the figuresbackground
	 */
	public static final String 	SUPPORT_LABEL="<< supports >>";
	public static final String 	DERIVED_LABEL="<< derived from >>";
	public static final String 	COMPONENT_HOME_LABEL="<< component home >>";
	public static final String 	COMPOSITION_HOME_LABEL="<<composite>>";
	public static final String 	EVENTPORT_EVENT_LABEL="<< event_type >>";
	public static final String 	HOME_KEY_LABEL= "<<home_key>>";
	public static final String 	ABSTRACT_DERIVED_LABEL="<< abstract derived from >>";
	public static final String 	IMPL_LABEL="<<implements>>";
	public static final String 	MANAGES_LABEL="<<manages>>";
	public static final String 	PROVIDES_INTERFACE_LABEL="<< provides interface >>";
	public static final String 	USES_INTERFACE_LABEL="<< uses interface >>";
	//public static final String 	IMPL_LABEL="<<implements>>";
	
	
	
	
	
	
	public static Color classColor = new Color(null,255,255,206);
	
	/**
	 * <code>font</code> one font for figures
	 */
	public static Font font = new Font(null, "Arial", 8, SWT.BOLD);
	public static Font font1 = new Font(null, "Arial", 7, 0);
	
	/**
	 * <code>classFont</code> another font for figures
	 */
	public static Font classFont = new Font(null, "Arial", 12, SWT.BOLD);
	private static CCMModelFactory factory =CCMModelManager.getFactory();
	
	
	/**
	 * create full repository identifier of this instance
	 * @param absName absolute name of instance
	 * @param identifier identifier of instance
	 * @param version version of instance
	 * @return full repository identifier of this instance
	 */
	public static final String getRepositoryIdString(String absName,String identifier,String version){
	    return "IDL:"+absName+":"+identifier+":"+version;
	}
	
	
	/**
	 * adds to the idlTypeCmb new item and select this,if idlTemp kind is WSTRING, ARRAY,SEQUENCE, STRING or FIXED
	 * else select item in the idlTypeCmb that identicate with idlTemp
	 * @see ccm.model.template.IDLKind
	 * @see ccm.model.template.IDLTemplate
	 * @param idlTemp ccm.model.template.IDLTemplate
	 * @param idlTypeCmb Combo
	 */
	public static final void  setIDL(IDLTemplate idlTemp,Combo idlTypeCmb){
	    switch(idlTemp.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	        idlTypeCmb.add("wstring["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
	    	break;
	    case IDLKind.ARRAY:
	        idlTypeCmb.add("array["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.SEQUENCE:
	        idlTypeCmb.add("sequence["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.STRING:
	        idlTypeCmb.add("string["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.FIXED:
	        idlTypeCmb.add("fixed(digits="+idlTemp.getDigits()+", scale="+idlTemp.getScale()+")");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
    	case IDLKind.IDL:
    	    idlTypeCmb.select(idlTemp.getIndexOfIDLType());
	    }   
	}
	
	/**
	 * create the name of the idlType for the GUI 
	 * @see ccm.model.template.IDLKind
	 * @see ccm.model.template.IDLTemplate
	 * @param idlTemp ccm.model.template.IDLTemplate
	 * @param idlTypesName list of all idlType that define in the project
	 * @return name as String of the idlType
	 */
	public static final String  getIDLName(IDLTemplate idlTemp,List idlTypesName){
	    switch(idlTemp.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	        return "wstring["+idlTemp.getBound()+"]";
	    case IDLKind.ARRAY:
	        return "array["+idlTemp.getBound()+"]";
	    case IDLKind.SEQUENCE:
	        return "sequence["+idlTemp.getBound()+"]";
	    case IDLKind.STRING:
	        return "string["+idlTemp.getBound()+"]";
	    case IDLKind.FIXED:
	        return "fixed(digits="+idlTemp.getDigits()+", scale="+idlTemp.getScale()+")";
    	case IDLKind.IDL:
    	    return (String) idlTypesName.get(idlTemp.getIndexOfIDLType());
    	default:
    	    return "";
	    }   
	}
	
	/**
	 * adds to the idlTypeCmb new item and select this,if idlTemp kind is WSTRING, ARRAY,SEQUENCE, STRING or FIXED
	 * else select item in the idlTypeCmb that identicate with idlTemp
	 * @see ccm.model.template.IDLKind
	 * @see ccm.model.template.IDLTemplate
	 * @param idlTemp ccm.model.template.IDLTemplate
	 * @param idlTypeCmb CCombo
	 */
	public static final void  setIDL(IDLTemplate idlTemp,CCombo idlTypeCmb){
	    switch(idlTemp.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	        idlTypeCmb.add("wstring["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
	    	break;
	    case IDLKind.ARRAY:
	        idlTypeCmb.add("array["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.SEQUENCE:
	        idlTypeCmb.add("sequence["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.STRING:
	        idlTypeCmb.add("string["+idlTemp.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.FIXED:
	        idlTypeCmb.add("fixed(digits="+idlTemp.getDigits()+", scale="+idlTemp.getScale()+")");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
    	case IDLKind.IDL:
    	    idlTypeCmb.select(idlTemp.getIndexOfIDLType());
	    }   
	}
	
	
	/** 
	 * create the ccm.model.template.IDLTemplate that reflect the type
	 * @param type IDLType
	 * @param idlTypes  list of all idlType that define in the project
	 * @return ccm.model.template.IDLTemplate
	 */
	public static IDLTemplate  getIDLTemplate(IDLType  type,List idlTypes){
	    IDLTemplate idlTemp=new IDLTemplate();
	    if(type instanceof PrimitiveDef ||
	       type instanceof InterfaceDef ||
	       type instanceof ComponentDef ||
	       type instanceof HomeDef ||
	       type instanceof UnionDef ||
	       type instanceof StructDef ||
	       type instanceof EnumDef ||
	       type instanceof AliasDef ||
	       type instanceof ValueBoxDef ||
	       type instanceof ValueDef){
	        idlTemp.setIdlKind(IDLKind.IDL_LITERAL);
	        idlTemp.setIndexOfIDLType(idlTypes.indexOf(type));        
	    }else if(type instanceof StringDef){
	        idlTemp.setIdlKind(IDLKind.STRING_LITERAL);
	        idlTemp.setBound((new Long(((StringDef)type).getBound())).intValue());
	    }else if(type instanceof WstringDef){
	        idlTemp.setIdlKind(IDLKind.WSTRING_LITERAL);
	        idlTemp.setBound((new Long(((WstringDef)type).getBound())).intValue());
	    }else if(type instanceof FixedDef){
	        idlTemp.setIdlKind(IDLKind.FIXED_LITERAL);
	        idlTemp.setScale((new Long(((FixedDef)type).getScale())).intValue());
	        idlTemp.setDigits((new Long(((FixedDef)type).getDigits())).intValue());
	    }else if(type instanceof ArrayDef){
	        idlTemp.setIdlKind(IDLKind.ARRAY_LITERAL);
	        idlTemp.setBound((new Long(((ArrayDef)type).getBound())).intValue());
	    }else if(type instanceof SequenceDef){
	        idlTemp.setIdlKind(IDLKind.SEQUENCE_LITERAL);
	        idlTemp.setBound((new Long(((SequenceDef)type).getBound())).intValue());
	    }
	    return idlTemp;
	}
	

	
	public static String getRelationDescription(Relation rel) {
		
		if (rel instanceof CompHomeRelation) return "<< component home >>";
		if (rel instanceof SupportsRelation) return "<< supports >>";
		if (rel instanceof EventPortEventRelation) return "<< event_typeAss >>";
		if (rel instanceof ManagersRelation) return "<< manages >>";
		if (rel instanceof AbstractItfDerivedRelation) return "<< derived from >>";
	//	if (rel instanceof IpmlementsRelation) return "<< implements >>";
		if (rel instanceof ValueDerivedRelation) return "<< derived from >>";
		if (rel instanceof AbstractDerivedRelation) return "<< abstract derived from >>";
		if (rel instanceof InterfaceRelation) {
			if (((InterfaceRelation) rel).getProvidesDef()!=null) 
			return "<< provides interface >>";
			else return "<< uses interface >>";
		}

		return null;
	}
	public static void setIDLTyped(Typed typed,IDLTemplate idlTemplate,ModuleDef root,List idlT){
	    switch(idlTemplate.getIdlKind().getValue()){
	    case IDLKind.IDL:
	        typed.setIDLType((IDLType)idlT.get(idlTemplate.getIndexOfIDLType()));
	    	break;
	    case IDLKind.WSTRING:
	        WstringDef wstring=factory.createWstringDef();
	    	wstring.setBound(idlTemplate.getBound());
	    	IDLTypeContainer container=root.getCCM().getIdlContainer();
	    	EList list =container.getWstrings();
	    	list.add(wstring);
	    	typed.setIDLType(wstring);
	    	break;
	    case IDLKind.ARRAY:
	        ArrayDef arr=factory.createArrayDef();
    		arr.setBound(idlTemplate.getBound());
    		root.getCCM().getIdlContainer().getArrays().add(arr);
    		typed.setIDLType(arr);
    		break;
	    case IDLKind.STRING:
	        StringDef string=factory.createStringDef();
    		string.setBound(idlTemplate.getBound());
    		root.getCCM().getIdlContainer().getStrings().add(string);
    		typed.setIDLType(string);
    		break;
	    case IDLKind.FIXED:
	        FixedDef fixed=factory.createFixedDef();
    		fixed.setDigits((new Integer(idlTemplate.getDigits())).shortValue());
    		fixed.setScale((new Integer(idlTemplate.getScale())).shortValue());
    		root.getCCM().getIdlContainer().getFixeds().add(fixed);
    		typed.setIDLType(fixed);
    		break;
	    case IDLKind.SEQUENCE:
	        SequenceDef seq=factory.createSequenceDef();
    		seq.setBound(idlTemplate.getBound());
    		root.getCCM().getIdlContainer().getSequences().add(seq);
    		typed.setIDLType(seq);
	    }
	} 
}


