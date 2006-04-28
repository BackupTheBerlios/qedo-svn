/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import java.util.Iterator;
import java.util.List;

import CCMModel.ArrayDef;
import CCMModel.FixedDef;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.WstringDef;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.UnionFieldTemplate;

public class CreateUnionDefCommand extends CreateModelCommand {
	private List memberList;
	private IDLTemplate discrType=new IDLTemplate(IDLKind.IDL_LITERAL);
	private UnionDef unionD;

	/**
	 * @param type
	 */
	public CreateUnionDefCommand() {
		super(UnionDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		unionD = factory.createUnionDef();
		setNewObject(unionD);
		
		super.execute();
		
		setIDL();
		addMembers();
	}
	
	private void addMembers(){
	    unionD.getUnionMembers().clear();
	    Iterator it=memberList.iterator();
	    while(it.hasNext()){
	        UnionFieldTemplate p=(UnionFieldTemplate) it.next();
	        UnionField fld=factory.createUnionField();
	        fld.setIdentifier(p.getIdentifier());
	        this.setIDLTyped(fld,p.getIdlType());
	        fld.setLabel(p.getLabel());
			unionD.getUnionMembers().add(fld);
	    }
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}

	public void setUnionMembers(List memberList) {
		this.memberList = memberList;
	}

	public void setDiscrType(IDLTemplate idlTemp) {
		this.discrType = idlTemp;
	}
	
	private void setIDL(){
	    switch(discrType.getIdlKind().getValue()){
	    case IDLKind.IDL:
	        unionD.setDiscriminatorType((IDLType)idlTypes.get(discrType.getIndexOfIDLType()));
	    	break;
	    case IDLKind.WSTRING:
	        WstringDef wstring=factory.createWstringDef();
	    	wstring.setBound(discrType.getBound());
	    	getRootModule().getCCM().getIdlContainer().getWstrings().add(wstring);
	    	unionD.setDiscriminatorType(wstring);
	    	break;
	    case IDLKind.ARRAY:
	        ArrayDef arr=factory.createArrayDef();
    		arr.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getArrays().add(arr);
    		unionD.setDiscriminatorType(arr);
    		break;
	    case IDLKind.STRING:
	        StringDef string=factory.createStringDef();
    		string.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getStrings().add(string);
    		unionD.setDiscriminatorType(string);
    		break;
	    case IDLKind.FIXED:
	        FixedDef fixed=factory.createFixedDef();
    		fixed.setDigits((new Integer(discrType.getDigits())).shortValue());
    		fixed.setScale((new Integer(discrType.getScale())).shortValue());
    		getRootModule().getCCM().getIdlContainer().getFixeds().add(fixed);
    		unionD.setDiscriminatorType(fixed);
    		break;
	    case IDLKind.SEQUENCE:
	        SequenceDef seq=factory.createSequenceDef();
    		seq.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getSequences().add(seq);
    		unionD.setDiscriminatorType(seq);
	    }
	}
}
