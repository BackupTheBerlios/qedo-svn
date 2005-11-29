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
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.OperationDef;
import CCMModel.Typed;

import ccm.CCMConstants;
import ccm.dialogs.EditIDLTypeDialog;
import ccm.model.ModelFactory;
import ccm.model.template.IDLTemplate;

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class IDLtypePropertyDescriptor extends PropertyDescriptor{
	private IDLTemplate idlTemp;
	//private List idlT=new LinkedList();
    private List idlTypeNames=new LinkedList();
	//private ModelFactory mf;
	public IDLtypePropertyDescriptor(Object id, String displayName, IDLTemplate idlTemp,List idlTypeNames )
	{
		super(id,displayName);
		this.idlTemp=idlTemp;
		this.idlTypeNames=idlTypeNames;
		 
		}
	public CellEditor createPropertyEditor(Composite parent){
		 
	 
		CellEditor result = new ExtendedDialogCellEditor(parent, new LabelProvider())

		 {
			 protected Object openDialogBox(Control cellEditorWindow)
            {
			 	 
			 	EditIDLTypeDialog dialog = new EditIDLTypeDialog(
                cellEditorWindow.getShell(),0);
			 	dialog.setIdlTList(idlTypeNames);
			   // IDLTemplate template=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT); 
			    dialog.setIdlTemp(idlTemp);
			 	dialog.open();
              if (!dialog.isState())
              	return null;
             
              return dialog.getIdlTemp();
            }
		};
		return result;
		
	}

}
