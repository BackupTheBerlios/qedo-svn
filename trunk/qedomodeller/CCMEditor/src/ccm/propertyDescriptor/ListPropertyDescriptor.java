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

import ccm.dialogs.SelectValuesDialog;

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ListPropertyDescriptor  extends PropertyDescriptor{	
	//private OperationDef abstObj;
	private List values=new LinkedList();
	private List allValues=null;
	private String discription;
	//private ModelFactory mf;
	public ListPropertyDescriptor(Object id, String displayName,List values, List allValues, String discription  )
	{
		super(id,displayName);
	    this.discription=discription;
		this.values=values;
	 
		this.allValues=allValues;
	}
	public CellEditor createPropertyEditor(Composite parent){
	 
	 
	CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

	 {
		 protected Object openDialogBox(Control cellEditorWindow)
        {
		 	 
		 	//EditIDLTypeDialog dialog = new EditIDLTypeDialog(
		 	SelectValuesDialog dialog = new SelectValuesDialog(
		 	cellEditorWindow.getShell(),0);
		 	
		 	dialog.setValues(values);
		    dialog.setAllValues(allValues);
		    dialog.setDiscription(discription);
            dialog.open();
          if (!dialog.isState())
          	return null;
         
          return dialog.getValues();
        }
	};
	return result;
	
	
}

}
 