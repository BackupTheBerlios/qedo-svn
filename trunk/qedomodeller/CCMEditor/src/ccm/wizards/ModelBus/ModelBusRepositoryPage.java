package ccm.wizards.ModelBus;

import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.ListIterator;
import java.util.Properties;
import java.util.Vector;

import org.eclipse.jface.dialogs.IDialogPage;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.mddi.modelbus.adapter.user.AdapterStub;
import org.eclipse.mddi.modelbus.adapter.user.impl.AdapterStubImpl;
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
import RepositoryResult.ModelInformation;
import RepositoryResult.RepositoryResultFactory;
import RepositoryResult.RepositoryResultPackage;
import ccmio.repository.CCMRepository;


/**
 * The "New" wizard page allows setting the container for
 * the new file as well as the file name. The page
 * will only accept file name without the extension OR
 * with the extension that matches the expected one (ccm).
 */

public class ModelBusRepositoryPage extends WizardPage {

	private AdapterStub adapterStub;
	private String modelId;
	private String modelName;
	
	private Tree packageTree;
	
	private ISelection selection;
    private Text refFileText; 

    private RepositoryResultPackage resultPackage = RepositoryResultPackage.eINSTANCE;
	/**
	 * Constructor for RepositoryPage.
	 * @param selection
	 */
	public ModelBusRepositoryPage(ISelection selection) {
		super("ModeBusRepositoryPage");
		setTitle("ModelBus Repository Browser");
		setDescription("Repository-Module");
		this.selection = selection;
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

		GridData gd = new GridData(GridData.FILL_HORIZONTAL);

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
			updatePackageTree();
			
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
			modelId = (String) sel.getData();
		}
		dialogChanged();
	}

	/**
	 * checks if RepositoryRoot.ref and a module is choosen
	 */
	private void dialogChanged(){

		if (modelId == null){
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
		System.out.println("Test");
		Properties modelBusProperties = new Properties();
		modelBusProperties.put(AdapterStub.PROP_REGISTRY_LOCATION, "http://monarch.fokus.fraunhofer.de:8080/WebRegistry/services/WebRegistry");

	
		try {
			   adapterStub = new AdapterStubImpl(modelBusProperties);
			   
			   Object[] inputs2 = new Object[0];
			   
			   Object[] outputs = adapterStub.getGenericServiceInvocation().consume("getAllModelInformation",inputs2);
			   Collection[] models = (Collection[])outputs[0];
			   
			   packageTree.removeAll();
			   packageTree.setEnabled(false);

			   System.out.println("found " + models.length + " models in repository");
			   for (int i=0; i<models.length;i++)
			   {
				   Vector modelvector = (Vector)models[i];
				   for (int v=0; v<modelvector.size();v++)
				   {
					   ModelInformation modelinfo = (ModelInformation)modelvector.get(v);
					    
					   System.out.println(modelinfo.getName()+" - " + modelinfo.getUUID()+" - "+modelinfo.getMetaModelName());
					   
						TreeItem  tree_package = new TreeItem(packageTree,SWT.NULL);
						tree_package.setText(modelinfo.getName() + " ( Type: " + modelinfo.getMetaModelName() + ")");
						tree_package.setData(modelinfo.getUUID());
						// module.setExpanded(true);
						// disabled for now
						//	updatePackageTree(tree_package,reppackages[i]);
				   }				   
			   }
			   
			   if (models.length == 0){
					updateStatus("Can´t find Package in Repository"); 
					return;
			   }
				
				packageTree.setEnabled(true);
				updateStatus(null);
			   
		} catch (Exception e){
			e.printStackTrace();
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

	public String getModelId(){
		return this.modelId;
	}


}