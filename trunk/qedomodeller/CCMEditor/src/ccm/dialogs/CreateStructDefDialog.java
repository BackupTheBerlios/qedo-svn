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
import org.eclipse.swt.widgets.Text;

import ccm.CCMConstants;
import ccm.model.template.FieldTemplate;


/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class CreateStructDefDialog extends org.eclipse.swt.widgets.Dialog  implements KeyListener{
	private Shell dialogShell;
	private Button enter;
	private Button cancel;
//	private Composite composite3;
	private Label nameLb;
	private Text nameTxt;
	private List par;
	private Label parLb;
	private Button addP;
	private Button editP;
	private Button removeP;
	private Label repositoryIDLb;
	private Text repositoryIDTxt;
	private Label versionLb;
	private Text versionTxt;
	private Composite composite2;
	 

	private boolean state=false;
	private String identifier="";
	private String repositoryId="";
	private String version="";
	private java.util.List memberList=new LinkedList();
	private java.util.List idlTList=new LinkedList();
    private String absName;
	
	
	
	public CreateStructDefDialog(Shell parent, int style) {
		super(parent, style);
	}

	/** Auto-generated event handler method */
	protected void removePMouseDown(MouseEvent evt){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    memberList.remove(index);
	    par.remove(index);
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        editP.setEnabled(false);
	    }
	}

	/** Auto-generated event handler method */
	protected void editPMouseDown(MouseEvent evt){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    FieldTemplate field=(FieldTemplate) memberList.get(index);
	    AddFieldDialog d=new AddFieldDialog(this.dialogShell,0,"Edit Field");
	    d.setField(field);
	    d.setIdlTList(idlTList);
	    d.open();
	    if(!d.isState())return;
	    field=d.getField();
	    memberList.set(index,field);
	    par.setItem(index,field.getIdentifier());
	}

	/** Auto-generated event handler method */
	protected void addPMouseDown(MouseEvent evt){
	    FieldTemplate field=new FieldTemplate("");
	    AddFieldDialog d=new AddFieldDialog(this.dialogShell,0,"Add Field");
	    d.setField(field);
	    d.setIdlTList(idlTList);
	    d.open();
	    if(!d.isState())return;
	    field=d.getField();
	    memberList.add(field);
	    par.add(field.getIdentifier());
	    if(par.getItemCount()>0){
	        removeP.setEnabled(true);
	        editP.setEnabled(true);
	    }
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    identifier=nameTxt.getText();
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
		 
			composite2 = new Composite(dialogShell,SWT.NO_RADIO_GROUP);
			versionTxt = new Text(composite2,SWT.BORDER);
			versionLb = new Label(composite2,SWT.NULL);
			repositoryIDTxt = new Text(composite2,SWT.BORDER);
			repositoryIDLb = new Label(composite2,SWT.NULL);
			cancel = new Button(composite2,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite2,SWT.PUSH| SWT.CENTER);
	
			removeP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			editP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			addP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			parLb = new Label(composite2,SWT.NULL);
			par = new List(composite2,SWT.BORDER|SWT.V_SCROLL);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			//composite3 = new Composite(dialogShell,SWT.NULL);
			
			dialogShell.setText("Add Struct");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(407,390));
	
			 
	 
		//	final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
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
	
			FormData versionTxtLData = new FormData();
			versionTxtLData.height = 13;
			versionTxtLData.width = 287;
			versionTxtLData.left =  new FormAttachment(265, 1000, 0);
			versionTxtLData.right =  new FormAttachment(993, 1000, 0);
			versionTxtLData.top =  new FormAttachment(146, 1000, 0);
			versionTxtLData.bottom =  new FormAttachment(225, 1000, 0);
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
			versionLbLData.right =  new FormAttachment(253, 1000, 0);
			versionLbLData.top =  new FormAttachment(156, 1000, 0);
			versionLbLData.bottom =  new FormAttachment(214, 1000, 0);
			versionLb.setLayoutData(versionLbLData);
			versionLb.setText("Version:");
			versionLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
	 		final Font versionLbfont = new Font(Display.getDefault(),"Tahoma",8,1);
			versionLb.setFont(versionLbfont);
	
			FormData repositoryIDTxtLData = new FormData();
			repositoryIDTxtLData.height = 13;
			repositoryIDTxtLData.width = 287;
			repositoryIDTxtLData.left =  new FormAttachment(265, 1000, 0);
			repositoryIDTxtLData.right =  new FormAttachment(993, 1000, 0);
			repositoryIDTxtLData.top =  new FormAttachment(84, 1000, 0);
			repositoryIDTxtLData.bottom =  new FormAttachment(144, 1000, 0);
			repositoryIDTxt.setLayoutData(repositoryIDTxtLData);
			repositoryIDTxt.setDoubleClickEnabled(false);
	 		final Font repositoryIDTxtfont = new Font(Display.getDefault(),"Tahoma",7,0);
			repositoryIDTxt.setFont(repositoryIDTxtfont);
			repositoryIDTxt.setEditable(false);
			repositoryIDTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
			repositoryIDTxt.setEnabled(false);
	
			FormData repositoryIDLbLData = new FormData();
			repositoryIDLbLData.height = 20;
			repositoryIDLbLData.width = 90;
			repositoryIDLbLData.left =  new FormAttachment(13, 1000, 0);
			repositoryIDLbLData.right =  new FormAttachment(259, 1000, 0);
			repositoryIDLbLData.top =  new FormAttachment(87, 1000, 0);
			repositoryIDLbLData.bottom =  new FormAttachment(140, 1000, 0);
			repositoryIDLb.setLayoutData(repositoryIDLbLData);
			repositoryIDLb.setText("Repository Id:");
			repositoryIDLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			repositoryIDLb.setFont(versionLbfont);
	
			FormData removePLData = new FormData();
			removePLData.height = 25;
			removePLData.width = 70;
			removePLData.left =  new FormAttachment(26, 1000, 0);
			removePLData.right =  new FormAttachment(201, 1000, 0);
			removePLData.top =  new FormAttachment(697, 1000, 0);
			removePLData.bottom =  new FormAttachment(771, 1000, 0);
			removeP.setLayoutData(removePLData);
			removeP.setText("REMOVE");
			removeP.setSize(new org.eclipse.swt.graphics.Point(70,25));
			final Font removePfont = new Font(Display.getDefault(),"Tahoma",8,1);
			removeP.setFont(removePfont);
			removeP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					removePMouseDown(evt);
				}
			});
	
			FormData editPLData = new FormData();
			editPLData.height = 25;
			editPLData.width = 70;
			editPLData.left =  new FormAttachment(26, 1000, 0);
			editPLData.right =  new FormAttachment(201, 1000, 0);
			editPLData.top =  new FormAttachment(550, 1000, 0);
			editPLData.bottom =  new FormAttachment(624, 1000, 0);
			editP.setLayoutData(editPLData);
			editP.setText("EDIT");
			editP.setSize(new org.eclipse.swt.graphics.Point(70,25));
			editP.setFont(removePfont);
			editP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					editPMouseDown(evt);
				}
			});
	
		 	FormData addPLData = new FormData();
		 	addPLData.height = 25;
		 	addPLData.width = 70;
		 	addPLData.left =  new FormAttachment(26, 1000, 0);
		 	addPLData.right =  new FormAttachment(201, 1000, 0);
		 	addPLData.top =  new FormAttachment(402, 1000, 0);
		 	addPLData.bottom =  new FormAttachment(476, 1000, 0);
			
			addP.setLayoutData(addPLData);
			addP.setText("ADD");
			addP.setSize(new org.eclipse.swt.graphics.Point(70,25));
			addP.setFont(removePfont);
			addP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					addPMouseDown(evt);
				}
			});
	

			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(775, 1000, 0);
			cancelLData.right =  new FormAttachment(976, 1000, 0);
			cancelLData.top =  new FormAttachment (850, 1000, 0);
			cancelLData.bottom =  new FormAttachment(947, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(77,23));
			cancel.setFont(versionLbfont);
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
			enterLData.top =  new FormAttachment(850, 1000, 0);
			enterLData.bottom =  new FormAttachment(947, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(77,23));
			enter.setFont(versionLbfont);
			enter.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					enterMouseDown(evt);
				}
			});
			FormData parLbLData = new FormData();
			parLbLData.height = 20;
			parLbLData.width = 90;
			parLbLData.left =  new FormAttachment(13, 1000, 0);
			parLbLData.right =  new FormAttachment(253, 1000, 0);
			parLbLData.top =  new FormAttachment(233, 1000, 0);
			parLbLData.bottom =  new FormAttachment(279, 1000, 0);
			parLb.setLayoutData(parLbLData);
			//parLb.setAlignment(SWT.RIGHT);
			parLb.setText("Members:");
			parLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			parLb.setFont(versionLbfont);
	
			FormData parLData = new FormData();
			parLData.height = 100;
			parLData.width = 293;
			parLData.left =  new FormAttachment(265, 1000, 0);
			parLData.right =  new FormAttachment(993, 1000, 0);
			parLData.top =  new FormAttachment(235, 1000, 0);
			parLData.bottom =  new FormAttachment(786, 1000, 0);
			par.setLayoutData(parLData);
			par.setFont(repositoryIDTxtfont);
			par.setSize(new org.eclipse.swt.graphics.Point(293,100));
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 287;
			nameTxtLData.left =  new FormAttachment(265, 1000, 0);
			nameTxtLData.right =  new FormAttachment(993, 1000, 0);
			nameTxtLData.top =  new FormAttachment(16, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(82, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(repositoryIDTxtfont);
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
			nameLbLData.right =  new FormAttachment(258, 1000, 0);
			nameLbLData.top =  new FormAttachment(20, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(72, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Identifier:");
			nameLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			nameLb.setFont(versionLbfont);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	 
	
			
			 
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
					 
					versionLbfont.dispose();
					repositoryIDTxtfont.dispose();
					removePfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 407,340);
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
	    Iterator it=memberList.iterator();
	    while(it.hasNext()){
	        FieldTemplate member=(FieldTemplate) it.next();
	        par.add(member.getIdentifier());
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
			CreateStructDefDialog inst = new CreateStructDefDialog(shell, SWT.NULL);
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
    public java.util.List getMemberList() {
        return memberList;
    }
    /**
     * @param list The list to set.
     */
    public void setMemberList(java.util.List list) {
        this.memberList.clear();
        this.memberList.addAll(list);
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
	protected void versionTxtKeyReleased(KeyEvent evt){
	    version=versionTxt.getText();
	    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
	    repositoryIDTxt.setText(repositoryId);
	}

	/** Auto-generated event handler method */
	protected void nameTxtKeyReleased(KeyEvent evt){
	    identifier=nameTxt.getText();
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
