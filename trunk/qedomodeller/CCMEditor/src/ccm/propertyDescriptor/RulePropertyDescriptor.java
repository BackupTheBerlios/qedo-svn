/*
 * Created on 29.09.2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.propertyDescriptor;

import java.util.List;

import org.eclipse.emf.common.ui.celleditor.ExtendedDialogCellEditor;
import org.eclipse.jface.viewers.CellEditor;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import ccm.dialogs.EditRuleDialog;

/**
 * @author Siegercn
 *
 */
public class RulePropertyDescriptor  extends PropertyDescriptor{	
	//private OperationDef abstObj;
	private List packages =null;
	private List rules=null;
	//private ModelFactory mf;
	public RulePropertyDescriptor(Object id, String displayName,List rules )
	{
		super(id,displayName);
	 
		this.rules=rules;
	}
	public CellEditor createPropertyEditor(Composite parent){
	 
	 
	CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

	 {
		 protected Object openDialogBox(Control cellEditorWindow)
        {
		 	 
		 	//EditIDLTypeDialog dialog = new EditIDLTypeDialog(
		 	EditRuleDialog dialog = new EditRuleDialog(
		 	cellEditorWindow.getShell(),0);
		 	dialog.setPackages(packages);
		  //  IDLTemplate template=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT); 
		  //  dialog.setIdlTemp(template);
		    dialog.setPameterList(rules);
            dialog.open();
          if (!dialog.isState())
          	return null;
         
          return dialog.getPameterList();
        }
	};
	return result;
	
	
}

}
 
