package ccm.wizards;

import java.io.IOException;
import java.util.List;
import java.util.ListIterator;

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

import MDE._CCMPackage;
import MDE._CCMPackageHelper;
import MDE.BaseIDL.Contained;
import MDE.BaseIDL.ModuleDef;
import MDE.BaseIDL.ModuleDefHelper;
import Reflective.MofError;
import Reflective.__RefPackageStub;
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
	private Tree packageTree;
	private ModuleDef module;
	private _CCMPackage current_package;
	private ModuleDef[] modules;
	
	//private static String refFileName ="C:\\repository\\etc\\ccmRepositoryRoot.ref";
	private static String refFileName ="";
	
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
//	    refFileName = System.getProperty("java.io.tmpdir") + "eUMLRepositoryRoot.ref"; 
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
		//moduleTree = new Tree(container,SWT.BORDER |SWT.MULTI | SWT.V_SCROLL);
		packageTree = new Tree(container,SWT.BORDER | SWT.SINGLE);
		gd = new GridData(GridData.FILL_BOTH);
		packageTree.setLayoutData(gd);
		packageTree.setEnabled(false);
		packageTree.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				//moduleTree.getSelection();
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
		if (!refFileName.equals(""))
			updatePackageTree();
	//	else if(!refFileName.equals("")){
	//		try{
	//			repository = new CCMRepository(refFileName);
	//		}
	//		catch (Exception e){e.printStackTrace();}
	//	}
			
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
		dialogChanged();
		updatePackageTree();
		
		
	}
	/**
	 * Uses the standard file selection dialog to
	 * choose the new value for the module field.
	 */
	private void handleSelection(){
		TreeItem[] sels = packageTree.getSelection();
		//modules= new ModuleDef[sels.length];
		//for (int i=0;i<sels.length;i++){
		//	modules[i]=(ModuleDef)sels[i].getData();
		//}
		if (sels.length > 0)
		{
			TreeItem sel = sels[0];
			current_package = (_CCMPackage) sel.getData();
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
		if (current_package == null){
			updateStatus("Choose a Repository-Package.");
			return;
		}
		updateStatus(null);
		//updateModuleTree();
	}
	/**
	 * Updates the ModelTree.
	 */
	private void updatePackageTree()
	{
		
		try
		{
			repository = new CCMRepository(refFileName);
			// gets all module
			List reppackages = 
				repository.getMDE();
//				repository.getMDE().base_idl_ref().module_def_ref().all_of_class_module_def();
			packageTree.removeAll();
			packageTree.setEnabled(false);
			ListIterator package_iter;
			for (ListIterator it = reppackages.listIterator(); it.hasNext();)
//			for (int i=0;i< reppackages.length;i++)
			{
//					_CCMPackage temp_package = _CCMPackageHelper.narrow(it.next());
					__RefPackageStub ref_pack = (__RefPackageStub)it.next();
					_CCMPackage temp_package;
					try {
						temp_package = _CCMPackageHelper.narrow(ref_pack);
					} catch (Exception e)
					{
						// not a CCM Package
						continue;
					}
					TreeItem  tree_package = new TreeItem(packageTree,SWT.NULL);
					tree_package.setText(temp_package.medini_get_name());
					tree_package.setData(temp_package);
					// module.setExpanded(true);
					// disabled for now
					//	updatePackageTree(tree_package,reppackages[i]);
			}
			if (reppackages.isEmpty()){
				updateStatus("Can´t find Package in Repository"); 
				return;
			}
			
			packageTree.setEnabled(true);
			updateStatus(null);
		}
		catch (IOException ex)
			{ updateStatus("Can´t open Repository.ref-File"); return; }
		catch (MofError ex)
			{ updateStatus("MofError" + ex.getMessage()); return; }
		catch (COMM_FAILURE ex)
			{ updateStatus("Can´t connect to Repository"); return; }
	
	}
	
	
	private void updatePackageTree(TreeItem treeItem,ModuleDef repmodule) throws MofError
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
				updatePackageTree(module,moduleDef);
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

	public _CCMPackage getPackage(){
		return current_package;
	}
	public ModuleDef[] getModules(){
		return modules;
	}

}