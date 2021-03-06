package ccm.dialogs;


import java.util.Iterator;
import java.util.LinkedList;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Shell;

import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.CCMModelFactory;
import CCMModel.ConnectionEnd;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;

/**
 * @author Siegercn
*/
public class EditConnectionDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	 
	private Button enter;
	private Button cancel;
	private Composite composite3;
	 
	private Button removeP;
	private Button editP;
	private Button addP;
	 
	private Label parLb;
	private List par;
	 
	private Composite composite2;
	 
	private Shell dialogShell; 
	protected CCMModelFactory factory=CCMModelManager.getFactory();
	private boolean state=false;
	 
	private String repositoryId="";
	 
	private java.util.List compFileList=new LinkedList();
	//private java.util.List idlTList=new LinkedList();
	//private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
	private String absName="";
	private java.util.List pkgs;
	private Assembly ass;
	private Shell parent ;
	public EditConnectionDialog(Shell parent, int style) {
		super(parent, style);
		this.parent=parent;
	}

	/**
	* Opens the Dialog Shell.
	* Auto-generated code - any changes you make will disappear.
	*/
	public void open(){
		try {
			preInitGUI();
	
			Shell parent = getParent();
			dialogShell = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
			dialogShell.setText(getText());
			 
		 
			composite2 = new Composite(dialogShell,SWT.NO_RADIO_GROUP);
			 
			removeP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			editP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			addP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			parLb = new Label(composite2,SWT.NULL);
			par = new List(composite2,SWT.BORDER|SWT.V_SCROLL);
			 
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Edit Connections");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(407,280));
	
			 
	
		 
			final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 400;
			composite2LData.heightHint = 220;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(400,190));
	
			 
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",9,1);
			 
	 
	 
		//	final Font repositoryIDTxtfont = new Font(Display.getDefault(),"Tahoma",10,0);
		  
	
			FormData removePLData = new FormData();
			removePLData.height = 23;
			removePLData.width = 80;
			removePLData.left =  new FormAttachment(800, 1000, 0);
			removePLData.right =  new FormAttachment(986, 1000, 0);
			removePLData.top =  new FormAttachment(740, 1000, 0);
			removePLData.bottom =  new FormAttachment(965, 1000, 0);
			removeP.setLayoutData(removePLData);
			removeP.setText("REMOVE");
			removeP.setSize(new org.eclipse.swt.graphics.Point(80,23));
			final Font removePfont = new Font(Display.getDefault(),"Tahoma",8,1);
			removeP.setFont(removePfont);
			removeP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					removePMouseDown(evt);
				}
			});
	
			FormData editPLData = new FormData();
			editPLData.height = 23;
			editPLData.width = 80;
			editPLData.left =  new FormAttachment(800, 1000, 0);
			editPLData.right =  new FormAttachment(986, 1000, 0);
			editPLData.top =  new FormAttachment(471, 1000, 0);
			editPLData.bottom =  new FormAttachment(700, 1000, 0);
			editP.setLayoutData(editPLData);
			editP.setText("EDIT");
			editP.setSize(new org.eclipse.swt.graphics.Point(80,23));
			editP.setFont(removePfont);
			editP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					editPMouseDown(evt);
				}
			});
	
			FormData addPLData = new FormData();
			addPLData.height = 23;
			addPLData.width = 80;
			addPLData.left =  new FormAttachment(800, 1000, 0);
			addPLData.right =  new FormAttachment(986, 1000, 0);
			addPLData.top =  new FormAttachment(209, 1000, 0);
			addPLData.bottom =  new FormAttachment(430, 1000, 0);
			addP.setLayoutData(addPLData);
			addP.setText("ADD");
			addP.setSize(new org.eclipse.swt.graphics.Point(80,23));
			addP.setFont(removePfont);
			addP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					addPMouseDown(evt);
				}
			});
	 
	 
	
			FormData parLbLData = new FormData();
			parLbLData.height = 22;
			parLbLData.width = 388;
			parLbLData.left =  new FormAttachment(38, 1000, 0);
			parLbLData.right =  new FormAttachment(758, 1000, 0);
			parLbLData.top =  new FormAttachment(70, 1000, 0);
			parLbLData.bottom =  new FormAttachment(170, 1000, 0);
			parLb.setLayoutData(parLbLData);
			parLb.setText("Parameters :");
			parLb.setSize(new org.eclipse.swt.graphics.Point(388,22));
			parLb.setFont(idlBtnfont);
	
			FormData parLData = new FormData();
			parLData.height = 178;
			parLData.width = 388;
			parLData.left =  new FormAttachment(38, 1000, 0);
			parLData.right =  new FormAttachment(758, 1000, 0);
			parLData.top =  new FormAttachment(209, 1000, 0);
			parLData.bottom =  new FormAttachment(960, 1000, 0);
			par.setLayoutData(parLData);
			par.setFont(removePfont);
			 
			par.setSize(new org.eclipse.swt.graphics.Point(388,178));
	
			 
	 
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 386;
			composite3LData.heightHint = 34;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(386,34));
			composite3.setFont(removePfont);
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(775, 1000, 0);
			cancelLData.right =  new FormAttachment(976, 1000, 0);
			cancelLData.top =  new FormAttachment(102, 1000, 0);
			cancelLData.bottom =  new FormAttachment(847, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(77,23));
			cancel.setFont(removePfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseUp(MouseEvent evt) {
					cancelMouseUp(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 23;
			enterLData.width = 77;
			enterLData.left =  new FormAttachment(545, 1000, 0);
			enterLData.right =  new FormAttachment(745, 1000, 0);
			enterLData.top =  new FormAttachment(102, 1000, 0);
			enterLData.bottom =  new FormAttachment(847, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(77,23));
			enter.setFont(removePfont);
			enter.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					enterMouseDown(evt);
				}
			});
			FormLayout composite3Layout = new FormLayout();
			composite3.setLayout(composite3Layout);
			composite3Layout.marginWidth = 0;
			composite3Layout.marginHeight = 0;
			composite3Layout.spacing = 0;
			composite3.layout();
			GridLayout dialogShellLayout = new GridLayout(1, true);
			dialogShell.setLayout(dialogShellLayout);
			dialogShellLayout.marginWidth = 5;
			dialogShellLayout.marginHeight = 5;
			dialogShellLayout.numColumns = 1;
			dialogShellLayout.makeColumnsEqualWidth = true;
			dialogShellLayout.horizontalSpacing = 5;
			dialogShellLayout.verticalSpacing = 5;
			dialogShell.layout();
			dialogShell.addDisposeListener(new DisposeListener() {
				public void widgetDisposed(DisposeEvent e) {
					 
					label1font.dispose();
					idlBtnfont.dispose();
					//repositoryIDTxtfont.dispose();
					removePfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 407,280);
			dialogShell.setSize(bounds.width, bounds.height);
			postInitGUI();
			dialogShell.open();
			Display display = dialogShell.getDisplay();
			while (!dialogShell.isDisposed()) {
				if (!display.readAndDispatch())
					display.sleep();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Add your pre-init code in here 	*/
	public void preInitGUI(){
	}

	/** Add your post-init code in here 	*/
	public void postInitGUI(){
	   
	    Iterator it=compFileList.iterator();
	    while(it.hasNext()){
	        AssemblyConnection parameter=(AssemblyConnection) it.next();
	        par.add(parameter.getIdentifier());
	    }
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        editP.setEnabled(false);
	    }else{
	        par.select(0);
	    }
	   
	   
	}

	/** Auto-generated main method */
	public static void main(String[] args){
		showGUI();
	}

	/**
	* This static method creates a new instance of this class and shows
	* it inside a new Shell.
	*
	* It is a convenience method for showing the GUI, but it can be
	* copied and used as a basis for your own code.	*
	* It is auto-generated code - the body of this method will be
	* re-generated after any changes are made to the GUI.
	* However, if you delete this method it will not be re-created.	*/
	public static void showGUI(){
		try {
			Display display = Display.getDefault();
			Shell shell = new Shell(display);
			EditConnectionDialog inst = new EditConnectionDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    
	    state=true;
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
		dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void addPMouseDown(MouseEvent evt){
	    addParameter();
	}
	
	private void addParameter(){
		EditConnectionDialog2 d=new EditConnectionDialog2(this.dialogShell, 0);
		// d=new CreateComponentFileDialog(this.dialogShell,0);
	    d.setAssembly(this.ass);
	   // d.setIdlTList(idlTList);
	    d.open();
	    if(!d.isState())
	    	return;
	    //field=d.getField();
	    AssemblyConnection aConnection=d.getConnection();
	    for (Iterator it=compFileList.iterator();it.hasNext();){
	    	 AssemblyConnection con= (AssemblyConnection)it.next();
	    	 if(connectionDiff(con,aConnection)){
	    	 	MessageDialog.openError(parent, "Error",  " a Connection  is already exist " ); 
	    	 	return;
	    	 }
	    }
	    
	    compFileList.add(aConnection);
	    par.add(aConnection.getIdentifier());
	    if(par.getItemCount()>0){
	        removeP.setEnabled(true);
	        editP.setEnabled(true);
	    }
	    
	}
	
	/**
	 * @param con
	 * @param connection
	 * @return
	 */
	private boolean connectionDiff(AssemblyConnection con, AssemblyConnection connection) {
		 if(   con.getSource().getInstance().equals(connection.getSource().getInstance())
		 	&& con.getTarget().getInstance().equals(connection.getTarget().getInstance())
		 	&& con.getSource().getFeature().equals(connection.getSource().getFeature())
		 	&& con.getTarget().getFeature().equals(connection.getTarget().getFeature()))
		 	return true;
		return false;
	}

	/** Auto-generated event handler method */
	protected void editPMouseDown(MouseEvent evt){
	    editParameter();
	}
	
	private void editParameter(){
		 int index=par.getSelectionIndex();
		    if(index==-1)return;
		    AssemblyConnection aConnection=(AssemblyConnection) compFileList.get(index);
		    
		    AssemblyConnection originalcon=factory.createAssemblyConnection();
		    originalcon.setIdentifier(aConnection.getIdentifier());
		    originalcon.setVersion(aConnection.getVersion());
            originalcon.setRepositoryId(aConnection.getRepositoryId());
    	    ConnectionEnd targetEnd=factory.createConnectionEnd();
    	 	ConnectionEnd sourceEnd=factory.createConnectionEnd();
    	 	targetEnd.setInstance(aConnection.getTarget().getInstance());
    	    targetEnd.setFeature(aConnection.getTarget().getFeature());
    	    sourceEnd.setInstance(aConnection.getSource().getInstance());
    	    sourceEnd.setFeature(aConnection.getSource().getFeature());
    	    originalcon.getContents().add(targetEnd);
    	    originalcon.getContents().add(sourceEnd);
    	    originalcon.setSource(sourceEnd);
    	    originalcon.setTarget(targetEnd);
    	    originalcon.setDefinedIn(ass);
    	    originalcon.setConfig(ass.getConfig());
    	    
		    EditConnectionDialog2 d=new EditConnectionDialog2(this.dialogShell, 0);
			// d=new CreateComponentFileDialog(this.dialogShell,0);
		    d.setAssembly(this.ass);
		    d.setIdentifier(aConnection.getIdentifier());
		    d.setRepositoryID(aConnection.getRepositoryId());
		    d.setVersion(aConnection.getVersion());
		    d.setConnection(aConnection);
		    
			
			// d=new CreateComponentFileDialog(this.dialogShell,0);
		    //d.setPackages(this.pkgs);
		   // d.setIdlTList(idlTList);
		    d.open();
		    if(!d.isState())
		    	return;
		    //field=d.getField();
		  // aConnection aConnection=factory.createRule();
		    if(d.getConnection()!=null){	
		    aConnection=d.getConnection();
		    for (int i =0;i<compFileList.size();i++){
		    	
		    if(i!=index){
		    	AssemblyConnection con= (AssemblyConnection)compFileList.get(i);
		    	if(connectionDiff(con,aConnection)){
			    	compFileList.set(index,originalcon);
			    	par.setItem(index,originalcon.getIdentifier());
			    	MessageDialog.openError(parent, "Error",  " a Connection  is already exist " ); 
			    	return;
			    }
			 }
		    }
		    	compFileList.set(index,aConnection);
		    	par.setItem(index,aConnection.getIdentifier());
		    }
		}

	/** Auto-generated event handler method */
	protected void removePMouseDown(MouseEvent evt){
	    deleteParameter();
	}
	
	private void deleteParameter(){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    compFileList.remove(index);
	    par.remove(index);
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        editP.setEnabled(false);
	    }
	}
 
    
    /**
     * @return Returns the list.
     */
    public java.util.List getPameterList() {
        return compFileList;
    }
    /**
     * @param list The list to set.
     */
    public void setPameterList(java.util.List list) {
        this.compFileList.clear();
        this.compFileList.addAll(list);
    }
    /**
     * @return Returns the state.
     */
    public boolean isState() {
        return state;
    }
    /**
     * @param state The state to set.
     */
    public void setState(boolean state) {
        this.state = state;
    }
    /**
     * @param idlTList The idlTList to set.
     */
    

    /**
     * @param repositoryId The repositoryId to set.
     */
    public void setRepositoryId(String absName,String id,String version) {
        this.absName=absName;
        this.repositoryId = CCMConstants.getRepositoryIdString(absName,id,version);
    }
    /**
     * @return Returns the version.
     */

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			 state=true;
			    dialogShell.close();
		}
		
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyReleased(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
    

	public void setAssembly(Assembly ass) {
		this.ass=ass;
	}
}
 
 
 
