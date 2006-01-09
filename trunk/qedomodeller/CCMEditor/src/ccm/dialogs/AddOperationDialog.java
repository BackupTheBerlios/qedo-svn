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
import org.eclipse.swt.events.SelectionAdapter;
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
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import ccm.CCMConstants;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;

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
public class AddOperationDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Button idlBtn;
	private Text versionTxt;
	private Label versionLb;
	private Text repositoryIDTxt;
	private Label repositoryIDLb;
	private Combo idlTypeCmb;
	private Label label2;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Label label1;
	private Button removeP;
	private Button editP;
	private Button addP;
	private Label contextLb;
	private Text contextTxt;
	private Label parLb;
	private List par;
	private Text nameTxt;
	private Label nameLb;
	private Composite composite2;
	//private Composite composite1;
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
	
	public AddOperationDialog(Shell parent, int style) {
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
			 
			composite2 = new Composite(dialogShell,SWT.NO_RADIO_GROUP);
			idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
			versionTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIDTxt = new Text(composite2,SWT.BORDER);
			repositoryIDLb = new Label(composite2,SWT.NULL);
			idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
			label2 = new Label(composite2,SWT.NULL);
			removeP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			editP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			addP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			contextLb = new Label(composite2,SWT.NULL);
			contextTxt = new Text(composite2,SWT.V_SCROLL);
			parLb = new Label(composite2,SWT.NULL);
			par = new List(composite2,SWT.BORDER|SWT.V_SCROLL);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Add Operation");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(407,398));
	
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			 
	
		 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 400;
			composite2LData.heightHint = 339;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(400,339));
	
			FormData idlBtnLData = new FormData();
			idlBtnLData.height = 21;
			idlBtnLData.width = 28;
			idlBtnLData.left =  new FormAttachment(923, 1000, 0);
			idlBtnLData.right =  new FormAttachment(993, 1000, 0);
			idlBtnLData.top =  new FormAttachment(210, 1000, 0);
			idlBtnLData.bottom =  new FormAttachment(292, 1000, 0);
			idlBtn.setLayoutData(idlBtnLData);
			idlBtn.setText("....");
			idlBtn.setSize(new org.eclipse.swt.graphics.Point(28,21));
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			idlBtn.setFont(idlBtnfont);
			idlBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					idlBtnMouseDown(evt);
				}
			});
			final Font repositoryIDTxtfont = new Font(Display.getDefault(),"Tahoma",8,0);
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 287;
			versionTxtLData.left =  new FormAttachment(267, 1000, 0);
			versionTxtLData.right =  new FormAttachment(993, 1000, 0);
			versionTxtLData.top =  new FormAttachment(146, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(205, 1000, 0);
			versionTxt.setLayoutData(versionTxtLData);
			versionTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			versionTxt.setFont(repositoryIDTxtfont);
			FormData versionLbLData = new FormData();
			versionLbLData.height = 20;
			versionLbLData.width = 90;
			versionLbLData.left =  new FormAttachment(13, 1000, 0);
			versionLbLData.right =  new FormAttachment(261, 1000, 0);
			versionLbLData.top =  new FormAttachment(146, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(205, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			versionLb.setFont(idlBtnfont);
	
			FormData repositoryIDTxtLData = new FormData();
			repositoryIDTxtLData.height = 13;
			repositoryIDTxtLData.width = 287;
			repositoryIDTxtLData.left =  new FormAttachment(267, 1000, 0);
			repositoryIDTxtLData.right =  new FormAttachment(993, 1000, 0);
			repositoryIDTxtLData.top =  new FormAttachment(81, 1000, 0);
			repositoryIDTxtLData.bottom =  new FormAttachment(140, 1000, 0);
			repositoryIDTxt.setLayoutData(repositoryIDTxtLData);
			repositoryIDTxt.setDoubleClickEnabled(false);
			
			repositoryIDTxt.setFont(repositoryIDTxtfont);
			repositoryIDTxt.setEditable(false);
			repositoryIDTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			repositoryIDTxt.setEnabled(false);
	
			FormData repositoryIDLbLData = new FormData();
			repositoryIDLbLData.height = 20;
			repositoryIDLbLData.width = 90;
			repositoryIDLbLData.left =  new FormAttachment(13, 1000, 0);
			repositoryIDLbLData.right =  new FormAttachment(261, 1000, 0);
			repositoryIDLbLData.top =  new FormAttachment(81, 1000, 0);
			repositoryIDLbLData.bottom =  new FormAttachment(140, 1000, 0);
			repositoryIDLb.setLayoutData(repositoryIDLbLData);
			repositoryIDLb.setText("Repository Id:");
			repositoryIDLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIDLb.setFont(idlBtnfont);
	
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 20;
			idlTypeCmbLData.width = 249;
			idlTypeCmbLData.left =  new FormAttachment(267, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(918, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(210, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(270, 1000, 0);
			idlTypeCmb.setLayoutData(idlTypeCmbLData);
			idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(249,20));
			idlTypeCmb.setEnabled(true);
			idlTypeCmb.setFont(repositoryIDTxtfont);
			idlTypeCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					idlTypeCmbWidgetSelected(evt);
				}
			});
	
			FormData label2LData = new FormData();
			label2LData.height = 20;
			label2LData.width = 90;
			label2LData.left =  new FormAttachment(13, 1000, 0);
			label2LData.right =  new FormAttachment(261, 1000, 0);
			label2LData.top =  new FormAttachment(219, 1000, 0);
			label2LData.bottom =  new FormAttachment(278, 1000, 0);
			label2.setLayoutData(label2LData);
			label2.setText("Idl Type:");
			label2.setSize(new org.eclipse.swt.graphics.Point(90,20));
			label2.setFont(idlBtnfont);
	
			FormData removePLData = new FormData();
			removePLData.height = 20;
			removePLData.width = 70;
			removePLData.left =  new FormAttachment(816, 1000, 0);
			removePLData.right =  new FormAttachment(991, 1000, 0);
			removePLData.top =  new FormAttachment(924, 1000, 0);
			removePLData.bottom =  new FormAttachment(995, 1000, 0);
			removeP.setLayoutData(removePLData);
			removeP.setText("REMOVE");
			removeP.setSize(new org.eclipse.swt.graphics.Point(70,20));
			final Font removePfont = new Font(Display.getDefault(),"Tahoma",8,1);
			removeP.setFont(removePfont);
			removeP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					removePMouseDown(evt);
				}
			});
	
			FormData editPLData = new FormData();
			editPLData.height = 20;
			editPLData.width = 70;
			editPLData.left =  new FormAttachment(626, 1000, 0);
			editPLData.right =  new FormAttachment(801, 1000, 0);
			editPLData.top =  new FormAttachment(924, 1000, 0);
			editPLData.bottom =  new FormAttachment(995, 1000, 0);
			editP.setLayoutData(editPLData);
			editP.setText("EDIT");
			editP.setSize(new org.eclipse.swt.graphics.Point(70,20));
			editP.setFont(removePfont);
			editP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					editPMouseDown(evt);
				}
			});
	
			FormData addPLData = new FormData();
			addPLData.height = 20;
			addPLData.width = 70;
			addPLData.left =  new FormAttachment(438, 1000, 0);
			addPLData.right =  new FormAttachment(613, 1000, 0);
			addPLData.top =  new FormAttachment(924, 1000, 0);
			addPLData.bottom =  new FormAttachment(995, 1000, 0);
			addP.setLayoutData(addPLData);
			addP.setText("ADD");
			addP.setSize(new org.eclipse.swt.graphics.Point(70,20));
			addP.setFont(removePfont);
			addP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					addPMouseDown(evt);
				}
			});
	
			FormData contextLbLData = new FormData();
			contextLbLData.height = 20;
			contextLbLData.width = 90;
			contextLbLData.left =  new FormAttachment(13, 1000, 0);
			contextLbLData.right =  new FormAttachment(261, 1000, 0);
			contextLbLData.top =  new FormAttachment(325, 1000, 0);
			contextLbLData.bottom =  new FormAttachment(384, 1000, 0);
			contextLb.setLayoutData(contextLbLData);
			contextLb.setText("Context:");
			contextLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			contextLb.setFont(idlBtnfont);
	
			FormData contextTxtLData = new FormData();
			contextTxtLData.height = 198;
			contextTxtLData.width = 147;
			contextTxtLData.left =  new FormAttachment(13, 1000, 0);
			contextTxtLData.right =  new FormAttachment(413, 1000, 0);
			contextTxtLData.top =  new FormAttachment(390, 1000, 0);
			contextTxtLData.bottom =  new FormAttachment(995, 1000, 0);
			contextTxt.setLayoutData(contextTxtLData);
			contextTxt.setFont(repositoryIDTxtfont);
			contextTxt.setSize(new org.eclipse.swt.graphics.Point(147,198));
	
			FormData parLbLData = new FormData();
			parLbLData.height = 23;
			parLbLData.width = 208;
			parLbLData.left =  new FormAttachment(438, 1000, 0);
			parLbLData.right =  new FormAttachment(958, 1000, 0);
			parLbLData.top =  new FormAttachment(325, 1000, 0);
			parLbLData.bottom =  new FormAttachment(393, 1000, 0);
			parLb.setLayoutData(parLbLData);
			parLb.setText("Parameters:");
			parLb.setSize(new org.eclipse.swt.graphics.Point(208,23));
			parLb.setFont(idlBtnfont);
	
			FormData parLData = new FormData();
			parLData.height = 150;
			parLData.width = 213;
			parLData.left =  new FormAttachment(438, 1000, 0);
			parLData.right =  new FormAttachment(988, 1000, 0);
			parLData.top =  new FormAttachment(390, 1000, 0);
			parLData.bottom =  new FormAttachment(890, 1000, 0);
			par.setLayoutData(parLData);
			par.setFont(repositoryIDTxtfont);
			par.setSize(new org.eclipse.swt.graphics.Point(213,150));
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 287;
			nameTxtLData.left =  new FormAttachment(267, 1000, 0);
			nameTxtLData.right =  new FormAttachment(993, 1000, 0);
			nameTxtLData.top =  new FormAttachment(16, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(75, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(repositoryIDTxtfont);
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			nameTxt.setFocus();
			nameTxt.addKeyListener( new KeyAdapter() {
				public void keyPressed(KeyEvent evt) {
					nameTxtKeyPressed(evt);
				}
			});
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 20;
			nameLbLData.width = 90;
			nameLbLData.left =  new FormAttachment(13, 1000, 0);
			nameLbLData.right =  new FormAttachment(261, 1000, 0);
			nameLbLData.top =  new FormAttachment(13, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(72, 1000, 0);
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
			cancelLData.top =  new FormAttachment(262, 1000, 0);
			cancelLData.bottom =  new FormAttachment(980, 1000, 0);
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
			enterLData.top =  new FormAttachment(262, 1000, 0);
			enterLData.bottom =  new FormAttachment(980, 1000, 0);
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
					composite1background.dispose();
					//label1font.dispose();
					idlBtnfont.dispose();
					repositoryIDTxtfont.dispose();
					removePfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 407,398);
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
	    contextTxt.setText(context);
	    nameTxt.setText(identifier);
	    repositoryIDTxt.setText(repositoryId);
	    versionTxt.setText(version);
	    Iterator it=pameterList.iterator();
	    while(it.hasNext()){
	        ParameterTemplate parameter=(ParameterTemplate) it.next();
	        par.add(parameter.getIdentifier());
	    }
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        editP.setEnabled(false);
	    }else{
	        par.select(0);
	    }
	    it=idlTList.iterator();
	    while(it.hasNext()){
	        String idl=(String) it.next();
	        idlTypeCmb.add(idl.toString());
	    }
	//    CCMConstants.setIDL(idlTemp,idlTypeCmb);
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
			AddOperationDialog inst = new AddOperationDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=nameTxt.getText();
	    version=versionTxt.getText();
	    context=contextTxt.getText();
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
	    ParameterTemplate parameter=new ParameterTemplate("");
	    AddParameterDialog d=new AddParameterDialog(this.dialogShell,0,"Add Parameter");
	    d.setParameter(parameter);
	    d.setIdlTList(idlTList);
	    d.open();
	    if(!d.isState())return;
	    parameter=d.getParameter();
	    pameterList.add(parameter);
	    par.add(parameter.getIdentifier());
	    if(par.getItemCount()>0){
	        removeP.setEnabled(true);
	        editP.setEnabled(true);
	    }
	    
	}
	
	/** Auto-generated event handler method */
	protected void editPMouseDown(MouseEvent evt){
	    editParameter();
	}
	
	private void editParameter(){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    ParameterTemplate parameter=(ParameterTemplate) pameterList.get(index);
	    AddParameterDialog d=new AddParameterDialog(this.dialogShell,0,"Edit Parameter");
	    d.setParameter(parameter);
	    d.setIdlTList(idlTList);
	    d.open();
	    if(!d.isState())return;
	    parameter=d.getParameter();
	    pameterList.set(index,parameter);
	    par.setItem(index,parameter.getIdentifier());
	    
	}

	/** Auto-generated event handler method */
	protected void removePMouseDown(MouseEvent evt){
	    deleteParameter();
	}
	
	private void deleteParameter(){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    pameterList.remove(index);
	    par.remove(index);
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        editP.setEnabled(false);
	    }
	}
	
    /**
     * @return Returns the context.
     */
    public String getContext() {
        return context;
    }
    /**
     * @param context The context to set.
     */
    public void setContext(String context) {
        this.context = context;
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
    public java.util.List getPameterList() {
        return pameterList;
    }
    /**
     * @param list The list to set.
     */
    public void setPameterList(java.util.List list) {
        this.pameterList.clear();
        this.pameterList.addAll(list);
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
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    idlTemp=d.getIdlTemp();
	    CCMConstants.setIDL(idlTemp,idlTypeCmb);
	}

	/** Auto-generated event handler method */
	protected void idlTypeCmbWidgetSelected(SelectionEvent evt){
	    if(idlTemp.getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    idlTemp.setIdlKind(IDLKind.IDL_LITERAL);
	    idlTemp.setIndexOfIDLType(idlTypeCmb.getSelectionIndex());
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
			    context=contextTxt.getText();
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
