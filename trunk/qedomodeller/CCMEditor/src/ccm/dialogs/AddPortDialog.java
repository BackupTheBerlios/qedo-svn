package ccm.dialogs;


import java.util.Iterator;
import java.util.LinkedList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
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
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import ccm.CCMConstants;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* *************************************
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED
* for this machine, so Jigloo or this code cannot be used legally
* for any corporate or commercial purpose.
* *************************************
*/
public class AddPortDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Text versionTxt;
	private Label versionLb;
	private Text repositoryIDTxt;
	private Label repositoryIDLb;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	 
	private Text nameTxt;
	private Label nameLb;
	private Composite composite2;
	 
	private Shell dialogShell; 
	
	private boolean state=false;
	private String identifier="";
	private String repositoryId="";
	private String version="";
	private String context="";
	private java.util.List pameterList=new LinkedList();
	private java.util.List idlTList=new LinkedList();
	private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
	private String absName="";
	
	public AddPortDialog(Shell parent, int style, String text) {
		super(parent, style);
		setText(text);
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
			versionTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIDTxt = new Text(composite2,SWT.BORDER);
			repositoryIDLb = new Label(composite2,SWT.NULL);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText(getText());
			dialogShell.setSize(407, 140);

			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
	 
	
			GridData composite2LData = new GridData();
			composite2LData.widthHint = 392;
			composite2LData.heightHint = 96;
			composite2.setLayoutData(composite2LData);

			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 278;
			versionTxtLData.left =  new FormAttachment( 267, 1000, 0);
			versionTxtLData.right =  new FormAttachment(976, 1000, 0);
			versionTxtLData.top =  new FormAttachment(510, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(720, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);

			FormData versionLbLData = new FormData();
			versionLbLData.height = 17;
			versionLbLData.width = 89;
			versionLbLData.left =  new FormAttachment(11, 1000, 0);
			versionLbLData.right =  new FormAttachment(266, 1000, 0);
			versionLbLData.top =  new FormAttachment(500, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(682, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setFont(idlBtnfont);
	
			FormData repositoryIDTxtLData = new FormData();
			repositoryIDTxtLData.height = 13;
			repositoryIDTxtLData.width = 277;
			repositoryIDTxtLData.left =  new FormAttachment(267, 1000, 0);
			repositoryIDTxtLData.right =  new FormAttachment(976, 1000, 0);
			repositoryIDTxtLData.top =  new FormAttachment(275, 1000, 0);
			repositoryIDTxtLData.bottom =  new FormAttachment(485, 1000, 0);
			repositoryIDTxt.setLayoutData(repositoryIDTxtLData);
			repositoryIDTxt.setDoubleClickEnabled(false);
			final Font repositoryIDTxtfont =new Font(Display.getDefault(),"Tahoma",7,0);
			repositoryIDTxt.setFont(repositoryIDTxtfont);
			repositoryIDTxt.setEditable(false);
			repositoryIDTxt.setEnabled(false);
	
			FormData repositoryIDLbLData = new FormData();
			repositoryIDLbLData.height = 19;
			repositoryIDLbLData.width = 86;
			repositoryIDLbLData.left =  new FormAttachment(11, 1000, 0);
			repositoryIDLbLData.right =  new FormAttachment(266, 1000, 0);
			repositoryIDLbLData.top =  new FormAttachment(294, 1000, 0);
			repositoryIDLbLData.bottom =  new FormAttachment(484, 1000, 0);
			repositoryIDLb.setLayoutData(repositoryIDLbLData);
			repositoryIDLb.setText("Repository Id:");
			repositoryIDLb.setFont(idlBtnfont);

			final Font removePfont = new Font(Display.getDefault(),"Arial",8,1);

			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 277;
			nameTxtLData.left =  new FormAttachment(267, 1000, 0);
			nameTxtLData.right =  new FormAttachment(976, 1000, 0);
			nameTxtLData.top =  new FormAttachment(48, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(256, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(repositoryIDTxtfont);
			nameTxt.setFocus();
			nameTxt.addKeyListener( new KeyAdapter() {
				public void keyPressed(KeyEvent evt) {
					nameTxtKeyPressed(evt);
				}
			});
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 17;
			nameLbLData.width = 90;
			nameLbLData.left =  new FormAttachment(11, 1000, 0);
			nameLbLData.right =  new FormAttachment(266, 1000, 0);
			nameLbLData.top =  new FormAttachment(70, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(216, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Identifier:");
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
			cancelLData.height = 21;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(795, 1000, 0);
			cancelLData.right =  new FormAttachment(990, 1000, 0);
			cancelLData.top =  new FormAttachment(1, 1000, 0);
			cancelLData.bottom =  new FormAttachment(647, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(77,21));
			cancel.setFont(idlBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseUp(MouseEvent evt) {
					cancelMouseUp(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 21;
			enterLData.width = 77;
			enterLData.left =  new FormAttachment(545, 1000, 0);
			enterLData.right =  new FormAttachment(745, 1000, 0);
			enterLData.top =  new FormAttachment(1, 1000, 0);
			enterLData.bottom =  new FormAttachment(647, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(77,21));
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
					 
					idlBtnfont.dispose();
					repositoryIDTxtfont.dispose();
					removePfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 400,140);
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
	    Iterator it=pameterList.iterator();
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
			AddPortDialog inst = new AddPortDialog(shell, SWT.NULL, "");
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=nameTxt.getText();
	    version=versionTxt.getText();
	    state=true;
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
		dialogShell.close();
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
    public void setIdlTList(java.util.List idlTList) {
        this.idlTList.clear();
        this.idlTList.addAll(idlTList);
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
	protected void nameTxtKeyPressed(KeyEvent evt){
	    identifier=nameTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIDTxt.setText(repositoryId);
	}

	/** Auto-generated event handler method */
	protected void idlBtnMouseDown(MouseEvent evt){
	    SetOIDLTypeDialog d=new SetOIDLTypeDialog(this.dialogShell,0);
	    d.setIdlTemp(idlTemp);
	    d.open();
	    if(!d.isState())return;
	    if(idlTemp.getIdlKind().getValue()!=IDLKind.IDL){
	    }
	    idlTemp=d.getIdlTemp();
	}

	/** Auto-generated event handler method */
	protected void idlTypeCmbWidgetSelected(SelectionEvent evt){
	    if(idlTemp.getIdlKind().getValue()!=IDLKind.IDL){
	    }
	    idlTemp.setIdlKind(IDLKind.IDL_LITERAL);
	}
    /**
     * @return Returns the idlTemp.
     */
    public IDLTemplate getIdlTemp() {
        return idlTemp;
    }
    /**
     * @param idlTemp The idlTemp to set.
     */
    public void setIdlTemp(IDLTemplate idlTemp) {
        this.idlTemp = idlTemp;
    }

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
	
		identifier=nameTxt.getText();
	    version=versionTxt.getText();
	    state=true;
	    dialogShell.close();}
		
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyReleased(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
}
