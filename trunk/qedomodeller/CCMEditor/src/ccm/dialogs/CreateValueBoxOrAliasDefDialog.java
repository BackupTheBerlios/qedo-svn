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
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.SWT;

import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

import ccm.CCMConstants;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class CreateValueBoxOrAliasDefDialog extends org.eclipse.swt.widgets.Dialog  implements KeyListener{
	private Button idlBtn;
	private Combo idlTypeCmb;
	private Label idlTypeLb;
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
	private Composite composite2;
	 
	
	private String identifier="";
	private String repositoryId="";
	private String version="";
	private boolean state=false;
	private String discription;
	private java.util.List idlTList=new LinkedList();
	//private int idlTypeNumber=-1;
	private IDLTemplate idlTemplate;
    private String absName;
    private String text;
	

	public CreateValueBoxOrAliasDefDialog(Shell parent, int style,  String text) {
		super(parent, style);
		this.text=text;
	}

	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=identifierTxt.getText();
	    version=versionTxt.getText();
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
			idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
			idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
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
	
			dialogShell.setText(text);
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(476,150));
	 
		//	final Color composite1background = new Color(Display.getDefault(),255,255,255);
			 
			//final Font discLbfont = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
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
	
			FormData idlBtnLData = new FormData();
			idlBtnLData.height = 21;
			idlBtnLData.width = 32;
			idlBtnLData.left =  new FormAttachment(927, 1000, 0);
			idlBtnLData.right =  new FormAttachment(996, 1000, 0);
			idlBtnLData.top =  new FormAttachment(700, 1000, 0);
			idlBtnLData.bottom =  new FormAttachment(926, 1000, 0);
			idlBtn.setLayoutData(idlBtnLData);
			idlBtn.setText("....");
			idlBtn.setSize(new org.eclipse.swt.graphics.Point(32,21));
		    final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			idlBtn.setFont(idlBtnfont);
			idlBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					idlBtnMouseDown(evt);
				}
			});
	
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 27;
			idlTypeCmbLData.width = 310;
			idlTypeCmbLData.left =  new FormAttachment(240, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(923, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(700, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(936, 1000, 0);
			idlTypeCmb.setLayoutData(idlTypeCmbLData);
			idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(310,27));
			final Font idlTypeCmbfont = new Font(Display.getDefault(),"Tahoma",7,0);
			idlTypeCmb.setFont(idlTypeCmbfont);
			idlTypeCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					idlTypeCmbWidgetSelected(evt);
				}
			});
	
			FormData idlTypeLbLData = new FormData();
			idlTypeLbLData.height = 20;
			idlTypeLbLData.width = 60;
			idlTypeLbLData.left =  new FormAttachment(11, 1000, 0);
			idlTypeLbLData.right =  new FormAttachment(141, 1000, 0);
			idlTypeLbLData.top =  new FormAttachment(720, 1000, 0);
			idlTypeLbLData.bottom =  new FormAttachment(916, 1000, 0);
			idlTypeLb.setLayoutData(idlTypeLbLData);
			idlTypeLb.setText("Idl Type:");
			idlTypeLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			idlTypeLb.setFont(idlBtnfont);
	
			FormData repositoryIdTxtLData = new FormData();
			repositoryIdTxtLData.height = 13;
			repositoryIdTxtLData.width = 352;
			repositoryIdTxtLData.left =  new FormAttachment(240, 1000, 0);
			repositoryIdTxtLData.right =  new FormAttachment(996, 1000, 0);
			repositoryIdTxtLData.top =  new FormAttachment(269, 1000, 0);
			repositoryIdTxtLData.bottom =  new FormAttachment(465, 1000, 0);
			repositoryIdTxt.setLayoutData(repositoryIdTxtLData);
			repositoryIdTxt.setDoubleClickEnabled(false);
			repositoryIdTxt.setFont(idlTypeCmbfont);
			repositoryIdTxt.setEditable(false);
			repositoryIdTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			repositoryIdTxt.setEnabled(false);
	
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 352;
			versionTxtLData.left =  new FormAttachment(240, 1000, 0);
			versionTxtLData.right =  new FormAttachment(996, 1000, 0);
			versionTxtLData.top =  new FormAttachment(485, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(681, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setFont(idlTypeCmbfont);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			versionTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					versionTxtKeyReleased(evt);
				}
			});
	
			FormData identifierTxtLData = new FormData();
			identifierTxtLData.height = 13;
			identifierTxtLData.width = 352;
			identifierTxtLData.left =  new FormAttachment(240, 1000, 0);
			identifierTxtLData.right =  new FormAttachment(996, 1000, 0);
			identifierTxtLData.top =  new FormAttachment(53, 1000, 0);
			identifierTxtLData.bottom =  new FormAttachment(250, 1000, 0);
			identifierTxt.setLayoutData(identifierTxtLData);
			identifierTxt.setFont(idlTypeCmbfont);
			identifierTxt.setFocus();
			identifierTxt.setSize(new org.eclipse.swt.graphics.Point(352,13));
			identifierTxt.addKeyListener( new KeyAdapter() {
				public void keyReleased(KeyEvent evt) {
					identifierTxtKeyReleased(evt);
				}
			});
	
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 90;
			versionLbLData.left =  new FormAttachment(11, 1000, 0);
			versionLbLData.right =  new FormAttachment(230, 1000, 0);
			versionLbLData.top =  new FormAttachment(485, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(681, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			versionLb.setFont(idlBtnfont);
	
			FormData repositoryIdLbLData = new FormData();
			repositoryIdLbLData.height = 20;
			repositoryIdLbLData.width = 90;
			repositoryIdLbLData.left =  new FormAttachment(11, 1000, 0);
			repositoryIdLbLData.right =  new FormAttachment(230, 1000, 0);
			repositoryIdLbLData.top =  new FormAttachment(269, 1000, 0);
			repositoryIdLbLData.bottom =  new FormAttachment(465, 1000, 0);
			repositoryIdLb.setLayoutData(repositoryIdLbLData);
			repositoryIdLb.setText("Repository ID:");
			repositoryIdLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIdLb.setFont(idlBtnfont);
	
			FormData idLbLData = new FormData();
			idLbLData.height = 20;
			idLbLData.width = 90;
			idLbLData.left =  new FormAttachment(11, 1000, 0);
			idLbLData.right =  new FormAttachment(230, 1000, 0);
			idLbLData.top =  new FormAttachment(53, 1000, 0);
			idLbLData.bottom =  new FormAttachment(250, 1000, 0);
			idLb.setLayoutData(idLbLData);
			idLb.setText("Identifier:");
			idLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
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
			cancelLData.height = 25;
			cancelLData.width = 80;
			cancelLData.left =  new FormAttachment(816, 1000, 0);
			cancelLData.right =  new FormAttachment(988, 1000, 0);
			cancelLData.top =  new FormAttachment(6, 1000, 0);
			cancelLData.bottom =  new FormAttachment(580, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(80,25));
			cancel.setFont(idlBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 25;
			enterLData.width = 80;
			enterLData.left =  new FormAttachment(623, 1000, 0);
			enterLData.right =  new FormAttachment(795, 1000, 0);
			enterLData.top =  new FormAttachment(6, 1000, 0);
			enterLData.bottom =  new FormAttachment(580, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(80,25));
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
					 
					//discLbfont.dispose();
					idlBtnfont.dispose();
					idlTypeCmbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 476,150);
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
//	    discLb.setText(discription);
 //		dialogShell.setText(discription);
	    Iterator it=idlTList.iterator();
	    while(it.hasNext()){
	        String idl=(String) it.next();
	        idlTypeCmb.add(idl.toString());
	    }
	    idlTypeCmb.select(0);
	    setIDL();
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
			CreateValueBoxOrAliasDefDialog inst = new CreateValueBoxOrAliasDefDialog(shell, SWT.NULL,"");
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
    public void setDiscription(String discription) {
        this.discription = discription;
    }
    
    /**
     * @param idlTList The idlTList to set.
     */
    public void setIdlTList(java.util.List idlTList) {
        this.idlTList.clear();
        this.idlTList.addAll(idlTList);
    }
    
    /**
     * @return Returns the idlTemplate.
     */
    public IDLTemplate getIdlTemplate() {
        return idlTemplate;
    }
    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }

	/** Auto-generated event handler method */
	protected void idlTypeCmbWidgetSelected(SelectionEvent evt){
	    if(idlTemplate.getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    idlTemplate.setIdlKind(IDLKind.IDL_LITERAL);
	    idlTemplate.setIndexOfIDLType(idlTypeCmb.getSelectionIndex());
	}

	/** Auto-generated event handler method */
	protected void idlBtnMouseDown(MouseEvent evt){
	    SetOIDLTypeDialog d=new SetOIDLTypeDialog(this.dialogShell,0);
	    d.setIdlTemp(idlTemplate);
	    d.open();
	    if(!d.isState())return;
	    if(idlTemplate.getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    idlTemplate=d.getIdlTemp();
	    setIDL();
	}
	
	private void setIDL(){
	    switch(idlTemplate.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	        idlTypeCmb.add("wstring["+idlTemplate.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
	    	break;
	    case IDLKind.ARRAY:
	        idlTypeCmb.add("array["+idlTemplate.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.SEQUENCE:
	        idlTypeCmb.add("sequence["+idlTemplate.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.STRING:
	        idlTypeCmb.add("string["+idlTemplate.getBound()+"]");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
	    case IDLKind.FIXED:
	        idlTypeCmb.add("fixed(digits="+idlTemplate.getDigits()+", scale="+idlTemplate.getScale()+")");
	    	idlTypeCmb.select(idlTypeCmb.getItemCount()-1);
    		break;
    	case IDLKind.IDL:
    	    idlTypeCmb.select(idlTemplate.getIndexOfIDLType());
	    }	    
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
