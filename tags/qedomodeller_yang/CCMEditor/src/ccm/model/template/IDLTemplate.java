/*
 * Created on 12.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model.template;

import CCMModel.ArrayDef;
import CCMModel.FixedDef;
import CCMModel.IDLType;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.WstringDef;





/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class IDLTemplate {
    
   private IDLKind idlKind=IDLKind.IDL_LITERAL;
   private int bound=0;
   private int digits=0;
   private int scale=0;
   private int indexOfIDLType=0;
   
   //******************************************
   public static IDLTemplate getTemlateFromIDLType(IDLType type){
    IDLTemplate template= null;
    if (type instanceof WstringDef){
    	 System.out.println("种种种种种种謙ype-wstringdef: "+ type); 
    	WstringDef sd = (WstringDef)type;
    	//sd.getBound()
    	template = new IDLTemplate(IDLKind.WSTRING_LITERAL);
    	template.setBound((int)sd.getBound());
    	 
    }
    if (type instanceof StringDef){
    	 
    	StringDef sd = (StringDef)type;
    	//sd.getBound()
    	template = new IDLTemplate(IDLKind.STRING_LITERAL);
    	template.setBound((int)sd.getBound());
    	 
    }
    if (type instanceof ArrayDef){
    	 
    	ArrayDef sd = (ArrayDef)type;
    	//sd.getBound()
    	template = new IDLTemplate(IDLKind.ARRAY_LITERAL);
    	template.setBound((int)sd.getBound());
    	 
    }
    if (type instanceof SequenceDef){
     
    	SequenceDef sd = (SequenceDef)type;
    	//sd.getBound()
    	template = new IDLTemplate(IDLKind.SEQUENCE_LITERAL);
    	template.setBound((int)sd.getBound());
    	 
    }
    if (type instanceof FixedDef){
    	 
    	FixedDef sd = (FixedDef)type;
    	//sd.getBound()
    	template = new IDLTemplate(IDLKind.FIXED_LITERAL);
    	template.setDigits(sd.getDigits());
    	template.setScale(sd.getScale());
    	 
    }
    if (type instanceof PrimitiveDef){
    	PrimitiveDef pd = (PrimitiveDef)type; 
    	PrimitiveKind pk = pd.getKind();
    	//pk.getValue();
    	template = new IDLTemplate(IDLKind.IDL_LITERAL);
    	template.setIndexOfIDLType(pk.getValue());  	
    	
    }
   	return template;
   	
   }
   //******************************************
   
   public IDLTemplate(IDLKind kind){
       this.idlKind=kind;
   }
   
   public IDLTemplate(){}
	/**
	 * @return Returns the bound.
	 */
	public int getBound() {
	    return bound;
	}
	/**
	 * @param bound The bound to set.
	 */
	public void setBound(int bound) {
	    this.bound = bound;
	}
	/**
	 * @return Returns the digits.
	 */
	public int getDigits() {
	    return digits;
	}
	/**
	 * @param digits The digits to set.
	 */
	public void setDigits(int digits) {
	    this.digits = digits;
	}
	/**
	 * @return Returns the idlKind.
	 */
	public IDLKind getIdlKind() {
	    return idlKind;
	}
	/**
	 * @param idlKind The idlKind to set.
	 */
	public void setIdlKind(IDLKind idlKind) {
	    this.idlKind = idlKind;
	}
	/**
	 * @return Returns the indexOfIDLType.
	 */
	public int getIndexOfIDLType() {
	    return indexOfIDLType;
	}
	/**
	 * @param indexOfIDLType The indexOfIDLType to set.
	 */
	public void setIndexOfIDLType(int indexOfIDLType) {
	    this.indexOfIDLType = indexOfIDLType;
	}
	/**
	 * @return Returns the scale.
	 */
	public int getScale() {
	    return scale;
	}
	/**
	 * @param scale The scale to set.
	 */
	public void setScale(int scale) {
	    this.scale = scale;
	}
}
