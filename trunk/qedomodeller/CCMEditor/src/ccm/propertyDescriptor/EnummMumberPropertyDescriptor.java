/*
 * Created on 29.09.2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.propertyDescriptor;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.ui.celleditor.ExtendedDialogCellEditor;
import org.eclipse.jface.viewers.CellEditor;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.IDLType;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import ccm.CCMConstants;
import ccm.dialogs.AddOperationDialog;
import ccm.dialogs.CreateEnumDefDialog;
import ccm.dialogs.CreateExceptionDefDialog;
import ccm.dialogs.EditEnumMumberDialog;
import ccm.dialogs.EditFieldDialog;
import ccm.dialogs.EditIDLTypeDialog;
import ccm.dialogs.EditParameterDialog;
import ccm.model.ModelFactory;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class EnummMumberPropertyDescriptor   extends PropertyDescriptor{	
	//private OperationDef abstObj;
 
	private List fieldTemList=null;
	//private ModelFactory mf;
	public EnummMumberPropertyDescriptor (Object id, String displayName,List fieldTemList  )
	{
		super(id,displayName);
		this.fieldTemList=fieldTemList;
	}
	public CellEditor createPropertyEditor(Composite parent){
	 
	 
	CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

	 {
		 protected Object openDialogBox(Control cellEditorWindow)
        {
		 	 
		 	//EditIDLTypeDialog dialog = new EditIDLTypeDialog(
		 	//CreateEnumDefDialog dialog = new CreateEnumDefDialog(
		 	EditEnumMumberDialog dialog = new EditEnumMumberDialog(
		 	cellEditorWindow.getShell(),0);
		 	//dialog.setIdlTList(idlTypeNames);
		  //  IDLTemplate template=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT); 
		  //  dialog.setIdlTemp(template);
		    dialog.setMemberList(fieldTemList);
            dialog.open();
          if (!dialog.isState())
          	return null;
         
          return dialog.getMemberList();
        }
	};
	return result;
	
	
}

}

