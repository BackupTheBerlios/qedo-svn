package ccm.wizards;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.Path;
import org.eclipse.jface.dialogs.IDialogPage;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.dialogs.ContainerSelectionDialog;


/**
 * The "New" wizard page allows setting the container for
 * the new file as well as the file name. The page
 * will only accept file name without the extension OR
 * with the extension that matches the expected one (ccm).
 */

public class InputFilePage extends WizardPage {
	private Text containerText, 
					fileText, 
					versionText;
	
	private ISelection selection;
	private String fileName;


	/**
	 * Constructor for ImportWizardPage.
	 * @param selection
	 */
	public InputFilePage(ISelection selection, String fileName) {
		super("importWizardPage");
		setTitle(" give new file name");
		setDescription("This wizard imports a ccmmodel from a repository and creates a new file with *.ccm extension that can be opened by a multi-page editor.");
		this.selection = selection;
		this.fileName=fileName;
	}
	
	/**
	 * @see IDialogPage#createControl(Composite)
	 */
	public void createControl(Composite parent) {
		Composite container = new Composite(parent, SWT.NULL);
		GridLayout layout = new GridLayout();
		container.setLayout(layout);
		layout.numColumns = 2;
		layout.verticalSpacing = 9;
		 
		
		// file
		//Label label = new Label(container, SWT.NULL);
	 	Label label = new Label(container, SWT.NULL);
	 	label.setText("&File name:");

	 	fileText = new Text(container, SWT.BORDER | SWT.SINGLE);
	 	GridData gd = new GridData(GridData.FILL_HORIZONTAL);
	 	fileText.setLayoutData(gd);
	 	fileText.addModifyListener(new ModifyListener() {
	 		public void modifyText(ModifyEvent e) {
	 			dialogChanged();
	 		}
	 	});

	 	//label = new Label(container, SWT.NULL);
	 	//label.setText("");

		// version
		 
		initialize();
		dialogChanged();
		setControl(container);
	}
	
	/**
	 * Tests if the current workbench selection is a suitable
	 * container to use.
	 */
	
	private void initialize() {
		if (selection!=null && selection.isEmpty()==false && selection instanceof IStructuredSelection) {
			IStructuredSelection ssel = (IStructuredSelection)selection;
			if (ssel.size()>1) return;
			Object obj = ssel.getFirstElement();
			if (obj instanceof IResource) {
				IContainer container;
				if (obj instanceof IContainer)
					container = (IContainer)obj;
				else
					container = ((IResource)obj).getParent();
				containerText.setText(container.getFullPath().toString());
			}
		}
		fileText.setText(fileName);
		//versionText.setText("1.0");
	}
	/**
	 * Uses the standard container selection dialog to
	 * choose the new value for the container field.
	 */

	private void handleBrowse() {
		ContainerSelectionDialog dialog =
			new ContainerSelectionDialog(
				getShell(),
				ResourcesPlugin.getWorkspace().getRoot(),
				false,
				"Select new file container");
		if (dialog.open() == ContainerSelectionDialog.OK) {
			Object[] result = dialog.getResult();
			if (result.length == 1) {
				containerText.setText(((Path)result[0]).toOSString());
			}
		}
	}
	/**
	 * Ensures that all text fields are set.
	 */

	private void dialogChanged() {
		String container = getContainerName();
		String fileName = getFileName();

		if (container.length() == 0) {
			updateStatus("File container must be specified"); 
			return;
		}
		if (fileName.length() == 0) {
			updateStatus("File name must be specified"); 
			return;
		}
		int dotLoc = fileName.lastIndexOf('.');
		if (dotLoc != -1) {
			String ext = fileName.substring(dotLoc + 1);
			if (ext.equalsIgnoreCase("ccm") == false) {
				updateStatus("File extension must be \"ccm\"");
				return;
			}
		}

		updateStatus(null);
	}

	private void updateStatus(String message) {
		setErrorMessage(message);
		setPageComplete(message == null);
	}
	public String getContainerName() {
		return containerText.getText();
	}
	public String getFileName() {
		return fileText.getText();
		//return "import.ccm";
	}
	public String getVersion(){
	    return versionText.getText();
	}
}
 