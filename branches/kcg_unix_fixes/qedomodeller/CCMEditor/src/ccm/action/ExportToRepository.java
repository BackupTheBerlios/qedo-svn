/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution
 *
 * Contributors:
 *             Eduard Weiss
 *
 */

package ccm.action;

import java.io.IOException;

import org.eclipse.gef.ui.actions.EditorPartAction;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.IEditorPart;
import org.omg.CORBA.COMM_FAILURE;

import CCMModel.CCM;
import Reflective.MofError;
import ccm.editors.TypedPage;
import ccmio.repository.CCMExport;
import ccmio.repository.CCMRepository;

/**
 * The Export to Repository-Button
 */
public class ExportToRepository extends EditorPartAction {
    
	
    static public String RUN_CONVERTER = "Action hinzu";

    private CCM ccm;
    

    /**
     * @param editor
     */
    public ExportToRepository(IEditorPart activeEditorPart) {
        super(activeEditorPart);
        setDescription("export from ccm-repository");
        setText("Run export");
        init();
    }


    /**
     * @see org.eclipse.gef.ui.actions.WorkbenchPartAction#init()
     */
    protected void init() {
        setToolTipText("exports ccm-model from repository");
        setId(RUN_CONVERTER);
    }

    /**
     * @see org.eclipse.jface.action.IAction#run()
     */
    public void run() { 
    	CCM ccm=((TypedPage)getEditorPart()).getCcmView().getCCM();
	    FileDialog fd = new FileDialog(getEditorPart().getEditorSite().getShell());
	    fd.setFilterExtensions(new String[] {"*.ref","*.*"});
	    fd.setText("get the RepositoryRoot.ref file");
	    String RepositoryRootRefFile = fd.open();
		// connect to repository
		try{
			CCMRepository repository = new CCMRepository(RepositoryRootRefFile);
			CCMExport.exports(repository,ccm);
			MessageDialog.openInformation(null,"Result","Export successfull");	
		}
		catch(MofError ex)
		{ MessageDialog.openError(null,"Error","MOF Error : " + ex.getMessage()); }
		catch(IOException ex)
		{ MessageDialog.openError(null,"Error","Can´t open RepositoryRoot.ref-file."); }
		catch(COMM_FAILURE ex)
		{ MessageDialog.openError(null,"Error","Can´t connect to repository."); }
    }

    /**
     * @see org.eclipse.gef.ui.actions.WorkbenchPartAction#calculateEnabled()
     */
    protected boolean calculateEnabled() {
        //if(!(getEditorPart()instanceof DiagramPage) )return false;
        //return getEditorPart() != null;
		return true;
    }
    /**
     * @see org.eclipse.gef.ui.actions.EditorPartAction#setEditorPart(org.eclipse.ui.IEditorPart)
     */
    public void setEditorPart(IEditorPart part) {
        super.setEditorPart(part);
    }
}
