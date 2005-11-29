package ccm.dialogs;

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
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.SWT;

import ccm.CCMConstants;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class CreateValueDefDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Button isTruncatableBtn;
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
	private Button isAbstractBtn;
	private Button isCustomBtn;
	private Composite composite2;
	 
	private String identifier="";
	private String repositoryId="";
	private String description="Add Value";
	private String version="";
	private boolean isAbstract=false;
	private boolean isCustom=false;
	private boolean isTruncat=false;
	private boolean state=false;
    private String absName;

	
	public CreateValueDefDialog(Shell parent, int style ) {
		super(parent, style);
		 
	}

	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=identifierTxt.getText();
	    version=versionTxt.getText();
	    isAbstract=isAbstractBtn.getSelection();
	    isCustom=isCustomBtn.getSelection();
	    isTruncat=isTruncatableBtn.getSelection();
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
			isTruncatableBtn = new Button(composite2,SWT.CHECK| SWT.LEFT);
			isCustomBtn = new Button(composite2,SWT.CHECK| SWT.LEFT);
			isAbstractBtn = new Button(composite2,SWT.CHECK| SWT.LEFT);
			repositoryIdTxt = new Text(composite2,SWT.BORDER);
			versionTxt = new Text(composite2,SWT.BORDER);
			identifierTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIdLb = new Label(composite2,SWT.NULL);
			idLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText(description);
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(476,146));
	
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			 
			final Font discLbfont = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 464;
			composite2LData.heightHint = 102;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(464,102));
	
			FormData isTruncatableBtnLData = new FormData();
			isTruncatableBtnLData.height = 20;
			isTruncatableBtnLData.width = 120;
			isTruncatableBtnLData.left =  new FormAttachment(465, 1000, 0);
			isTruncatableBtnLData.right =  new FormAttachment(998, 1000, 0);
			isTruncatableBtnLData.top =  new FormAttachment(716, 1000, 0);
			isTruncatableBtnLData.bottom =  new FormAttachment(840, 1000, 0);
			isTruncatableBtn.setLayoutData(isTruncatableBtnLData);
			isTruncatableBtn.setText("is truncatable");
			isTruncatableBtn.setSize(new org.eclipse.swt.graphics.Point(120,20));
			final Font isTruncatableBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			isTruncatableBtn.setFont(isTruncatableBtnfont);
	
			FormData isCustomBtnLData = new FormData();
			isCustomBtnLData.height = 20;
			isCustomBtnLData.width = 87;
			isCustomBtnLData.left =  new FormAttachment(230, 1000, 0);
			isCustomBtnLData.right =  new FormAttachment(435, 1000, 0);
			isCustomBtnLData.top =  new FormAttachment(880, 1000, 0);
			isCustomBtnLData.bottom =  new FormAttachment(1000, 1000, 0);
			isCustomBtn.setLayoutData(isCustomBtnLData);
			isCustomBtn.setText("is custom");
			isCustomBtn.setSize(new org.eclipse.swt.graphics.Point(87,20));
			isCustomBtn.setFont(isTruncatableBtnfont);
	
			FormData isAbstractBtnLData = new FormData();
			isAbstractBtnLData.height = 20;
			isAbstractBtnLData.width = 100;
			isAbstractBtnLData.left =  new FormAttachment(230, 1000, 0);
			isAbstractBtnLData.right =  new FormAttachment(435, 1000, 0);
			isAbstractBtnLData.top =  new FormAttachment(716, 1000, 0);
			isAbstractBtnLData.bottom =  new FormAttachment(840, 1000, 0);
			isAbstractBtn.setLayoutData(isAbstractBtnLData);
			isAbstractBtn.setText("is abstract");
			isAbstractBtn.setSize(new org.eclipse.swt.graphics.Point(100,20));
			isAbstractBtn.setFont(isTruncatableBtnfont);
	
			FormData repositoryIdTxtLData = new FormData();
			repositoryIdTxtLData.height = 13;
			repositoryIdTxtLData.width = 352;
			repositoryIdTxtLData.left =  new FormAttachment(230, 1000, 0);
			repositoryIdTxtLData.right =  new FormAttachment(996, 1000, 0);
			repositoryIdTxtLData.top =  new FormAttachment(269, 1000, 0);
			repositoryIdTxtLData.bottom =  new FormAttachment(465, 1000, 0);
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
			versionTxtLData.left =  new FormAttachment(230, 1000, 0);
			versionTxtLData.right =  new FormAttachment(996, 1000, 0);
			versionTxtLData.top =  new FormAttachment(485, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(681, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setFont(repositoryIdTxtfont);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			versionTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					versionTxtKeyReleased(evt);
				}
			});
	
			FormData identifierTxtLData = new FormData();
			identifierTxtLData.height = 13;
			identifierTxtLData.width = 352;
			identifierTxtLData.left =  new FormAttachment(230, 1000, 0);
			identifierTxtLData.right =  new FormAttachment(996, 1000, 0);
			identifierTxtLData.top =  new FormAttachment(53, 1000, 0);
			identifierTxtLData.bottom =  new FormAttachment(250, 1000, 0);
			identifierTxt.setLayoutData(identifierTxtLData);
			identifierTxt.setFont(repositoryIdTxtfont);
			identifierTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			identifierTxt.setFocus();
			identifierTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					identifierTxtKeyReleased(evt);
				}
			});
	
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 90;
			versionLbLData.left =  new FormAttachment(11, 1000, 0);
			versionLbLData.right =  new FormAttachment(225, 1000, 0);
			versionLbLData.top =  new FormAttachment(485, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(681, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			versionLb.setFont(isTruncatableBtnfont);
	
			FormData repositoryIdLbLData = new FormData();
			repositoryIdLbLData.height = 20;
			repositoryIdLbLData.width = 90;
			repositoryIdLbLData.left =  new FormAttachment(11, 1000, 0);
			repositoryIdLbLData.right =  new FormAttachment(225, 1000, 0);
			repositoryIdLbLData.top =  new FormAttachment(269, 1000, 0);
			repositoryIdLbLData.bottom =  new FormAttachment(465, 1000, 0);
			repositoryIdLb.setLayoutData(repositoryIdLbLData);
			repositoryIdLb.setText("Repository ID:");
			repositoryIdLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIdLb.setFont(isTruncatableBtnfont);
	
			FormData idLbLData = new FormData();
			idLbLData.height = 20;
			idLbLData.width = 90;
			idLbLData.left =  new FormAttachment(11, 1000, 0);
			idLbLData.right =  new FormAttachment(225, 1000, 0);
			idLbLData.top =  new FormAttachment(53, 1000, 0);
			idLbLData.bottom =  new FormAttachment(250, 1000, 0);
			idLb.setLayoutData(idLbLData);
			idLb.setText("Identifier:");
			idLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			idLb.setFont(isTruncatableBtnfont);
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
			cancelLData.height = 20;
			cancelLData.width = 80;
			cancelLData.left =  new FormAttachment(816, 1000, 0);
			cancelLData.right =  new FormAttachment(988, 1000, 0);
			cancelLData.top =  new FormAttachment( 6, 1000, 0);
			cancelLData.bottom =  new FormAttachment(540, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(80,20));
			cancel.setFont(isTruncatableBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 20;
			enterLData.width = 80;
			enterLData.left =  new FormAttachment(623, 1000, 0);
			enterLData.right =  new FormAttachment(795, 1000, 0);
			enterLData.top =  new FormAttachment( 6, 1000, 0);
			enterLData.bottom =  new FormAttachment(540, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(80,20));
			enter.setFont(isTruncatableBtnfont);
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
					composite1background.dispose();
					discLbfont.dispose();
					isTruncatableBtnfont.dispose();
					repositoryIdTxtfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 476,146);
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
	    repositoryIdTxt.setText(repositoryId);
	    versionTxt.setText(version);
		dialogShell.setText(description);
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
			CreateValueDefDialog inst = new CreateValueDefDialog(shell, SWT.NULL );
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
     * @return Returns the isAbstract.
     */
    public boolean isAbstract() {
        return isAbstract;
    }
    /**
     * @return Returns the isLocal.
     */
    public boolean isCustom() {
        return isCustom;
    }
    /**
     * @param discription The discription to set.
     */
    public boolean isTruncatable() {
        return isTruncat;
    }

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

	/**
	 * @param description The description to set.
	 */
	public void setDescription(String description) {
		this.description = description;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			identifier=identifierTxt.getText();
		    version=versionTxt.getText();
		    isAbstract=isAbstractBtn.getSelection();
		    isCustom=isCustomBtn.getSelection();
		    isTruncat=isTruncatableBtn.getSelection();
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
