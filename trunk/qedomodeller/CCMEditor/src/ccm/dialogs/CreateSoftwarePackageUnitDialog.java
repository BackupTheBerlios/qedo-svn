package ccm.dialogs;


import java.util.List;

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
 
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.SWT;

import CCMModel.ComponentDef;
import CCMModel.ModuleDef;

import ccm.CCMConstants;
/*
* @author Siegercn
*/
 
public class CreateSoftwarePackageUnitDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	//private Button isLocalBtn;
	//private Button isAbstractBtn;
	 
	private Button cancel;
	private Button enter;
	private Composite composite3;
	private Text repositoryIdTxt;
	private Text versionTxt;
	private Text identifierTxt;
	private Label versionLb;
	private Text licenseKeyTxt;
	private Label licenseKeyLb;
	private Text licenseTxtRefTxt;
	private Label licenseTxtRefLb;
	private Text titleTxt;
	private Label titleLb;
	private Text autorTxt;
	private Label autorLb;
	private Text typeTxt;
	private Label typeLb;
	
	private Combo copmCmb;
	private Label comLb;
	private Label baseLb;
	private Label localLb;
	private Label idlFileLb;
	private ComponentDef component=null;
	private ModuleDef module=null;
	private List componentDefList;
	
	private Label repositoryIdLb;
	private Label idLb;
	private Composite composite2;
	 
	private Shell dialogShell;

	private String identifier="";
	private String repositoryId="";
	private String version="";
	 
	private boolean state=false;
	private String discription="";
    private String absName;
	private String uuid="";
	private String licenseTxtRef;
	private String licenseKey;
	
	public CreateSoftwarePackageUnitDialog(Shell parent, int style) {
		super(parent, style);
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
		 
			repositoryIdTxt = new Text(composite2,SWT.BORDER);
			versionTxt = new Text(composite2,SWT.BORDER);
			identifierTxt = new Text(composite2,SWT.BORDER);
			titleTxt=new Text(composite2,SWT.BORDER);
			licenseKeyTxt = new Text(composite2,SWT.BORDER);
			licenseKeyLb=new Label(composite2,SWT.NULL);
			licenseTxtRefTxt = new Text(composite2,SWT.BORDER);
			licenseTxtRefLb=new Label(composite2,SWT.NULL);
			titleLb=new Label(composite2,SWT.NULL);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIdLb = new Label(composite2,SWT.NULL);
			idLb = new Label(composite2,SWT.NULL);
			autorTxt=new Text(composite2,SWT.BORDER);
			autorLb=new Label(composite2,SWT.NULL);
			typeTxt=new Text(composite2,SWT.BORDER);
			typeLb = new Label(composite2,SWT.NULL);
			
			copmCmb = new Combo(composite2,SWT.NULL);
			comLb = new Label(composite2,SWT.NULL);
			baseLb = new Label(composite2,SWT.NULL);
			localLb = new Label(composite2,SWT.NULL);
			idlFileLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Add SoftwarePackage");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(476,180));
	  
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 464;
			composite2LData.heightHint = 135;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(464,135));
	
			 
			final Font isLocalBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);

			FormData copmCmbLData = new FormData();
			copmCmbLData.height = 24;
			copmCmbLData.width = 214;
			copmCmbLData.left =  new FormAttachment(334, 1000, 0);
			copmCmbLData.right =  new FormAttachment(995, 1000, 0);
			copmCmbLData.top =  new FormAttachment(358, 1000, 0);
			copmCmbLData.bottom =  new FormAttachment(624, 1000, 0);
			copmCmb.setLayoutData(copmCmbLData);
			copmCmb.setSize(new org.eclipse.swt.graphics.Point(214,24));
			final Font copmCmbfont = new Font(Display.getDefault(),"Tahoma",7,0);
			copmCmb.setFont(copmCmbfont);
	
			FormData comLbLData = new FormData();
			comLbLData.height = 17;
			comLbLData.width = 96;
			comLbLData.left =  new FormAttachment(21, 1000, 0);
			comLbLData.right =  new FormAttachment(330, 1000, 0);
			comLbLData.top =  new FormAttachment(399, 1000, 0);
			comLbLData.bottom =  new FormAttachment(600, 1000, 0);
			comLb.setLayoutData(comLbLData);
			comLb.setText("ComponentEnd:");
			comLb.setSize(new org.eclipse.swt.graphics.Point(96,17));
			//final Font comLbfont = new Font(Display.getDefault(),"Tahoma",8,1);
			comLb.setFont(isLocalBtnfont);
	
			 
	
			FormData repositoryIdTxtLData = new FormData();
			repositoryIdTxtLData.height = 13;
			repositoryIdTxtLData.width = 352;
			repositoryIdTxtLData.left =  new FormAttachment(239, 1000, 0);
			repositoryIdTxtLData.right =  new FormAttachment(996, 1000, 0);
			repositoryIdTxtLData.top =  new FormAttachment(210, 1000, 0);
			repositoryIdTxtLData.bottom =  new FormAttachment(360, 1000, 0);
			repositoryIdTxt.setLayoutData(repositoryIdTxtLData);
			repositoryIdTxt.setDoubleClickEnabled(false);
			final Font repositoryIdTxtfont = new Font(Display.getDefault(),"Tahoma",7,0);
			repositoryIdTxt.setFont(repositoryIdTxtfont);
			repositoryIdTxt.setEditable(false);
			repositoryIdTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			repositoryIdTxt.setEnabled(false);
	
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 352;
			versionTxtLData.left =  new FormAttachment(239, 1000, 0);
			versionTxtLData.right =  new FormAttachment(996, 1000, 0);
			versionTxtLData.top =  new FormAttachment(370, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(520, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setFont(repositoryIdTxtfont);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			//versionTxt.setFocus();
			versionTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					versionTxtKeyReleased(evt);
				}
			});
			
			FormData uuidTxtLData = new FormData();
			uuidTxtLData.height = 13;
			uuidTxtLData.width = 352;
			uuidTxtLData.left =  new FormAttachment(239, 1000, 0);
			uuidTxtLData.right =  new FormAttachment(996, 1000, 0);
			uuidTxtLData.top =  new FormAttachment(530, 1000, 0);
			uuidTxtLData.bottom =  new FormAttachment(680, 1000, 0);
			titleTxt.setLayoutData(uuidTxtLData);
			titleTxt.setFont(repositoryIdTxtfont);
			titleTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			//versionTxt.setFocus();
			titleTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					uuidTxtKeyReleased(evt);
				}
			});
			
			FormData licenseKeyTxtData = new FormData();
			licenseKeyTxtData.height = 13;
			licenseKeyTxtData.width = 352;
			licenseKeyTxtData.left =  new FormAttachment(239, 1000, 0);
			licenseKeyTxtData.right =  new FormAttachment(996, 1000, 0);
			licenseKeyTxtData.top =  new FormAttachment(690, 1000, 0);
			licenseKeyTxtData.bottom =  new FormAttachment(840, 1000, 0);
			licenseKeyTxt.setLayoutData(licenseKeyTxtData);
			licenseKeyTxt.setFont(repositoryIdTxtfont);
			licenseKeyTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			//versionTxt.setFocus();
			titleTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					licenseKeyTxtKeyReleased(evt);
				}
			});
			
			FormData licenseTxtRefTxtData = new FormData();
			licenseTxtRefTxtData.height = 13;
			licenseTxtRefTxtData.width = 352;
			licenseTxtRefTxtData.left =  new FormAttachment(239, 1000, 0);
			licenseTxtRefTxtData.right =  new FormAttachment(996, 1000, 0);
			licenseTxtRefTxtData.top =  new FormAttachment(850, 1000, 0);
			licenseTxtRefTxtData.bottom =  new FormAttachment(1000, 1000, 0);
			licenseTxtRefTxt.setLayoutData(licenseTxtRefTxtData);
			licenseTxtRefTxt.setFont(repositoryIdTxtfont);
			licenseTxtRefTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			//versionTxt.setFocus();
			titleTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					licenseTxtRefTxtKeyReleased(evt);
				}
			});
			
			FormData identifierTxtLData = new FormData();
			identifierTxtLData.height = 13;
			identifierTxtLData.width = 352;
			identifierTxtLData.left =  new FormAttachment(239, 1000, 0);
			identifierTxtLData.right =  new FormAttachment(996, 1000, 0);
			identifierTxtLData.top =  new FormAttachment(50, 1000, 0);
			identifierTxtLData.bottom =  new FormAttachment(200, 1000, 0);
			identifierTxt.setLayoutData(identifierTxtLData);
			identifierTxt.setFont(repositoryIdTxtfont);
			identifierTxt.setFocus();
			identifierTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			identifierTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					identifierTxtKeyReleased(evt);
				}
			});
	
			FormData licenseKeyLbData = new FormData();
			licenseKeyLbData.height = 20;
			licenseKeyLbData.width = 90;
			licenseKeyLbData.left =  new FormAttachment(11, 1000, 0);
			licenseKeyLbData.right =  new FormAttachment(245, 1000, 0);
			licenseKeyLbData.top =  new FormAttachment(698, 1000, 0);
			licenseKeyLbData.bottom =  new FormAttachment(840, 1000, 0);
			licenseKeyLb.setLayoutData(licenseKeyLbData);
			licenseKeyLb.setText("license Key:");
			licenseKeyLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			licenseKeyLb.setFont(isLocalBtnfont);
			
			FormData uuidLbLData = new FormData();
			uuidLbLData.height = 20;
			uuidLbLData.width = 90;
			uuidLbLData.left =  new FormAttachment(11, 1000, 0);
			uuidLbLData.right =  new FormAttachment(245, 1000, 0);
			uuidLbLData.top =  new FormAttachment(538, 1000, 0);
			uuidLbLData.bottom =  new FormAttachment(690, 1000, 0);
			titleLb.setLayoutData(uuidLbLData);
			titleLb.setText("UUID:");
			titleLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			titleLb.setFont(isLocalBtnfont);
			
			FormData licenseTxtRefLbData = new FormData();
			licenseTxtRefLbData.height = 20;
			licenseTxtRefLbData.width = 90;
			licenseTxtRefLbData.left =  new FormAttachment(11, 1000, 0);
			licenseTxtRefLbData.right =  new FormAttachment(245, 1000, 0);
			licenseTxtRefLbData.top =  new FormAttachment(859, 1000, 0);
			licenseTxtRefLbData.bottom =  new FormAttachment(1000, 1000, 0);
			licenseTxtRefLb.setLayoutData(licenseTxtRefLbData);
			licenseTxtRefLb.setText("licenceTxtRef:");
			licenseTxtRefLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			licenseTxtRefLb.setFont(isLocalBtnfont);
			
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 90;
			versionLbLData.left =  new FormAttachment(11, 1000, 0);
			versionLbLData.right =  new FormAttachment(245, 1000, 0);
			versionLbLData.top =  new FormAttachment(380, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(520, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			versionLb.setFont(isLocalBtnfont);
	
			FormData repositoryIdLbLData = new FormData();
			repositoryIdLbLData.height = 20;
			repositoryIdLbLData.width = 90;
			repositoryIdLbLData.left =  new FormAttachment(11, 1000, 0);
			repositoryIdLbLData.right =  new FormAttachment(245, 1000, 0);
			repositoryIdLbLData.top =  new FormAttachment(220, 1000, 0);
			repositoryIdLbLData.bottom =  new FormAttachment(360, 1000, 0);
			repositoryIdLb.setLayoutData(repositoryIdLbLData);
			repositoryIdLb.setText("Repository ID:");
			repositoryIdLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIdLb.setFont(isLocalBtnfont);
	
			FormData idLbLData = new FormData();
			idLbLData.height = 20;
			idLbLData.width = 90;
			idLbLData.left =  new FormAttachment(11, 1000, 0);
			idLbLData.right =  new FormAttachment(245, 1000, 0);
			idLbLData.top =  new FormAttachment(59, 1000, 0);
			idLbLData.bottom =  new FormAttachment(200, 1000, 0);
			idLb.setLayoutData(idLbLData);
			idLb.setText("Identifier:");
			idLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			idLb.setFont(isLocalBtnfont);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 466;
			composite3LData.heightHint = 46;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(466,46));
	
			FormData cancelLData = new FormData();
			cancelLData.height = 21;
			cancelLData.width = 80;
			cancelLData.left =  new FormAttachment(840, 1000, 0);
			cancelLData.right =  new FormAttachment(990, 1000, 0);
			cancelLData.top =  new FormAttachment( 100, 1000, 0);
			cancelLData.bottom =  new FormAttachment(580, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(80,21));
			cancel.setFont(isLocalBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 21;
			enterLData.width = 80;
			enterLData.left =  new FormAttachment(623, 1000, 0);
			enterLData.right =  new FormAttachment(795, 1000, 0);
			enterLData.top =  new FormAttachment( 100, 1000, 0);
			enterLData.bottom =  new FormAttachment(580, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(80,21));
			enter.setFont(isLocalBtnfont);
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
					 
					isLocalBtnfont.dispose();
					repositoryIdTxtfont.dispose();
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
	protected void licenseTxtRefTxtKeyReleased(KeyEvent evt) {
		licenseTxtRef =licenseTxtRefTxt.getText();
		
	}

	/**
	 * @param evt
	 */
	protected void licenseKeyTxtKeyReleased(KeyEvent evt) {
		licenseKey=licenseKeyTxt.getText();
	}

	/**
	 * @param evt
	 */
	protected void uuidTxtKeyReleased(KeyEvent evt) {
		uuid=titleTxt.getText();
		
	}

	/** Add your pre-init code in here 	*/
	public void preInitGUI(){
	}

	/** Add your post-init code in here 	*/
	public void postInitGUI(){
	    repositoryIdTxt.setText(repositoryId);
	    versionTxt.setText(version);
	    
	    dialogShell.setText(discription);
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
			CreateSoftwarePackageUnitDialog inst = new CreateSoftwarePackageUnitDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=identifierTxt.getText();
	    version=versionTxt.getText();
	    state=true;
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
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
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
    public String getUUID() {
        return uuid;
    }
    public String getLicenseKey() {
        return licenseKey;
    }
    public String getLicenseTxtRef() {
        return licenseTxtRef;
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
    public void setDiscription(String discription) {
        this.discription = discription;
    }

	/** Auto-generated event handler method */
	protected void versionTxtKeyReleased(KeyEvent evt){
	    version=versionTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIdTxt.setText(repositoryId);
	}

	/** Auto-geenerated event handler method */
	protected void identifierTxtKeyReleased(KeyEvent evt){
	    identifier=identifierTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIdTxt.setText(repositoryId);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			 identifier=identifierTxt.getText();
			    version=versionTxt.getText();
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
 
