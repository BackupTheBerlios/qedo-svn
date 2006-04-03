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
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import CCMModel.ParameterMode;
import ccm.CCMConstants;
import ccm.model.template.IDLKind;
import ccm.model.template.ParameterTemplate;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class AddParameterDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Button idlBtn;
	private Combo idlTypeCmb;
	private Label idlTypeLb;
	//private Label label1;
	private Combo dirCm;
	private Label dirLb;
	private Text nameTxt;
	private Label nameLb;
	private Button cancel;
	private Button enter;
	private Composite composite3;
	private Composite composite2;
	//private Composite composite1;
	private Shell dialogShell;
	
	private boolean state=false;
	private ParameterTemplate parameter;
	private java.util.List idlTList=new LinkedList();
	private String text;
	

	public AddParameterDialog(Shell parent, int style,String text) {
		super(parent, style);
		this.text=text;
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
			dirCm = new Combo(composite2,SWT.READ_ONLY);
			dirLb = new Label(composite2,SWT.NULL);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText(text);
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(304,138));
	
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			//final Font idlBtnfont2 = new Font(Display.getDefault(),"Tahoma",8,1);
			//final Font idlBtnfont3 = new Font(Display.getDefault(),"Tahoma",7,1);
			//final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 296;
			composite2LData.heightHint = 90;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(296,90));
	
			FormData idlBtnLData = new FormData();
			idlBtnLData.height = 21;
			idlBtnLData.width = 30;
			idlBtnLData.left =  new FormAttachment(886, 1000, 0);
			idlBtnLData.right =  new FormAttachment(988, 1000, 0);
			idlBtnLData.top =  new FormAttachment(276, 1000, 0);
			idlBtnLData.bottom =  new FormAttachment(526, 1000, 0);
			idlBtn.setLayoutData(idlBtnLData);
			idlBtn.setText("....");
			idlBtn.setSize(new org.eclipse.swt.graphics.Point(30,21));
			
			idlBtn.setFont(idlBtnfont);
			idlBtn.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					idlBtnMouseDown(evt);
				}
			});
	
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 24;
			idlTypeCmbLData.width = 173;
			idlTypeCmbLData.left =  new FormAttachment(238, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(883, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(276, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(505, 1000, 0);
			idlTypeCmb.setLayoutData(idlTypeCmbLData);
			idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(173,24));
			//final Font idlTypeCmbfont = new Font(Display.getDefault(),"Tahoma",10,0);
			idlTypeCmb.setFont(idlBtnfont);
			idlTypeCmb.addSelectionListener( new SelectionAdapter() {
				public void widgetSelected(SelectionEvent evt) {
					idlTypeCmbWidgetSelected(evt);
				}
			});
	
			FormData idlTypeLbLData = new FormData();
			idlTypeLbLData.height = 20;
			idlTypeLbLData.width = 60;
			idlTypeLbLData.left =  new FormAttachment(17, 1000, 0);
			idlTypeLbLData.right =  new FormAttachment(221, 1000, 0);
			idlTypeLbLData.top =  new FormAttachment(305, 1000, 0);
			idlTypeLbLData.bottom =  new FormAttachment(495, 1000, 0);
			idlTypeLb.setLayoutData(idlTypeLbLData);
			idlTypeLb.setText("Idl Type:");
			idlTypeLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			idlTypeLb.setFont(idlBtnfont);
	
			FormData dirCmLData = new FormData();
			dirCmLData.height = 27;
			dirCmLData.width = 94;
			dirCmLData.left =  new FormAttachment(238, 1000, 0);
			dirCmLData.right =  new FormAttachment(616, 1000, 0);
			dirCmLData.top =  new FormAttachment(582, 1000, 0);
			dirCmLData.bottom =  new FormAttachment(811, 1000, 0);
			dirCm.setLayoutData(dirCmLData);
			dirCm.setSize(new org.eclipse.swt.graphics.Point(94,27));
			dirCm.setFont(idlBtnfont);
	
			FormData dirLbLData = new FormData();
			dirLbLData.height = 20;
			dirLbLData.width = 60;
			dirLbLData.left =  new FormAttachment(18, 1000, 0);
			dirLbLData.right =  new FormAttachment(234, 1000, 0);
			dirLbLData.top =  new FormAttachment(600, 1000, 0);
			dirLbLData.bottom =  new FormAttachment(793, 1000, 0);
			dirLb.setLayoutData(dirLbLData);
			dirLb.setText("Direction:");
			dirLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			dirLb.setFont(idlBtnfont);
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 212;
			nameTxtLData.left =  new FormAttachment(238, 1000, 0);
			nameTxtLData.right =  new FormAttachment(988, 1000, 0);
			nameTxtLData.top =  new FormAttachment(28, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(260, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(idlBtnfont);
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(212,13));
			nameTxt.setFocus();
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 20;
			nameLbLData.width = 60;
			nameLbLData.left =  new FormAttachment(18, 1000, 0);
			nameLbLData.right =  new FormAttachment(221, 1000, 0);
			nameLbLData.top =  new FormAttachment(41, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(252, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Name:");
			nameLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
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
			composite3LData.widthHint = 297;
			composite3LData.heightHint = 39;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(297,39));
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 75;
			cancelLData.left =  new FormAttachment(715, 1000, 0);
			cancelLData.right =  new FormAttachment(954, 1000, 0);
			cancelLData.top =  new FormAttachment( 6, 1000, 0);
			cancelLData.bottom =  new FormAttachment(733, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(75,23));
			cancel.setFont(idlBtnfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseUp(MouseEvent evt) {
					cancelMouseUp(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 23;
			enterLData.width = 75;
			enterLData.left =  new FormAttachment(453, 1000, 0);
			enterLData.right =  new FormAttachment(681, 1000, 0);
			enterLData.top =  new FormAttachment( 6, 1000, 0);
			enterLData.bottom =  new FormAttachment(733, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(75,23));
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
				//	label1font.dispose();
					idlBtnfont.dispose();
					//idlTypeCmbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 304,138);
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
	    nameTxt.setText(parameter.getIdentifier());
	    dirCm.add("IN");
	    dirCm.add("OUT");
	    dirCm.add("INOUT");
	    dirCm.select(parameter.getMode().getValue());
	    Iterator it=idlTList.iterator();
	    while(it.hasNext()){
	        String idl=(String) it.next();
	        idlTypeCmb.add(idl.toString());
	    }
	    CCMConstants.setIDL(parameter.getIdlType(),idlTypeCmb);
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
			AddParameterDialog inst = new AddParameterDialog(shell, SWT.NULL,"");
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    parameter.setIdentifier(nameTxt.getText());
	    parameter.setMode(ParameterMode.get(dirCm.getSelectionIndex()));
	    state=true;
		dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
		dialogShell.close();
	}
    /**
     * @return Returns the parameter.
     */
    public ParameterTemplate getParameter() {
        return parameter;
    }
    /**
     * @param parameter The parameter to set.
     */
    public void setParameter(ParameterTemplate parameter) {
        this.parameter = parameter;
    }
    
    /**
     * @param idlTList The idlTList to set.
     */
    public void setIdlTList(java.util.List idlTList) {
        this.idlTList.clear();
        this.idlTList.addAll(idlTList);
    }
    /**
     * @return Returns the state.
     */
    public boolean isState() {
        return state;
    }


	/** Auto-generated event handler method */
	protected void idlBtnMouseDown(MouseEvent evt){
	    SetOIDLTypeDialog d=new SetOIDLTypeDialog(this.dialogShell,0);
	    d.setIdlTemp(parameter.getIdlType());
	    d.open();
	    if(!d.isState())return;
	    if(parameter.getIdlType().getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    parameter.setIdlType(d.getIdlTemp());
	    CCMConstants.setIDL(parameter.getIdlType(),idlTypeCmb);
	}

	/** Auto-generated event handler method */
	protected void idlTypeCmbWidgetSelected(SelectionEvent evt){
	    if(parameter.getIdlType().getIdlKind().getValue()!=IDLKind.IDL){
	        idlTypeCmb.remove(idlTypeCmb.getItemCount()-1);
	    }
	    parameter.getIdlType().setIdlKind(IDLKind.IDL_LITERAL);
	    parameter.getIdlType().setIndexOfIDLType(idlTypeCmb.getSelectionIndex());
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			parameter.setIdentifier(nameTxt.getText());
		    parameter.setMode(ParameterMode.get(dirCm.getSelectionIndex()));
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
