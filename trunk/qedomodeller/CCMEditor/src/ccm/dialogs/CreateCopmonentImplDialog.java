package ccm.dialogs;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.SWT;

import CCMModel.ComponentDef;
import CCMModel.ModuleDef;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class CreateCopmonentImplDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	 
	private Combo copmCmb;
	private Label comLb;
	private Text nameTxt;
	private Label nameLb;
	private Button cancel;
	private Button enter;
	private Composite composite3;
	private Composite composite2;
	 
	private Shell dialogShell;
	
	private boolean state =false;
	private String name="";
	private ComponentDef component=null;
	private ModuleDef module=null;
	private List componentDefList;

	public CreateCopmonentImplDialog(Shell parent, int style) {
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
			copmCmb = new Combo(composite2,SWT.NULL);
			comLb = new Label(composite2,SWT.NULL);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(375,117));
			dialogShell.setText("Add Component");

			GridData composite2LData = new GridData();
			composite2LData.widthHint = 363;
			composite2LData.heightHint = 70;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(363,70));
	
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
			final Font comLbfont = new Font(Display.getDefault(),"Tahoma",8,1);
			comLb.setFont(comLbfont);
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 13;
			nameTxtLData.width = 287;
			nameTxtLData.left =  new FormAttachment(334, 1000, 0);
			nameTxtLData.right =  new FormAttachment(992, 1000, 0);
			nameTxtLData.top =  new FormAttachment(48, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(335, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(copmCmbfont);
			nameTxt.setFocus();
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(287,13));
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 18;
			nameLbLData.width = 41;
			nameLbLData.left =  new FormAttachment(21, 1000, 0);
			nameLbLData.right =  new FormAttachment(137, 1000, 0);
			nameLbLData.top =  new FormAttachment(67, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(299, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Name:");
			nameLb.setSize(new org.eclipse.swt.graphics.Point(41,18));
			nameLb.setFont(comLbfont);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.widthHint = 355;
			composite3LData.heightHint = 44;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(355,44));
	
			FormData cancelLData = new FormData();
			cancelLData.height = 20;
			cancelLData.width = 70;
			cancelLData.left =  new FormAttachment(787, 1000, 0);
			cancelLData.right =  new FormAttachment(976, 1000, 0);
			cancelLData.top =  new FormAttachment( 1, 1000, 0);
			cancelLData.bottom =  new FormAttachment(629, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(60,20));
			cancel.setFont(comLbfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 20;
			enterLData.width = 70;
			enterLData.left =  new FormAttachment(562, 1000, 0);
			enterLData.right =  new FormAttachment(741, 1000, 0);
			enterLData.top =  new FormAttachment( 1, 1000, 0);
			enterLData.bottom =  new FormAttachment(629, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(60,20));
			enter.setFont(comLbfont);
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
					 
					copmCmbfont.dispose();
					comLbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 375,117);
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
		copmCmb.removeAll();
		componentDefList=new LinkedList();
	 	Iterator it=module.getContents().iterator();
	 	while(it.hasNext()){
			Object o=it.next();
			if(o instanceof ComponentDef){
				copmCmb.add(((ComponentDef)o).getIdentifier());
				componentDefList.add(o);
			}
		}
		copmCmb.select(0);
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
			CreateCopmonentImplDialog inst = new CreateCopmonentImplDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
		dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
		name=nameTxt.getText();
		component=(ComponentDef) componentDefList.get(copmCmb.getSelectionIndex());
		dialogShell.close();
		state=true;
		
	}
	/**
	 * @return Returns the component.
	 */
	public ComponentDef getComponent() {
		return component;
	}
	/**
	 * @return Returns the name.
	 */
	public String getName() {
		return name;
	}
	/**
	 * @return Returns the state.
	 */
	public boolean isState() {
		return state;
	}
	/**
	 * @param module The module to set.
	 */
	public void setModule(ModuleDef module) {
		this.module = module;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
		name=nameTxt.getText();
		component=(ComponentDef) componentDefList.get(copmCmb.getSelectionIndex());
		dialogShell.close();
		state=true;}
		
		
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyReleased(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
}
