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

import CCMModel.Assembly;
import ccm.dialogs.EditConnectionDialog;

/**
 * @author Siegercn
 *
 */
public class ConnectionPropertyDescriptor  extends PropertyDescriptor{	
	//private OperationDef abstObj;
	private List packages =null;
	private List aConnections=null;
	private Assembly  ass;
	//private ModelFactory mf;
	public ConnectionPropertyDescriptor(Object id, String displayName,Assembly  ass)
	{
		super(id,displayName);
	 
		this.ass=ass;
		aConnections=ass.getConnection();
	}
	public CellEditor createPropertyEditor(Composite parent){
	 
	 
	CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

	 {
		 protected Object openDialogBox(Control cellEditorWindow)
        {
		 	 
		 	//EditIDLTypeDialog dialog = new EditIDLTypeDialog(
		 	EditConnectionDialog dialog = new EditConnectionDialog(
		 	cellEditorWindow.getShell(),0);
		 	dialog.setAssembly(ass);
		  //  IDLTemplate template=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT); 
		  //  dialog.setIdlTemp(template);
		    dialog.setPameterList(aConnections);
            dialog.open();
          if (!dialog.isState())
          	return null;
         
          return dialog.getPameterList();
        }
	};
	return result;
	
	
}

}
 
 