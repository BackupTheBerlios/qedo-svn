package ccm.wizards;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Status;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.operation.IRunnableWithProgress;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWizard;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.ide.IDE;

import CCMModel.CCM;
import Reflective.MofError;
import ccm.model.CCMModelManager;
import ccmio.repository.CCMImport;
import ccmio.repository.CCMRepository;

/**
 * This is a sample new wizard. Its role is to create a new file 
 * resource in the provided container. If the container resource
 * (a folder or a project) is selected in the workspace 
 * when the wizard is opened, it will accept it as the target
 * container. The wizard creates one file with the extension
 * "ccm". If a sample multi-page editor (also available
 * as a template) is registered for the same extension, it will
 * be able to open it.
 */

public class ImportWizard extends Wizard implements INewWizard {
	private ImportWizardPage page;
	private RepositoryPage repositoryPage;
	private ISelection selection;
	private String version;

	/**
	 * Constructor for SampleNewWizard.
	 */
	public ImportWizard() {
		super();
		setNeedsProgressMonitor(true);
		 
	}
	
	/**
	 * Adding the page to the wizard.
	 */

	public void addPages() {
		 
		page = new ImportWizardPage(selection);
		addPage(page);
		repositoryPage = new RepositoryPage(selection);
		addPage(repositoryPage);
	}

	/**
	 * This method is called when 'Finish' button is pressed in
	 * the wizard. We will create an operation and run it
	 * using wizard as execution context.
	 */
	public boolean performFinish() {
		 
		final String containerName = page.getContainerName();
		final String fileName = page.getFileName();
		final MDE.BaseIDL.ModuleDef repModule  = repositoryPage.getModule();
		final CCMRepository repository = repositoryPage.getRepository();
		version=page.getVersion();
		
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IResource resource = root.findMember(new Path(containerName));
		if (!resource.exists() || !(resource instanceof IContainer)) {
			MessageDialog.openError(getShell(),"Error","Container \"" + containerName + "\" does not exist.");
		}
		IContainer container = (IContainer) resource;
		IFile file = container.getFile(new Path(fileName));
		if (file.exists())
			if (!MessageDialog.openQuestion(getShell(),
					"Overwrite?", "File \"" + file.getName() + "\" already exists. Overwrite?"))
				return false;
		
		IRunnableWithProgress op = new IRunnableWithProgress() {
			public void run(IProgressMonitor monitor) throws InvocationTargetException {
				try {
					doFinish(containerName, fileName, repository, repModule, monitor);
				} catch (CoreException e) {
					throw new InvocationTargetException(e);
				} finally {
					monitor.done();
				}
			}
		};
		try {
			 
			getContainer().run(true, false, op);
		} catch (InterruptedException e) {
			return false;
		} catch (InvocationTargetException e) {
			Throwable realException = e.getTargetException();
			MessageDialog.openError(getShell(), "Error", realException.getMessage());
			return false;
		}
		return true;
	}
	
	/**
	 * The worker method. It will find the container, create the
	 * file if missing or just replace its contents, and open
	 * the editor on the newly created file.
	 */

	private void doFinish(
		String containerName,
		String fileName,
		CCMRepository repository,
		MDE.BaseIDL.ModuleDef module,
		IProgressMonitor monitor)
		throws CoreException
	{
		// create a sample file
		monitor.beginTask("Creating " + fileName, 4);
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IResource resource = root.findMember(new Path(containerName));
		if (!resource.exists() || !(resource instanceof IContainer)) {
			throwCoreException("Container \"" + containerName + "\" does not exist.");
		}
		IContainer container = (IContainer) resource;

		final IFile file = container.getFile(new Path(fileName));
		monitor.worked(1);
		monitor.setTaskName("create ccm model...");
		createCCMFile(file,repository,module,monitor);

		monitor.worked(3);
		monitor.setTaskName("Opening file for editing...");

		getShell().getDisplay().asyncExec(new Runnable() {
			public void run() {
				System.out.println(">>>>>>>>>>>>>import 5");
				IWorkbenchPage page =
					PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
				try {
					IEditorPart editor = IDE.openEditor(page, file, true);
//					if (editor instanceof CCMEditor);
//						CCMEditor ccmeditor = (CCMEditor)IDE.openEditor(page, file, true);
				} catch (PartInitException e) {
				}
			}
		});
		monitor.worked(4);

	}
	
	/**
	 * We will initialize file contents with a sample text.
	 */

	private InputStream openContentStream() {
		String contents =version;
		return new ByteArrayInputStream(contents.getBytes());
	}

	private void throwCoreException(String message) throws CoreException {
		IStatus status =
			new Status(IStatus.ERROR, "CCM", IStatus.OK, message, null);
		throw new CoreException(status);
	}

	/**
	 * We will accept the selection in the workbench to see if
	 * we can initialize from it.
	 * @see IWorkbenchWizard#init(IWorkbench, IStructuredSelection)
	 */
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		this.selection = selection;
	}
	
	private void createCCMFile(
			IFile file,
			CCMRepository repository,
			MDE.BaseIDL.ModuleDef module,
			IProgressMonitor monitor) throws CoreException
	{ 
		CCMModelManager modelManager = new CCMModelManager();
		IPath path = file.getFullPath();
		CCM ccm= null;

		try { // try to create file
			InputStream stream = openContentStream();
			if (!file.exists())
				file.create(stream, true, monitor);
			else
				file.setContents(stream,true,true,monitor);
			stream.close();
		} catch (IOException e) {
			throwCoreException("can´t create File \"" + file.getName() + "\".");
		}

		modelManager.createModelView(file);

		Resource resource = modelManager.resource;
		
		for (int i=0;i<resource.getContents().size();i++)
			if (resource.getContents().get(i) instanceof CCM)
				ccm = (CCM)resource.getContents().get(i);
		if (ccm == null)
			throwCoreException("Can´t find CCM-Object");

		try
		{
			CCMImport.imports(repository,module,ccm);
		}
		catch (MofError ex)
		{ throwCoreException("Mof Error : " + ex.getMessage()); }

		monitor.worked(2);
		monitor.setTaskName("save ccm model to file...");
		try{
			modelManager.save(path);
		}
		catch (IOException ex)
		{ throwCoreException("can't save the imported model to the new file : " + ex.getMessage()); }
	}
}