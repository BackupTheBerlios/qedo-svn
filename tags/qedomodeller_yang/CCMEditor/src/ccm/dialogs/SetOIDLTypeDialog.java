package ccm.dialogs;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
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
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class SetOIDLTypeDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Button cancelBtn;
	private Button enterBtn;
	private Composite composite3;
	private Text scaleTxt;
	private Text boundDigitTxt;
	private Label scaleLb;
	private Label BoundDigitLb;
	private Composite composite2;
	private Button sequenceBtn;
	private Button arrayBtn;
	private Button fixedBtn;
	private Button stringBtn;
	private Button wstringBtn;
	private Group group1;
	//private Composite composite1;
	private Shell dialogShell;
	
	private boolean state=false;
	private IDLTemplate idlTemp;

	public SetOIDLTypeDialog(Shell parent, int style) {
		super(parent, style);
	}

	/**
	* Opens the Dialog Shell.
	* Auto-generated code - any changes you make will disappear.
	*/
	public void open(){
		try {
			preInitGUI();
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",9,1);
			final Font font = new Font(Display.getDefault(),"Tahoma",8,1);
			final Font idlBtnfont3 = new Font(Display.getDefault(),"Tahoma",7,1);
			final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			 
			Shell parent = getParent();
			dialogShell = new Shell(parent, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
			dialogShell.setText(getText());
			 
			group1 = new Group(dialogShell,SWT.NULL);
			sequenceBtn = new Button(group1,SWT.CHECK| SWT.LEFT);
			arrayBtn = new Button(group1,SWT.CHECK| SWT.LEFT);
			fixedBtn = new Button(group1,SWT.CHECK| SWT.LEFT);
			stringBtn = new Button(group1,SWT.CHECK| SWT.LEFT);
			wstringBtn = new Button(group1,SWT.CHECK| SWT.LEFT);
			composite2 = new Composite(dialogShell,SWT.NULL);
			scaleTxt = new Text(composite2,SWT.BORDER);
			boundDigitTxt = new Text(composite2,SWT.BORDER);
			scaleLb = new Label(composite2,SWT.NULL);
			BoundDigitLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancelBtn = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enterBtn = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(493,170));
	
		 
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
		 
	
			GridData group1LData = new GridData();
			group1LData.verticalAlignment = GridData.CENTER;
			group1LData.horizontalAlignment = GridData.BEGINNING;
			group1LData.widthHint = 478;
			group1LData.heightHint = 33;
			group1LData.horizontalIndent = 0;
			group1LData.horizontalSpan = 1;
			group1LData.verticalSpan = 1;
			group1LData.grabExcessHorizontalSpace = false;
			group1LData.grabExcessVerticalSpace = false;
			group1.setLayoutData(group1LData);
			group1.setSize(new org.eclipse.swt.graphics.Point(478,33));
	
			FormData sequenceBtnLData = new FormData();
			sequenceBtnLData.height = 20;
			sequenceBtnLData.width = 83;
			sequenceBtnLData.left =  new FormAttachment(758, 1000, 0);
			sequenceBtnLData.right =  new FormAttachment(980, 1000, 0);
			sequenceBtnLData.top =  new FormAttachment(83, 1000, 0);
			sequenceBtnLData.bottom =  new FormAttachment(750, 1000, 0);
			sequenceBtn.setLayoutData(sequenceBtnLData);
			sequenceBtn.setText("Sequence");
			sequenceBtn.setSize(new org.eclipse.swt.graphics.Point(83,20));
			final Font sequenceBtnfont = new Font(Display.getDefault(),"Tahoma",10,1);
			sequenceBtn.setFont( font);
			sequenceBtn.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					sequenceBtnWidgetSelected(evt);
				}
			});
	
			FormData arrayBtnLData = new FormData();
			arrayBtnLData.height = 20;
			arrayBtnLData.width = 57;
			arrayBtnLData.left =  new FormAttachment(603, 1000, 0);
			arrayBtnLData.right =  new FormAttachment(734, 1000, 0);
			arrayBtnLData.top =  new FormAttachment(83, 1000, 0);
			arrayBtnLData.bottom =  new FormAttachment(750, 1000, 0);
			arrayBtn.setLayoutData(arrayBtnLData);
			arrayBtn.setText("array");
			arrayBtn.setSize(new org.eclipse.swt.graphics.Point(57,20));
			arrayBtn.setFont( font);
			arrayBtn.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					arrayBtnWidgetSelected(evt);
				}
			});
	
			FormData fixedBtnLData = new FormData();
			fixedBtnLData.height = 20;
			fixedBtnLData.width = 57;
			fixedBtnLData.left =  new FormAttachment(422, 1000, 0);
			fixedBtnLData.right =  new FormAttachment(543, 1000, 0);
			fixedBtnLData.top =  new FormAttachment(83, 1000, 0);
			fixedBtnLData.bottom =  new FormAttachment(750, 1000, 0);
			fixedBtn.setLayoutData(fixedBtnLData);
			fixedBtn.setText("Fixed");
			fixedBtn.setSize(new org.eclipse.swt.graphics.Point(57,20));
			fixedBtn.setFont( font);
			fixedBtn.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					fixedBtnWidgetSelected(evt);
				}
			});
	
			FormData stringBtnLData = new FormData();
			stringBtnLData.height = 20;
			stringBtnLData.width = 57;
			stringBtnLData.left =  new FormAttachment(221, 1000, 0);
			stringBtnLData.right =  new FormAttachment(359, 1000, 0);
			stringBtnLData.top =  new FormAttachment(83, 1000, 0);
			stringBtnLData.bottom =  new FormAttachment(750, 1000, 0);
			stringBtn.setLayoutData(stringBtnLData);
			stringBtn.setText("String");
			stringBtn.setSize(new org.eclipse.swt.graphics.Point(57,20));
			stringBtn.setFont( font);
			stringBtn.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					stringBtnWidgetSelected(evt);
				}
			});
	
			FormData wstringBtnLData = new FormData();
			wstringBtnLData.height = 20;
			wstringBtnLData.width = 69;
			wstringBtnLData.left =  new FormAttachment(15, 1000, 0);
			wstringBtnLData.right =  new FormAttachment(183, 1000, 0);
			wstringBtnLData.top =  new FormAttachment(83, 1000, 0);
			wstringBtnLData.bottom =  new FormAttachment(750, 1000, 0);
			wstringBtn.setLayoutData(wstringBtnLData);
			wstringBtn.setSelection(true);
			wstringBtn.setText("Wstring");
			wstringBtn.setSize(new org.eclipse.swt.graphics.Point(69,20));
			wstringBtn.setFont( font);
			wstringBtn.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					wstringBtnWidgetSelected(evt);
				}
			});
			FormLayout group1Layout = new FormLayout();
			group1.setLayout(group1Layout);
			group1Layout.marginWidth = 0;
			group1Layout.marginHeight = 0;
			group1Layout.spacing = 0;
			group1.layout();
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 485;
			composite2LData.heightHint = 63;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(485,63));
	
			FormData scaleTxtLData = new FormData();
			scaleTxtLData.height = 18;
			scaleTxtLData.width = 200;
			scaleTxtLData.left =  new FormAttachment(153, 1000, 0);
			scaleTxtLData.right =  new FormAttachment(980, 1000, 0);
			scaleTxtLData.top =  new FormAttachment(424, 1000, 0);
			scaleTxtLData.bottom =  new FormAttachment(738, 1000, 0);
			scaleTxt.setLayoutData(scaleTxtLData);
			scaleTxt.setText("0");
			scaleTxt.setSize(new org.eclipse.swt.graphics.Point(200,18));
	
			FormData boundDigitTxtLData = new FormData();
			boundDigitTxtLData.height = 18;
			boundDigitTxtLData.width = 200;
			boundDigitTxtLData.left =  new FormAttachment(153, 1000, 0);
			boundDigitTxtLData.right =  new FormAttachment(980, 1000, 0);
			boundDigitTxtLData.top =  new FormAttachment(78, 1000, 0);
			boundDigitTxtLData.bottom =  new FormAttachment(395, 1000, 0);
			boundDigitTxt.setLayoutData(boundDigitTxtLData);
			boundDigitTxt.setText("0");
			boundDigitTxt.setSize(new org.eclipse.swt.graphics.Point(200,18));
	
			FormData scaleLbLData = new FormData();
			scaleLbLData.height = 20;
			scaleLbLData.width = 60;
			scaleLbLData.left =  new FormAttachment(12, 1000, 0);
			scaleLbLData.right =  new FormAttachment(148, 1000, 0);
			scaleLbLData.top =  new FormAttachment(424, 1000, 0);
			scaleLbLData.bottom =  new FormAttachment(738, 1000, 0);
			scaleLb.setLayoutData(scaleLbLData);
			scaleLb.setText("Scale:");
			scaleLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			scaleLb.setFont( font);
	
			FormData BoundDigitLbLData = new FormData();
			BoundDigitLbLData.height = 20;
			BoundDigitLbLData.width = 60;
			BoundDigitLbLData.left =  new FormAttachment(12, 1000, 0);
			BoundDigitLbLData.right =  new FormAttachment(148, 1000, 0);
			BoundDigitLbLData.top =  new FormAttachment(80, 1000, 0);
			BoundDigitLbLData.bottom =  new FormAttachment(375, 1000, 0);
			BoundDigitLb.setLayoutData(BoundDigitLbLData);
			BoundDigitLb.setText("Bound:");
			BoundDigitLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			BoundDigitLb.setFont( font);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 442;
			composite3LData.heightHint = 38;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(442,38));
	
			FormData cancelBtnLData = new FormData();
			cancelBtnLData.height = 25;
			cancelBtnLData.width = 70;
			cancelBtnLData.left =  new FormAttachment(763, 1000, 0);
			cancelBtnLData.right =  new FormAttachment(921, 1000, 0);
			cancelBtnLData.top =  new FormAttachment(1, 1000, 0);
			cancelBtnLData.bottom =  new FormAttachment(609, 1000, 0);
			cancelBtn.setLayoutData(cancelBtnLData);
			cancelBtn.setText("CANCEL");
			cancelBtn.setSize(new org.eclipse.swt.graphics.Point(70,25));
			cancelBtn.setFont( font);
			cancelBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelBtnMouseDown(evt);
				}
			});
	
			FormData enterBtnLData = new FormData();
			enterBtnLData.height = 25;
			enterBtnLData.width = 70;
			enterBtnLData.left =  new FormAttachment(566, 1000, 0);
			enterBtnLData.right =  new FormAttachment(725, 1000, 0);
			enterBtnLData.top =  new FormAttachment(1, 1000, 0);
			enterBtnLData.bottom =  new FormAttachment(609, 1000, 0);
			enterBtn.setLayoutData(enterBtnLData);
			enterBtn.setText("ENTER");
			enterBtn.setSize(new org.eclipse.swt.graphics.Point(70,25));
			enterBtn.setFont( font);
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
					sequenceBtnfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 493,170);
			dialogShell.setSize(bounds.width, bounds.height);
			dialogShell.setText("Constructed Type");
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
	    switch(idlTemp.getIdlKind().getValue()){
	    case IDLKind.ARRAY:
	        wstringBtn.setSelection(false);
	    	stringBtn.setSelection(false);
	    	fixedBtn.setSelection(false);
	    	arrayBtn.setSelection(true);
	    	sequenceBtn.setSelection(false);
	    	BoundDigitLb.setText("Bound:");
	    	scaleLb.setVisible(false);
	    	scaleTxt.setVisible(false);	 
	    	boundDigitTxt.setText((new Integer(idlTemp.getBound())).toString());
	    	break;
	    case IDLKind.SEQUENCE:
	        wstringBtn.setSelection(false);
	    	stringBtn.setSelection(false);
	    	fixedBtn.setSelection(false);
	    	arrayBtn.setSelection(false);
	    	sequenceBtn.setSelection(true);
	    	BoundDigitLb.setText("Bound:");
	    	scaleLb.setVisible(false);
	    	scaleTxt.setVisible(false);	 	    	
	    	boundDigitTxt.setText((new Integer(idlTemp.getBound())).toString());
	    	break;
	    case IDLKind.STRING:
	        wstringBtn.setSelection(false);
	    	stringBtn.setSelection(true);
	    	fixedBtn.setSelection(false);
	    	arrayBtn.setSelection(false);
	    	sequenceBtn.setSelection(false);
	    	BoundDigitLb.setText("Bound:");
	    	scaleLb.setVisible(false);
	    	scaleTxt.setVisible(false);	 	    	
	    	boundDigitTxt.setText((new Integer(idlTemp.getBound())).toString());
	    	break;
	    case IDLKind.FIXED:
	        wstringBtn.setSelection(false);
	    	stringBtn.setSelection(false);
	    	fixedBtn.setSelection(true);
	    	arrayBtn.setSelection(false);
	    	sequenceBtn.setSelection(false);
	    	BoundDigitLb.setText("Digits:");
	    	scaleLb.setVisible(true);
	    	scaleTxt.setVisible(true);	 	    	
	    	boundDigitTxt.setText((new Integer(idlTemp.getDigits())).toString());
	    	scaleTxt.setText((new Integer(idlTemp.getScale())).toString());
	    	break;
	    default:
	        wstringBtn.setSelection(true);
	    	stringBtn.setSelection(false);
	    	fixedBtn.setSelection(false);
	    	arrayBtn.setSelection(false);
	    	sequenceBtn.setSelection(false);
	    	BoundDigitLb.setText("Bound:");
	    	scaleLb.setVisible(false);
	    	scaleTxt.setVisible(false);	 
	    	boundDigitTxt.setText((new Integer(idlTemp.getBound())).toString());  
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
			SetOIDLTypeDialog inst = new SetOIDLTypeDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterBtnMouseDown(MouseEvent evt){
	    state=true;
	    switch(idlTemp.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	    case IDLKind.ARRAY:
	    case IDLKind.SEQUENCE:
	    case IDLKind.STRING:
    		idlTemp.setBound((new Integer(boundDigitTxt.getText())).intValue());
    		break;
	    case IDLKind.FIXED:
    		idlTemp.setDigits((new Integer(boundDigitTxt.getText())).intValue());
    		idlTemp.setScale((new Integer(scaleTxt.getText())).intValue());
    		break;

	    }
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelBtnMouseDown(MouseEvent evt){
		dialogShell.close();
	}
    /**
     * @return Returns the state.
     */
    public boolean isState() {
        return state;
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

	/** Auto-generated event handler method */
	protected void wstringBtnWidgetSelected(SelectionEvent evt){
		stringBtn.setSelection(false);
		fixedBtn.setSelection(false);
		arrayBtn.setSelection(false);
		sequenceBtn.setSelection(false);
		BoundDigitLb.setText("Bound:");
		scaleLb.setVisible(false);
		scaleTxt.setVisible(false);
		idlTemp.setIdlKind(IDLKind.WSTRING_LITERAL);
	}

	/** Auto-generated event handler method */
	protected void stringBtnWidgetSelected(SelectionEvent evt){
		wstringBtn.setSelection(false);
		fixedBtn.setSelection(false);
		arrayBtn.setSelection(false);
		sequenceBtn.setSelection(false);
		BoundDigitLb.setText("Bound:");
		scaleLb.setVisible(false);
		scaleTxt.setVisible(false);
		idlTemp.setIdlKind(IDLKind.STRING_LITERAL);
	}

	/** Auto-generated event handler method */
	protected void fixedBtnWidgetSelected(SelectionEvent evt){
		wstringBtn.setSelection(false);
		stringBtn.setSelection(false);
		arrayBtn.setSelection(false);
		sequenceBtn.setSelection(false);
		BoundDigitLb.setText("Digits:");
		scaleLb.setVisible(true);
		scaleTxt.setVisible(true);
		idlTemp.setIdlKind(IDLKind.FIXED_LITERAL);
	}

	/** Auto-generated event handler method */
	protected void arrayBtnWidgetSelected(SelectionEvent evt){
		wstringBtn.setSelection(false);
		stringBtn.setSelection(false);
		fixedBtn.setSelection(false);
		sequenceBtn.setSelection(false);
		BoundDigitLb.setText("Bound:");
		scaleLb.setVisible(false);
		scaleTxt.setVisible(false);
		idlTemp.setIdlKind(IDLKind.ARRAY_LITERAL);
	}

	/** Auto-generated event handler method */
	protected void sequenceBtnWidgetSelected(SelectionEvent evt){
		wstringBtn.setSelection(false);
		stringBtn.setSelection(false);
		fixedBtn.setSelection(false);
		arrayBtn.setSelection(false);
		BoundDigitLb.setText("Bound:");
		scaleLb.setVisible(false);
		scaleTxt.setVisible(false);
		idlTemp.setIdlKind(IDLKind.SEQUENCE_LITERAL);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			 state=true;
			    switch(idlTemp.getIdlKind().getValue()){
			    case IDLKind.WSTRING:
			    case IDLKind.ARRAY:
			    case IDLKind.SEQUENCE:
			    case IDLKind.STRING:
		    		idlTemp.setBound((new Integer(boundDigitTxt.getText())).intValue());
		    		break;
			    case IDLKind.FIXED:
		    		idlTemp.setDigits((new Integer(boundDigitTxt.getText())).intValue());
		    		idlTemp.setScale((new Integer(scaleTxt.getText())).intValue());
		    		break;

			    }
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
