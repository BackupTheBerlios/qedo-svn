/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import CCMModel.ArrayDef;
import CCMModel.ConstantDef;
import CCMModel.EventDef;
import CCMModel.FixedDef;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.Typed;
import CCMModel.WstringDef;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

public class CreateConstantDefCommand extends CreateModelCommand {
	private String constValue;

	private IDLTemplate idlTemp;
	
	/**
	 * @param type
	 */
	public CreateConstantDefCommand() {
		super(EventDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createConstantDef());
		super.execute();
		((ConstantDef)newObject).setConstValue(constValue);
		setIDLTyped((ConstantDef) newObject, idlTemp);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	
	public void setConstValue(String constValue) {
		this.constValue = constValue;
	}

	public void setIdlTemplate(IDLTemplate idlTemp) {
		this.idlTemp = idlTemp;
	}
	
	protected void setIDLTyped(Typed typed,IDLTemplate idlTemplate){
	    switch(idlTemplate.getIdlKind().getValue()){
	    case IDLKind.IDL:
	        typed.setIDLType((IDLType)idlTypes.get(idlTemplate.getIndexOfIDLType()));
	    	break;
	    case IDLKind.WSTRING:
	        WstringDef wstring=factory.createWstringDef();
	    	wstring.setBound(idlTemplate.getBound());
	    	getRootModule().getCCM().getIdlContainer().getWstrings().add(wstring);
	    	typed.setIDLType(wstring);
	    	break;
	    case IDLKind.ARRAY:
	        ArrayDef arr=factory.createArrayDef();
    		arr.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getArrays().add(arr);
    		typed.setIDLType(arr);
    		break;
	    case IDLKind.STRING:
	        StringDef string=factory.createStringDef();
    		string.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getStrings().add(string);
    		typed.setIDLType(string);
    		break;
	    case IDLKind.FIXED:
	        FixedDef fixed=factory.createFixedDef();
    		fixed.setDigits((new Integer(idlTemplate.getDigits())).shortValue());
    		fixed.setScale((new Integer(idlTemplate.getScale())).shortValue());
    		getRootModule().getCCM().getIdlContainer().getFixeds().add(fixed);
    		typed.setIDLType(fixed);
    		break;
	    case IDLKind.SEQUENCE:
	        SequenceDef seq=factory.createSequenceDef();
    		seq.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getSequences().add(seq);
    		typed.setIDLType(seq);
	    }
	}
}
