package ccm.dialogs;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
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
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import ccm.CCMConstants;


/**
*@author Siegercn
*/
public class CreateComponentInstanceDialog extends org.eclipse.swt.widgets.Dialog {
	 
	private Text constValueTxt;
	private Label constValueLb;
	private Shell dialogShell;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Label idLb;
	private Label repositoryIdLb;
	private Label versionLb;
	private Text identifierTxt;
	private Text versionTxt;
	private Text repositoryIdTxt;
	private Label idlTypeLb;
	private Text cardinalityString;
	private Composite composite2;
    private int cardinality=0;
    private int startOder=0;
	private String identifier="";
	private String repositoryId="";
	private String version="";
	private boolean state=false;
	private String constValue="";
    private String absName="";
    private Shell parent ;
	
	public CreateComponentInstanceDialog(Shell parent, int style) {
		super(parent, style);
		this.parent=parent;
	}

	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=identifierTxt.getText();
	    version=versionTxt.getText();
	    constValue=constValueTxt.getText();
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
			 
			composite2 = new Composite(dialogShell,SWT.NULL);
			//idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
			constValueTxt = new Text(composite2,SWT.BORDER);
			constValueLb = new Label(composite2,SWT.NULL);
			cardinalityString =new Text(composite2,SWT.BORDER);
		//	idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
			idlTypeLb = new Label(composite2,SWT.NULL);
			repositoryIdTxt = new Text(composite2,SWT.BORDER);
			versionTxt = new Text(composite2,SWT.BORDER);
			identifierTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIdLb = new Label(composite2,SWT.NULL);
			idLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Add ComponentInstance");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(476,180));
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 464;
			composite2LData.heightHint = 136;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(464,136));
	
			 
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			 
	
			FormData constValueTxtLData = new FormData();
			constValueTxtLData.height = 13;
			constValueTxtLData.width = 342;
			constValueTxtLData.left =  new FormAttachment(252, 1000, 0);
			constValueTxtLData.right =  new FormAttachment(996, 1000, 0);
			constValueTxtLData.top =  new FormAttachment(525, 1000, 0);
			constValueTxtLData.bottom =  new FormAttachment(672, 1000, 0);
			constValueTxt.setLayoutData(constValueTxtLData);
			final Font constValueTxtfont = new Font(Display.getDefault(),"Tahoma",7,0);
			constValueTxt.setFont(constValueTxtfont);
			constValueTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
			constValueTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					constValueTxtKeyReleased(evt);
				}
			});
	
			FormData constValueLbLData = new FormData();
			constValueLbLData.height = 20;
			constValueLbLData.width = 100;
			constValueLbLData.left =  new FormAttachment(11, 1000, 0);
			constValueLbLData.right =  new FormAttachment(248, 1000, 0);
			constValueLbLData.top =  new FormAttachment(538, 1000, 0);
			constValueLbLData.bottom =  new FormAttachment(672, 1000, 0);
			constValueLb.setLayoutData(constValueLbLData);
			constValueLb.setText("StartOder:");
			constValueLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
			constValueLb.setFont(idlBtnfont);
	
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 27;
			idlTypeCmbLData.width = 306;
			idlTypeCmbLData.left =  new FormAttachment(252, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(996, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(702, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(878, 1000, 0);
			cardinalityString.setLayoutData(idlTypeCmbLData);
			cardinalityString.setSize(new org.eclipse.swt.graphics.Point(306,27));
			cardinalityString.setFont(constValueTxtfont);
			cardinalityString.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					cardinalityTxtKeyReleased(evt);
				}
			});
	
			FormData idlTypeLbLData = new FormData();
			idlTypeLbLData.height = 27;
			idlTypeLbLData.width = 60;
			idlTypeLbLData.left =  new FormAttachment(11, 1000, 0);
			idlTypeLbLData.right =  new FormAttachment(141, 1000, 0);
			idlTypeLbLData.top =  new FormAttachment(730, 1000, 0);
			idlTypeLbLData.bottom =  new FormAttachment(916, 1000, 0);
			idlTypeLb.setLayoutData(idlTypeLbLData);
			idlTypeLb.setText("cardinality:");
			idlTypeLb.setSize(new org.eclipse.swt.graphics.Point(60,27));
			idlTypeLb.setFont(idlBtnfont);
	
			FormData repositoryIdTxtLData = new FormData();
			repositoryIdTxtLData.height = 13;
			repositoryIdTxtLData.width = 342;
			repositoryIdTxtLData.left =  new FormAttachment(252, 1000, 0);
			repositoryIdTxtLData.right =  new FormAttachment(996, 1000, 0);
			repositoryIdTxtLData.top =  new FormAttachment(202, 1000, 0);
			repositoryIdTxtLData.bottom =  new FormAttachment(349, 1000, 0);
			repositoryIdTxt.setLayoutData(repositoryIdTxtLData);
			repositoryIdTxt.setDoubleClickEnabled(false);
			repositoryIdTxt.setFont(constValueTxtfont);
			repositoryIdTxt.setEditable(false);
			repositoryIdTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
			repositoryIdTxt.setEnabled(false);
	
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 342;
			versionTxtLData.left =  new FormAttachment(252, 1000, 0);
			versionTxtLData.right =  new FormAttachment(996, 1000, 0);
			versionTxtLData.top =  new FormAttachment(363, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(511, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setFont(constValueTxtfont);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
			versionTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					versionTxtKeyReleased(evt);
				}
			});
	
			FormData identifierTxtLData = new FormData();
			identifierTxtLData.height = 13;
			identifierTxtLData.width = 342;
			identifierTxtLData.left =  new FormAttachment(252, 1000, 0);
			identifierTxtLData.right =  new FormAttachment(996, 1000, 0);
			identifierTxtLData.top =  new FormAttachment(40, 1000, 0);
			identifierTxtLData.bottom =  new FormAttachment(187, 1000, 0);
			identifierTxt.setLayoutData(identifierTxtLData);
			identifierTxt.setFont(constValueTxtfont);
			identifierTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
			identifierTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					identifierTxtKeyReleased(evt);
				}
			});
	
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 100;
			versionLbLData.left =  new FormAttachment(11, 1000, 0);
			versionLbLData.right =  new FormAttachment(248, 1000, 0);
			versionLbLData.top =  new FormAttachment(373, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(511, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
			versionLb.setFont(idlBtnfont);
	
			FormData repositoryIdLbLData = new FormData();
			repositoryIdLbLData.height = 20;
			repositoryIdLbLData.width = 100;
			repositoryIdLbLData.left =  new FormAttachment(11, 1000, 0);
			repositoryIdLbLData.right =  new FormAttachment(248, 1000, 0);
			repositoryIdLbLData.top =  new FormAttachment(212, 1000, 0);
			repositoryIdLbLData.bottom =  new FormAttachment(349, 1000, 0);
			repositoryIdLb.setLayoutData(repositoryIdLbLData);
			repositoryIdLb.setText("Repository ID:");
			repositoryIdLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
			repositoryIdLb.setFont(idlBtnfont);
	
			FormData idLbLData = new FormData();
			idLbLData.height = 20;
			idLbLData.width = 100;
			idLbLData.left =  new FormAttachment(11, 1000, 0);
			idLbLData.right =  new FormAttachment(248, 1000, 0);
			idLbLData.top =  new FormAttachment(50, 1000, 0);
			idLbLData.bottom =  new FormAttachment(187, 1000, 0);
			idLb.setLayoutData(idLbLData);
			idLb.setText("Identifier:");
			idLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
			idLb.setFont(idlBtnfont);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 464;
			composite3LData.heightHint = 45;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(464,45));
	
			FormData cancelLData = new FormData();
			cancelLData.height = 24;
			cancelLData.width = 80;
			cancelLData.left =  new FormAttachment(816, 1000, 0);
			cancelLData.right =  new FormAttachment(988, 1000, 0);
			cancelLData.top =  new FormAttachment( 6, 1000, 0);
			cancelLData.bottom =  new FormAttachment(580, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(80,24));
			cancel.setFont(idlBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 24;
			enterLData.width = 79;
			enterLData.left =  new FormAttachment(623, 1000, 0);
			enterLData.right =  new FormAttachment(795, 1000, 0);
			enterLData.top =  new FormAttachment( 6, 1000, 0);
			enterLData.bottom =  new FormAttachment(580, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(79,24));
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
					constValueTxtfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 476,180);
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
	/**
	 * @param evt
	 */
	protected void constValueTxtKeyReleased(KeyEvent evt) {
		try{
			startOder= Integer.parseInt(constValueTxt.getText());
		}
		catch(NumberFormatException e){
			MessageDialog.openError(parent, "Error",  " the type of cardinality is Integer " ); }
		
		
	}

	/**
	 * @param evt
	 */
	protected void cardinalityTxtKeyReleased(KeyEvent evt) {
		try{
			cardinality= Integer.parseInt(cardinalityString.getText());
		}
		catch(NumberFormatException e){
			MessageDialog.openError(parent, "Error",  " the type of cardinality is Integer " ); }
		
	}

	/** Add your pre-init code in here 	*/
	public void preInitGUI(){
	}

	/** Add your post-init code in here 	*/
	public void postInitGUI(){
	    repositoryIdTxt.setText(repositoryId);
	    versionTxt.setText(version);
	    
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
			CreateConstantDefDialog inst = new CreateConstantDefDialog(shell, SWT.NULL);
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
    /**
     * @return Returns the state.
     */
    public boolean isState() {
        return state;
    }
    /**
     * @param discription The discription to set.
     */
    public int getStartOder() {
        return startOder;
    }
    public int getcardinality() {
        return cardinality;
    }
    
    /**
     * @param idlTList The idlTList to set.
     */
     

	/** Auto-generated event handler method */
	protected void versionTxtKeyReleased(KeyEvent evt){
	    version=versionTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIdTxt.setText(repositoryId);
	}

	/** Auto-generated event handler method */
	protected void identifierTxtKeyReleased(KeyEvent evt){
	    identifier=identifierTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIdTxt.setText(repositoryId);
	}

	 
    
}
 
