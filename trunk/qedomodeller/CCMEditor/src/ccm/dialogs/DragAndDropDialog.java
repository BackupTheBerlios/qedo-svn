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
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.SWT;

import org.eclipse.swt.widgets.Combo;

import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
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
public class DragAndDropDialog extends Dialog implements KeyListener{
	//private Button idlBtn;
	//private Button componentBtn;
	//private Button comImplBtn;
	private Combo discTypeCmb;
	private Label discriminatorTypeLb;
	private Shell dialogShell;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Composite composite2;
	private boolean state=false;
	private boolean isFirst=true;
	private String[]selections;
	private String discription="";
	 
	 
	

	public DragAndDropDialog(Shell parent, int style) {
		super(parent, style);
	}

	 
	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    

	   // setCategory(categorys[discTypeCmb.getSelectionIndex()]);
	    state=true;
	    //isAbstract=comImplBtn.getSelection();
	    //isLocal=componentBtn.getSelection();
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
			//componentBtn = new Button(composite2,SWT.CHECK| SWT.LEFT);
			//comImplBtn = new Button(composite2,SWT.CHECK| SWT.LEFT);
			discTypeCmb = new Combo(composite2,SWT.NULL);
			discriminatorTypeLb = new Label(composite2,SWT.NULL);
			 
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("DragAndDrop Component");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(270,70));
	 
		
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 260;
			composite2LData.heightHint = 20;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(260,20));
			FormData isLocalBtnLData = new FormData();
			isLocalBtnLData.height = 20;
			isLocalBtnLData.width = 70;
			isLocalBtnLData.left =  new FormAttachment(319, 1000, 0);
			isLocalBtnLData.right =  new FormAttachment(750, 1000, 0);
			isLocalBtnLData.top =  new FormAttachment(700, 1000, 0);
			isLocalBtnLData.bottom =  new FormAttachment(950, 1000, 0);
			//componentBtn.setLayoutData(isLocalBtnLData);
			//componentBtn.setText("is local");
			//componentBtn.setSize(new org.eclipse.swt.graphics.Point(70,20));
			//final Font isLocalBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			//componentBtn.setFont(isLocalBtnfont);
	
			 
	
	
			 
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			 
	
			FormData discTypeCmbLData = new FormData();
			discTypeCmbLData.height = 27;
			discTypeCmbLData.width = 204;
			discTypeCmbLData.left =  new FormAttachment(250, 1000, 0);
			discTypeCmbLData.right =  new FormAttachment(993, 1000, 0);
			discTypeCmbLData.top =  new FormAttachment(60, 1000, 0);
			discTypeCmbLData.bottom =  new FormAttachment(1000, 1000, 0);
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
			discriminatorTypeLbLData.left =  new FormAttachment(30, 1000, 0);
			discriminatorTypeLbLData.right =  new FormAttachment(300, 1000, 0);
			discriminatorTypeLbLData.top =  new FormAttachment(145, 1000, 0);
			discriminatorTypeLbLData.bottom =  new FormAttachment(980, 1000, 0);
			discriminatorTypeLb.setLayoutData(discriminatorTypeLbLData);
			discriminatorTypeLb.setText("Type:");
			discriminatorTypeLb.setSize(new org.eclipse.swt.graphics.Point(120,19));
			discriminatorTypeLb.setEnabled(true);
			discriminatorTypeLb.setFont(idlBtnfont);
	  
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 260;
			composite3LData.heightHint = 34;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(260,34));
			composite3.setFont(idlBtnfont);
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(745, 1000, 0);
			cancelLData.right =  new FormAttachment(992, 1000, 0);
			cancelLData.top =  new FormAttachment( 302, 1000, 0);
			cancelLData.bottom =  new FormAttachment(847, 1000, 0);
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
			enterLData.left =  new FormAttachment(475, 1000, 0);
			enterLData.right =  new FormAttachment(695, 1000, 0);
			enterLData.top =  new FormAttachment( 302, 1000, 0);
			enterLData.bottom =  new FormAttachment(847, 1000, 0);
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
				 
				 
					idlBtnfont.dispose();
					discTypeCmbfont.dispose();
					 
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 270,70);
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
		dialogShell.setText(discription);
		for (int i=0;i<selections.length;i++){
		discTypeCmb.add(selections[i]);
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
			DragAndDropDialog inst = new DragAndDropDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	 /**
     * @return Returns the identifier.
     */
    public boolean getType() {
        return isFirst;
    }
    /**
     * @param identifier The identifier tbooleano set.
     */
    public void setType(boolean type) {
        this.isFirst = type;
    }
    
    public void setslections(String[]selections) {
        this.selections = selections;
    }
    public void setDiscription(String discription) {
        this.discription = discription;
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
   
  
	protected void discTypeCmbWidgetSelected(SelectionEvent evt){
		if(discTypeCmb.getSelectionIndex()==0)
			isFirst=true;
		else
			isFirst=false;
		 
	}


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
 
  