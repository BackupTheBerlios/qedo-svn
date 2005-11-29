package ccm.wizards;

import java.io.IOException;

import org.eclipse.jface.dialogs.IDialogPage;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;
import org.omg.CORBA.COMM_FAILURE;

import MDE.BaseIDL.Contained;
import MDE.BaseIDL.ModuleDef;
import MDE.BaseIDL.ModuleDefHelper;
import Reflective.MofError;
import Reflective.NotSet;
import ccmio.repository.CCMRepository;


/**
 * The "New" wizard page allows setting the container for
 * the new file as well as the file name. The page
 * will only accept file name without the extension OR
 * with the extension that matches the expected one (ccm).
 */

public class RepositoryPage extends WizardPage {

	private Text moduleText;
	private Text refFileText;
	private CCMRepository repository;
	private Tree moduleTree;
	private ModuleDef module;
	
	private static String refFileName ="C:\\repository\\etc\\ccmRepositoryRoot.ref";
	
	private ISelection selection;


	/**
	 * Constructor for RepositoryPage.
	 * @param selection
	 */
	public RepositoryPage(ISelection selection) {
		super("repositoryPage");
		setTitle("CCM-Import/Export");
		setDescription("Repository-Module");
		this.selection = selection;
	}
	
	/**
	 * @see IDialogPage#createControl(Composite)
	 */
	public void createControl(Composite parent) {
		
		Composite 	container = new Composite(parent, SWT.NULL);
		GridLayout layout = new GridLayout();
		container.setLayout(layout);
		
		layout.numColumns = 2;
		layout.verticalSpacing = 9;

		// RepositoryRoot.ref
		// Label label = new Label(container, SWT.NULL);
		// label.setText("&RepositoryRoot:");

		refFileText = new Text(container, SWT.BORDER | SWT.SINGLE);
		GridData gd = new GridData(GridData.FILL_HORIZONTAL);
		refFileText.setLayoutData(gd);
		
		Button button = new Button(container, SWT.PUSH);
		button.setText("Browse...");
		button.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				handleRefBrowse();
			}
		});

		// Module-tree
		moduleTree = new Tree(container,SWT.BORDER | SWT.SINGLE);
		gd = new GridData(GridData.FILL_BOTH);
		moduleTree.setLayoutData(gd);
		moduleTree.setEnabled(false);
		moduleTree.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				handleSelection();
			}
		});
		
		initialize();
		dialogChanged();
		setControl(container);
	}
	
	/**
	 * initialize
	 */
	
	private void initialize() {
		refFileText.setText(refFileName);
		updateModuleTree();
	}
	/**
	 * Uses the standard file selection dialog to
	 * choose the new value for the reffile field.
	 */
	private void handleRefBrowse(){
		FileDialog dialog =
			new FileDialog(getShell());
		dialog.setText("Select the repository.ref file");
		dialog.setFileName("RepositoryRoot.ref");
		dialog.setFilterExtensions(new String[] {"*.ref","*.*"});
		String result;
		if ((result = dialog.open()) != null)
			refFileText.setText(result);
		updateModuleTree();
		dialogChanged();
	}
	/**
	 * Uses the standard file selection dialog to
	 * choose the new value for the module field.
	 */
	private void handleSelection(){
		TreeItem[] sels = moduleTree.getSelection();
		if (sels.length > 0)
		{
			TreeItem sel = sels[0];
			module = (ModuleDef) sel.getData();
		}
		dialogChanged();
	}

	/**
	 * checks if RepositoryRoot.ref and a module is choosen
	 */
	private void dialogChanged(){
		refFileName = getRefFileName();

		if (refFileName.length() == 0){
			updateStatus("RepositoryRoot.ref - File name must be specified");
			return;
		}
		if (module == null){
			updateStatus("Choose a Repository-Module.");
			return;
		}
		updateStatus(null);
	}
	/**
	 * Updates the ModelTree.
	 */
	private void updateModuleTree()
	{
		
		try
		{
			repository = new CCMRepository(refFileName);
			// gets all module
			MDE.BaseIDL.ModuleDef[] repmodules = 
				repository.getMDE().base_idl_ref().module_def_ref().all_of_class_module_def();
			moduleTree.removeAll();
			moduleTree.setEnabled(false);
			for (int i=0;i<repmodules.length;i++)
				try { repmodules[i].defined_in(); }
				catch (NotSet e)
				{
					TreeItem  module = new TreeItem(moduleTree,SWT.NULL);
					module.setText(repmodules[i].identifier());
					module.setData(repmodules[i]);
					// module.setExpanded(true);
					updateModuleTree(module,repmodules[i]);
				}
			if (repmodules.length == 0){
				updateStatus("Can´t find Module in Repository"); 
				return;
			}
			
			moduleTree.setEnabled(true);
			updateStatus(null);
		}
		catch (IOException ex)
			{ updateStatus("Can´t open Repository.ref-File"); return; }
		catch (MofError ex)
			{ updateStatus("MofError" + ex.getMessage()); return; }
		catch (COMM_FAILURE ex)
			{ updateStatus("Can´t connect to Repository"); return; }
	
	}
	
	
	private void updateModuleTree(TreeItem treeItem,ModuleDef repmodule) throws MofError
	{
		Contained[] contens = repmodule.contents();
		for (int i=0;i<contens.length;i++)
		{
			try { 
				ModuleDef moduleDef = ModuleDefHelper.narrow(contens[i]);
				TreeItem  module = new TreeItem(treeItem,SWT.NULL);
				module.setText(moduleDef.identifier());
				module.setData(moduleDef);
				// module.setExpanded(true);
				updateModuleTree(module,moduleDef);
			}
			catch (Exception e) {}
		}
	}

	private void updateStatus(String message) {
		setErrorMessage(message);
		setPageComplete(message == null);
		
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		setPageComplete(true);
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}

	public String getRefFileName() {
		return refFileText.getText();
	}

	public CCMRepository getRepository(){
		return repository;
	}

	public ModuleDef getModule(){
		return module;
	}

}