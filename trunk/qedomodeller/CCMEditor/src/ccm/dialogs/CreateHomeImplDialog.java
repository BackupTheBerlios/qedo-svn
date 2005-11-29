package ccm.dialogs;

import java.util.Iterator;
import java.util.LinkedList;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.SWT;

import org.eclipse.swt.widgets.Combo;

import CCMModel.ComponentCategory;
import CCMModel.HomeDef;
import ccm.CCMConstants;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.UnionFieldTemplate;

import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class CreateHomeImplDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	//private Button idlBtn;
	private Combo discTypeCmb;
	private Label discriminatorTypeLb;
	private Shell dialogShell;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Label nameLb;
	private Text nameTxt;
 
	 
	private Label repositoryIDLb;
	private Text repositoryIDTxt;
	private Label versionLb;
	private Text versionTxt;
	private Composite composite2;
	 
	
	private boolean state=false;
	private HomeDef home=null;
	private Object[] homes;
	private String identifier="";
	private String repositoryId="";
	private String version="";
	//private java.util.List memberList=new LinkedList();
	//private java.util.List idlTList=new LinkedList();
	//private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
    private String absName="";
	

	public CreateHomeImplDialog(Shell parent, int style) {
		super(parent, style);
	}

	 
	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=nameTxt.getText();
	    version=versionTxt.getText();

	   // setCategory(categorys[discTypeCmb.getSelectionIndex()]);
	    state=true;
	    dialogShell.close();
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
			 
			discTypeCmb = new Combo(composite2,SWT.NULL);
			discriminatorTypeLb = new Label(composite2,SWT.NULL);
			versionTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIDTxt = new Text(composite2,SWT.BORDER);
			repositoryIDLb = new Label(composite2,SWT.NULL);
			 
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Add HomeImpl");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(407,150));
	
			 
	
			 
			final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 400;
			composite2LData.heightHint = 110;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(400,110));
	
			 
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			 
	
			FormData discTypeCmbLData = new FormData();
			discTypeCmbLData.height = 27;
			discTypeCmbLData.width = 204;
			discTypeCmbLData.left =  new FormAttachment(266, 1000, 0);
			discTypeCmbLData.right =  new FormAttachment(993, 1000, 0);
			discTypeCmbLData.top =  new FormAttachment(680, 1000, 0);
			discTypeCmbLData.bottom =  new FormAttachment(880, 1000, 0);
			discTypeCmb.setLayoutData(discTypeCmbLData);
			discTypeCmb.setSize(new org.eclipse.swt.graphics.Point(204,27));
			final Font discTypeCmbfont = new Font(Display.getDefault(),"Tahoma",7,0);
			discTypeCmb.setFont(discTypeCmbfont);
			discTypeCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					discTypeCmbWidgetSelected(evt);
				}
			});
	
			FormData discriminatorTypeLbLData = new FormData();
			discriminatorTypeLbLData.height = 19;
			discriminatorTypeLbLData.width = 120;
			discriminatorTypeLbLData.left =  new FormAttachment(13, 1000, 0);
			discriminatorTypeLbLData.right =  new FormAttachment(260, 1000, 0);
			discriminatorTypeLbLData.top =  new FormAttachment(685, 1000, 0);
			discriminatorTypeLbLData.bottom =  new FormAttachment(880, 1000, 0);
			discriminatorTypeLb.setLayoutData(discriminatorTypeLbLData);
			discriminatorTypeLb.setText("HomeDef:");
			discriminatorTypeLb.setSize(new org.eclipse.swt.graphics.Point(120,19));
			discriminatorTypeLb.setEnabled(true);
			discriminatorTypeLb.setFont(idlBtnfont);
	
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 287;
			versionTxtLData.left =  new FormAttachment(266, 1000, 0);
			versionTxtLData.right =  new FormAttachment(993, 1000, 0);
			versionTxtLData.top =  new FormAttachment(460, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(660, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			versionTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					versionTxtKeyReleased(evt);
				}
			});
	
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 90;
			versionLbLData.left =  new FormAttachment(13, 1000, 0);
			versionLbLData.right =  new FormAttachment(260, 1000, 0);
			versionLbLData.top =  new FormAttachment(466, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(660, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			versionLb.setFont(idlBtnfont);
	
			FormData repositoryIDTxtLData = new FormData();
			repositoryIDTxtLData.height = 13;
			repositoryIDTxtLData.width = 287;
			repositoryIDTxtLData.left =  new FormAttachment(266, 1000, 0);
			repositoryIDTxtLData.right =  new FormAttachment(993, 1000, 0);
			repositoryIDTxtLData.top =  new FormAttachment(240, 1000, 0);
			repositoryIDTxtLData.bottom =  new FormAttachment(440, 1000, 0);
			repositoryIDTxt.setLayoutData(repositoryIDTxtLData);
			repositoryIDTxt.setDoubleClickEnabled(false);
			repositoryIDTxt.setFont(discTypeCmbfont);
			repositoryIDTxt.setEditable(false);
			repositoryIDTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			repositoryIDTxt.setEnabled(false);
	
			FormData repositoryIDLbLData = new FormData();
			repositoryIDLbLData.height = 20;
			repositoryIDLbLData.width = 90;
			repositoryIDLbLData.left =  new FormAttachment(13, 1000, 0);
			repositoryIDLbLData.right =  new FormAttachment(260, 1000, 0);
			repositoryIDLbLData.top =  new FormAttachment(245, 1000, 0);
			repositoryIDLbLData.bottom =  new FormAttachment(440, 1000, 0);
			repositoryIDLb.setLayoutData(repositoryIDLbLData);
			repositoryIDLb.setText("Repository Id:");
			repositoryIDLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIDLb.setFont(idlBtnfont);
	
			 
			 
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 287;
			nameTxtLData.left =  new FormAttachment(266, 1000, 0);
			nameTxtLData.right =  new FormAttachment(993, 1000, 0);
			nameTxtLData.top =  new FormAttachment(20, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(220, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(discTypeCmbfont);
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			nameTxt.setFocus();
			nameTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					nameTxtKeyReleased(evt);
				}
			});
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 20;
			nameLbLData.width = 90;
			nameLbLData.left =  new FormAttachment(13, 1000, 0);
			nameLbLData.right =  new FormAttachment(260, 1000, 0);
			nameLbLData.top =  new FormAttachment(23, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(220, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Identifier:");
			nameLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			nameLb.setFont(idlBtnfont);
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
			composite3.setFont(idlBtnfont);
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(775, 1000, 0);
			cancelLData.right =  new FormAttachment(976, 1000, 0);
			cancelLData.top =  new FormAttachment( 2, 1000, 0);
			cancelLData.bottom =  new FormAttachment(647, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(77,23));
			cancel.setFont(idlBtnfont);
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
			enterLData.top =  new FormAttachment( 2, 1000, 0);
			enterLData.bottom =  new FormAttachment(647, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(77,23));
			enter.setFont(idlBtnfont);
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
					discTypeCmbfont.dispose();
					 
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 407,150);
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
	    nameTxt.setText(identifier);
	    repositoryIDTxt.setText(repositoryId);
	    versionTxt.setText(version);
	    for(int i =0;i<homes.length;i++){
	    	discTypeCmb.add(((HomeDef)homes[i]).getIdentifier());
	    }
	    
	    
	    
 	  //  CCMConstants.setIDL(idlTemp,discTypeCmb);
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
			CreateCompositionDialog inst = new CreateCompositionDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	 /**
     * @return Returns the identifier.
     */
    public String getIdentifier() {
        return identifier;
    }
    /**
     * @param identifier The identifier to set.
     */
    public void setIdentifier(String identifier) {
        this.identifier = identifier;
    }
    /**
     * @return Returns the list.
     */
    public  HomeDef getHome() {
        return home;
    }
    /**
     * @param list The list to set.
     */
    public void setHome( HomeDef home) {
       
        this.home=home;
    }
    public void setHomes( java.util.List homesList) {
        
         this.homes=homesList.toArray();
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
     * @return Returns the repositoryId.
     */
    public String getRepositoryId() {
        return repositoryId;
    }
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
    public String getVersion() {
        return version;
    }
    /**
     * @param version The version to set.
     */
    public void setVersion(String version) {
        this.version = version;
    }

	 
    

	/** Auto-generated event handler method */
	protected void discTypeCmbWidgetSelected(SelectionEvent evt){
		
		setHome((HomeDef)homes[discTypeCmb.getSelectionIndex()]);
	}

	/** Auto-generated event handler method */
	protected void nameTxtKeyReleased(KeyEvent evt){
	    identifier=nameTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIDTxt.setText(repositoryId);
	}

	/** Auto-generated event handler method */
	protected void versionTxtKeyReleased(KeyEvent evt){
	    version=versionTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIDTxt.setText(repositoryId);
	}


	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
		identifier=nameTxt.getText();
	    version=versionTxt.getText();

	   // setCategory(categorys[discTypeCmb.getSelectionIndex()]);
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
}
 
 