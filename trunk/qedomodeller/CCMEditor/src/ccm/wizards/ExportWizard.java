package ccm.wizards;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.operation.IRunnableWithProgress;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.IExportWizard;
import org.eclipse.ui.IWorkbench;
import org.omg.CORBA.COMM_FAILURE;

import Reflective.MofError;
import ccm.model.CCMModelManager;
import ccmio.repository.CCMExport;
import ccmio.repository.CCMRepository;


public class ExportWizard extends Wizard implements IExportWizard {

	private ExportToRepositoryPage repository_page;
	private IStructuredSelection selection;


	public ExportWizard() {
	
		super();
		setNeedsProgressMonitor(true);
	}
	

	public void addPages() {
		repository_page = new ExportToRepositoryPage(selection);
		addPage(repository_page);
	}


	/*	Invoked when the Finish-Button is pressed.
	 * 	A thread with the main export function is 
	 *  created and executed.
	 */
	
	public boolean performFinish() {
 
		final IFile file = (IFile) selection.getFirstElement();
		final CCMRepository repository = repository_page.getRepository();
//		final MDE.BaseIDL.ModuleDef repository_module  = repository_page.getModule();
		
		
		IRunnableWithProgress op = new IRunnableWithProgress() {
			
			public void run(IProgressMonitor monitor) throws InvocationTargetException {
				try {
					export(repository, file, monitor); 
					} 
				catch (CoreException e) {
					//e.printStackTrace();
					throw new InvocationTargetException(e);
				} finally {
					monitor.done();
				}
			}
			
		};
		
		try { 
			getContainer().run(true, false, op); 
			 
			} 
		catch (InterruptedException e) {
			return false;
		} catch (InvocationTargetException e) {
			e.printStackTrace();
			Throwable realException = e.getTargetException();
			MessageDialog.openError(getShell(), "Error", realException.getMessage());
			return false;
		}

		return true;
	}
	
	
	
	/*
	 * The main export method.
	 */

	private void export (
			CCMRepository repository, 
//			ModuleDef repository_module, 
			IFile file, 
			IProgressMonitor monitor) throws CoreException 
	{			
		 
		monitor.beginTask("Exporting " + file + " to Repository", 2);
		CCMModelManager manager = new CCMModelManager();
		
		if (repository==null) {
			throwCoreException("Error connecting to Repository.");
		}
		
		try {
			//monitor.setTaskName("Loading CCM Project...");
		 
			manager.load(file.getFullPath());
			monitor.worked(1);			

			//monitor.setTaskName("Exporting CCM Project...");
			CCMExport exporter = new CCMExport();
			exporter.exports(repository, repository_page.getModelName(), manager.getModel());
			monitor.worked(2);		
			
		}
		catch (MofError ex) {
			//ex.printStackTrace();
			throwCoreException("MOF Error: " + ex.getMessage()); }
		catch (IOException e) {
			//e.printStackTrace();
			throwCoreException("Error loading file."); }
		catch (COMM_FAILURE ex) {
			//ex.printStackTrace();
			throwCoreException("Error connecting to Repository."); }

	}
	

	
	private void throwCoreException(String message) throws CoreException {
		IStatus status = new Status(IStatus.ERROR, "CCM", IStatus.OK, message, null);
		throw new CoreException(status);
	}



	public void init(IWorkbench workbench, IStructuredSelection selection) {
		this.selection = selection;
	}

	
}