package ccm.dialogs;

import java.util.Iterator;
import java.util.LinkedList;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.SWT;

import ccm.CCMConstants;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class SetIdlFromPropertyDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Label idlLb;
	private Combo idlTypesCmb;
	private Button idlBtn;
	private Button cancelBtn;
	private Button enterBtn;
	private Composite composite3;
	private Composite composite2;
	private Composite composite1;
	private Shell dialogShell;
	
	private boolean state;
	private IDLTemplate idlTemp;
	private String discription;
	private java.util.List idlTList=new LinkedList();

	public SetIdlFromPropertyDialog(Shell parent, int style) {
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
			composite1 = new Composite(dialogShell,SWT.NULL);
			composite2 = new Composite(dialogShell,SWT.NULL);
			idlLb = new Label(composite2,SWT.NULL);
			idlTypesCmb = new Combo(composite2,SWT.NULL);
			idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancelBtn = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enterBtn = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(439,184));
	
			GridData composite1LData = new GridData();
			composite1LData.verticalAlignment = GridData.CENTER;
			composite1LData.horizontalAlignment = GridData.BEGINNING;
			composite1LData.widthHint = 431;
			composite1LData.heightHint = 54;
			composite1LData.horizontalIndent = 0;
			composite1LData.horizontalSpan = 1;
			composite1LData.verticalSpan = 1;
			composite1LData.grabExcessHorizontalSpace = false;
			composite1LData.grabExcessVerticalSpace = false;
			composite1.setLayoutData(composite1LData);
			composite1.setSize(new org.eclipse.swt.graphics.Point(431,54));
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			composite1.setBackground(composite1background);
			FormLayout composite1Layout = new FormLayout();
			composite1.setLayout(composite1Layout);
			composite1Layout.marginWidth = 0;
			composite1Layout.marginHeight = 0;
			composite1Layout.spacing = 0;
			composite1.layout();
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 432;
			composite2LData.heightHint = 68;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(432,68));
	
			FormData idlLbLData = new FormData();
			idlLbLData.height = 20;
			idlLbLData.width = 125;
			idlLbLData.left =  new FormAttachment(12, 1000, 0);
			idlLbLData.right =  new FormAttachment(302, 1000, 0);
			idlLbLData.top =  new FormAttachment(80, 1000, 0);
			idlLbLData.bottom =  new FormAttachment(375, 1000, 0);
			idlLb.setLayoutData(idlLbLData);
			idlLb.setText("descriminator type");
			idlLb.setSize(new org.eclipse.swt.graphics.Point(125,20));
			final Font idlLbfont = new Font(Display.getDefault(),"Tahoma",10,1);
			idlLb.setFont(idlLbfont);
	
			FormData idlTypesCmbLData = new FormData();
			idlTypesCmbLData.height = 27;
			idlTypesCmbLData.width = 237;
			idlTypesCmbLData.left =  new FormAttachment(306, 1000, 0);
			idlTypesCmbLData.right =  new FormAttachment(924, 1000, 0);
			idlTypesCmbLData.top =  new FormAttachment(80, 1000, 0);
			idlTypesCmbLData.bottom =  new FormAttachment(433, 1000, 0);
			idlTypesCmb.setLayoutData(idlTypesCmbLData);
			idlTypesCmb.setSize(new org.eclipse.swt.graphics.Point(237,27));
			final Font idlTypesCmbfont = new Font(Display.getDefault(),"Tahoma",10,0);
			idlTypesCmb.setFont(idlTypesCmbfont);
			idlTypesCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					idlTypesCmbWidgetSelected(evt);
				}
			});
	
			FormData idlBtnLData = new FormData();
			idlBtnLData.height = 21;
			idlBtnLData.width = 30;
			idlBtnLData.left =  new FormAttachment(927, 1000, 0);
			idlBtnLData.right =  new FormAttachment(996, 1000, 0);
			idlBtnLData.top =  new FormAttachment(80, 1000, 0);
			idlBtnLData.bottom =  new FormAttachment(389, 1000, 0);
			idlBtn.setLayoutData(idlBtnLData);
			idlBtn.setText("....");
			idlBtn.setSize(new org.eclipse.swt.graphics.Point(30,21));
			idlBtn.setFont(idlLbfont);
			idlBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					idlBtnMouseDown(evt);
				}
			});
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 431;
			composite3LData.heightHint = 45;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(431,45));
	
			FormData cancelBtnLData = new FormData();
			cancelBtnLData.height = 25;
			cancelBtnLData.width = 70;
			cancelBtnLData.left =  new FormAttachment(792, 1000, 0);
			cancelBtnLData.right =  new FormAttachment(954, 1000, 0);
			cancelBtnLData.top =  new FormAttachment(300, 1000, 0);
			cancelBtnLData.bottom =  new FormAttachment(855, 1000, 0);
			cancelBtn.setLayoutData(cancelBtnLData);
			cancelBtn.setText("CANCEL");
			cancelBtn.setSize(new org.eclipse.swt.graphics.Point(70,25));
			cancelBtn.setFont(idlLbfont);
			cancelBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelBtnMouseDown(evt);
				}
			});
	
			FormData enterBtnLData = new FormData();
			enterBtnLData.height = 25;
			enterBtnLData.width = 70;
			enterBtnLData.left =  new FormAttachment(613, 1000, 0);
			enterBtnLData.right =  new FormAttachment(776, 1000, 0);
			enterBtnLData.top =  new FormAttachment(300, 1000, 0);
			enterBtnLData.bottom =  new FormAttachment(855, 1000, 0);
			enterBtn.setLayoutData(enterBtnLData);
			enterBtn.setText("ENTER");
			enterBtn.setSize(new org.eclipse.swt.graphics.Point(70,25));
			enterBtn.setFont(idlLbfont);
			enterBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					enterBtnMouseDown(evt);
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
					idlLbfont.dispose();
					idlTypesCmbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 439,184);
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
	    idlLb.setText(discription);
	    Iterator it=idlTList.iterator();
	    while(it.hasNext()){
	        String idl=(String) it.next();
	        idlTypesCmb.add(idl.toString());
	    }
	    CCMConstants.setIDL(idlTemp,idlTypesCmb);
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
			SetIdlFromPropertyDialog inst = new SetIdlFromPropertyDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void idlTypesCmbWidgetSelected(SelectionEvent evt){
	    if(idlTemp.getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypesCmb.remove(idlTypesCmb.getItemCount()-1);
	    }
	    idlTemp.setIdlKind(IDLKind.IDL_LITERAL);
	    idlTemp.setIndexOfIDLType(idlTypesCmb.getSelectionIndex());
	}

	/** Auto-generated event handler method */
	protected void idlBtnMouseDown(MouseEvent evt){
	    SetOIDLTypeDialog d=new SetOIDLTypeDialog(this.dialogShell,0);
	    d.setIdlTemp(idlTemp);
	    d.open();
	    if(!d.isState())return;
	    if(idlTemp.getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypesCmb.remove(idlTypesCmb.getItemCount()-1);
	    }
	    idlTemp=getIdlTemp();
	    CCMConstants.setIDL(idlTemp,idlTypesCmb);
	}

	/** Auto-generated event handler method */
	protected void cancelBtnMouseDown(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterBtnMouseDown(MouseEvent evt){
	    state=true;
		dialogShell.close();
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
