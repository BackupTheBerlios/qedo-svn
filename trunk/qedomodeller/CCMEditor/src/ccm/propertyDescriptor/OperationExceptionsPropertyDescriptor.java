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

import ccm.dialogs.EditExceptionsofOperationDialog;

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class OperationExceptionsPropertyDescriptor extends PropertyDescriptor{

    private List current_exceptions = new LinkedList();
    private List possible_exceptions = null;
    //private ModelFactory mf;
	public OperationExceptionsPropertyDescriptor(Object id, String displayName, List current_exceptions,List possible_exceptions)
	{
		super(id,displayName);
		this.current_exceptions=current_exceptions;
		this.possible_exceptions = possible_exceptions;
		 
		}
	public CellEditor createPropertyEditor(Composite parent){
		 
	 
		CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

		 {
			 protected Object openDialogBox(Control cellEditorWindow)
            {
			 	 
			 	EditExceptionsofOperationDialog dialog = new EditExceptionsofOperationDialog (
                cellEditorWindow.getShell(),0);
			 	dialog.setMemberList(current_exceptions);
			 	dialog.set_possible_excpetions(possible_exceptions);
			 	dialog.open();
              if (!dialog.isState())
              	return null;
             
              return dialog.getMemberList();
            }
		};
		return result;
		
	}

}
