/*
 * Created on 29.09.2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.propertyDescriptor;

import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.ui.celleditor.ExtendedDialogCellEditor;
import org.eclipse.jface.viewers.CellEditor;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import ccm.dialogs.EditParameterDialog;

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ParameterPropertyDescriptor  extends PropertyDescriptor{	
	//private OperationDef abstObj;
	private List idlTypeNames=new LinkedList();
	private List paraTemList=null;
	//private ModelFactory mf;
	public ParameterPropertyDescriptor(Object id, String displayName,List paraTemList, List idlTypeNames )
	{
		super(id,displayName);
	 
		this.idlTypeNames=idlTypeNames;
	 
		this.paraTemList=paraTemList;
	}
	public CellEditor createPropertyEditor(Composite parent){
	 
	 
	CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

	 {
		 protected Object openDialogBox(Control cellEditorWindow)
        {
		 	 
		 	//EditIDLTypeDialog dialog = new EditIDLTypeDialog(
		 	EditParameterDialog dialog = new EditParameterDialog(
		 	cellEditorWindow.getShell(),0);
		 	dialog.setIdlTList(idlTypeNames);
		  //  IDLTemplate template=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT); 
		  //  dialog.setIdlTemp(template);
		    dialog.setPameterList(paraTemList);
            dialog.open();
          if (!dialog.isState())
          	return null;
         
          return dialog.getPameterList();
        }
	};
	return result;
	
	
}

}
