package ccm.dialogs;


import java.util.Iterator;
import java.util.LinkedList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
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
import org.eclipse.swt.widgets.Shell;

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
public class EditIDLTypeDialog  extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Button idlBtn;
	 
	private Combo idlTypeCmb;
	private Label label2;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	 
	private Composite composite2;
 
	private Shell dialogShell; 
	
	private boolean state=false;
	 
	private java.util.List idlTList=new LinkedList();
	private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
	private String absName="";
	
	public EditIDLTypeDialog(Shell parent, int style) {
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
			label2 = new Label(composite2,SWT.NULL);
			idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
			idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
			
		
	 
			
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Edit IDLType");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(407,105));
	
			 

			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 400;
			composite2LData.heightHint = 60;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(400,60));
	
			FormData idlBtnLData = new FormData();
			idlBtnLData.height = 18;
			idlBtnLData.width = 28;
			idlBtnLData.left =  new FormAttachment(923, 1000, 0);
			idlBtnLData.right =  new FormAttachment(993, 1000, 0);
			idlBtnLData.top =  new FormAttachment(210, 1000, 0);
			idlBtnLData.bottom =  new FormAttachment(610, 1000, 0);
			idlBtn.setLayoutData(idlBtnLData);
			idlBtn.setText("....");
			idlBtn.setSize(new org.eclipse.swt.graphics.Point(28,21));
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			final Font idlBtnfont1 = new Font(Display.getDefault(),"Tahoma",9,1);
			idlBtn.setFont(idlBtnfont1);
			idlBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					idlBtnMouseDown(evt);
				}
			}); 
			//final Font repositoryIDTxtfont = new Font(Display.getDefault(),"Tahoma",10,0);
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 24;
			idlTypeCmbLData.width = 249;
			idlTypeCmbLData.left =  new FormAttachment(243, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(918, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(210, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(272, 1000, 0);
			idlTypeCmb.setLayoutData(idlTypeCmbLData);
			idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(249,24));
			idlTypeCmb.setEnabled(true);
			idlTypeCmb.setFont(idlBtnfont);
			idlTypeCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					idlTypeCmbWidgetSelected(evt);
				}
			});
	
			FormData label2LData = new FormData();
			label2LData.height = 21;
			label2LData.width = 90;
			label2LData.left =  new FormAttachment(13, 1000, 0);
			label2LData.right =  new FormAttachment(238, 1000, 0);
			label2LData.top =  new FormAttachment(249, 1000, 0);
			label2LData.bottom =  new FormAttachment(600, 1000, 0);
			label2.setLayoutData(label2LData);
			label2.setText("Idl Type : ");
			label2.setSize(new org.eclipse.swt.graphics.Point(90,20));
			label2.setFont(idlBtnfont1);
	
			 
	 
			 
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
			composite3LData.heightHint = 30;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(386,30));
			composite3.setFont(idlBtnfont);
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(775, 1000, 0);
			cancelLData.right =  new FormAttachment(976, 1000, 0);
			cancelLData.top =  new FormAttachment(1, 1000, 0);
			cancelLData.bottom =  new FormAttachment(787, 1000, 0);
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
			enterLData.top =  new FormAttachment(1, 1000, 0);
			enterLData.bottom =  new FormAttachment(787, 1000, 0);
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
					//composite1background.dispose();
					 
					idlBtnfont.dispose();
					idlBtnfont1.dispose();
				 ;
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 407,105);
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
	    
	    Iterator it=idlTList.iterator();
	    while(it.hasNext()){
	        String idl=(String) it.next();
	        idlTypeCmb.add(idl.toString());
	    }
	    CCMConstants.setIDL(idlTemp,idlTypeCmb);
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
	    
	    state=true;
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
		dialogShell.close();
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



