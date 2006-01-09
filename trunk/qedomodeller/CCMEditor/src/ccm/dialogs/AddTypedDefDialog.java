package ccm.dialogs;

import java.util.Hashtable;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
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
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

/**
* This code was generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a
* for-profit company or business) then you should purchase
* a license - please visit www.cloudgarden.com for details.
*/
public class AddTypedDefDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
	private Combo idlTypes;
	private Label typedByLb;
	//private Label label2;
	//private Label label1;
	private Label isReadLb;
	private Button isReadOnly;
	private Text nameTxt;
	private Label nameLB;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Composite composite2;
	 
	private Shell dialogShell;
	
	private boolean state=false;
	private String name="";
	private boolean readonly=false;
	private String dialogContext="";
	private String dialogType="";
	private Hashtable idlTypeTable;

	public AddTypedDefDialog(Shell parent, int style) {
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
			idlTypes = new Combo(composite2,SWT.NULL);
			typedByLb = new Label(composite2,SWT.NULL);
			isReadLb = new Label(composite2,SWT.NULL);
			isReadOnly = new Button(composite2,SWT.CHECK| SWT.LEFT);
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLB = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("Add Attribute");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(420,133));
	  
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 420;
			composite2LData.heightHint = 88;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(420,88));
	
			FormData idlTypesLData = new FormData();
			idlTypesLData.height = 27;
			idlTypesLData.width = 259;
			idlTypesLData.left =  new FormAttachment(190, 1000, 0);
			idlTypesLData.right =  new FormAttachment(976, 1000, 0);
			idlTypesLData.top =  new FormAttachment(330, 1000, 0);
			idlTypesLData.bottom =  new FormAttachment(470, 1000, 0);
			idlTypes.setLayoutData(idlTypesLData);
			idlTypes.setText("Combo1:");
			idlTypes.setSize(new org.eclipse.swt.graphics.Point(259,27));
			final Font idlTypesfont = new Font(Display.getDefault(),"Tahoma",7,1);
			idlTypes.setFont(idlTypesfont);
	
			FormData typedByLbLData = new FormData();
			typedByLbLData.height = 25;
			typedByLbLData.width = 60;
			typedByLbLData.left =  new FormAttachment(21, 1000, 0);
			typedByLbLData.right =  new FormAttachment(190, 1000, 0);
			typedByLbLData.top =  new FormAttachment(360, 1000, 0);
			typedByLbLData.bottom =  new FormAttachment(685, 1000, 0);
			typedByLb.setLayoutData(typedByLbLData);
			typedByLb.setText("Typed By:");
			typedByLb.setSize(new org.eclipse.swt.graphics.Point(60,25));
			final Font typedByLbfont = new Font(Display.getDefault(),"Tahoma",8,1);
			typedByLb.setFont(typedByLbfont);
	
			FormData isReadLbLData = new FormData();
			isReadLbLData.height = 25;
			isReadLbLData.width = 77;
			isReadLbLData.left =  new FormAttachment(260, 1000, 0);
			isReadLbLData.right =  new FormAttachment(470, 1000, 0);
			isReadLbLData.top =  new FormAttachment(670, 1000, 0);
			isReadLbLData.bottom =  new FormAttachment(935, 1000, 0);
			isReadLb.setLayoutData(isReadLbLData);
			isReadLb.setText("is readonly");
			isReadLb.setSize(new org.eclipse.swt.graphics.Point(77,25));
			isReadLb.setFont(typedByLbfont);
	
			FormData isReadOnlyLData = new FormData();
			isReadOnlyLData.height = 22;
			isReadOnlyLData.width = 17;
			isReadOnlyLData.left =  new FormAttachment(190, 1000, 0);
			isReadOnlyLData.right =  new FormAttachment(385, 1000, 0);
			isReadOnlyLData.top =  new FormAttachment(607, 1000, 0);
			isReadOnlyLData.bottom =  new FormAttachment(900, 1000, 0);
			isReadOnly.setLayoutData(isReadOnlyLData);
			//isReadOnly.setAlignment(SWT.RIGHT);
			isReadOnly.setSize(new org.eclipse.swt.graphics.Point(17,22));
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 18;
			nameTxtLData.width = 332;
			nameTxtLData.left =  new FormAttachment(190, 1000, 0);
			nameTxtLData.right =  new FormAttachment(976, 1000, 0);
			nameTxtLData.top =  new FormAttachment(57, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(300, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
			nameTxt.setFont(idlTypesfont);
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(332,18));
			nameTxt.setFocus();
			
			FormData nameLBLData = new FormData();
			nameLBLData.height = 25;
			nameLBLData.width = 45;
			nameLBLData.left =  new FormAttachment(21, 1000, 0);
			nameLBLData.right =  new FormAttachment(190, 1000, 0);
			nameLBLData.top =  new FormAttachment(72, 1000, 0);
			nameLBLData.bottom =  new FormAttachment(239, 1000, 0);
			nameLB.setLayoutData(nameLBLData);
			nameLB.setText("Name:");
			nameLB.setSize(new org.eclipse.swt.graphics.Point(45,25));
			nameLB.setFont(typedByLbfont);
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 416;
			composite3LData.heightHint = 44;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(416,44));
	
			FormData enterLData = new FormData();
			enterLData.height = 25;
			enterLData.width = 73;
			enterLData.left =  new FormAttachment(560, 1000, 0);
			enterLData.right =  new FormAttachment(743, 1000, 0);
			enterLData.top =  new FormAttachment(  0, 1000, 0);
			enterLData.bottom =  new FormAttachment(606, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(73,25));
			enter.setFont(typedByLbfont);
			enter.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					enterMouseDown(evt);
				}
			});
	
			FormData cancelLData = new FormData();
			cancelLData.height = 25;
			cancelLData.width = 73;
			cancelLData.left =  new FormAttachment(794, 1000, 0);
			cancelLData.right =  new FormAttachment(978, 1000, 0);
			cancelLData.top =  new FormAttachment( 0, 1000, 0);
			cancelLData.bottom =  new FormAttachment(606, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(73,25));
			cancel.setFont(typedByLbfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					cancelMouseDown(evt);
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
					 
					idlTypesfont.dispose();
					typedByLbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 420,133);
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
		dialogShell.setText(dialogContext);
	 
		idlTypes.removeAll();
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
			AddTypedDefDialog inst = new AddTypedDefDialog(shell, SWT.NULL);
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
		String str=nameTxt.getText().trim();
		if(str.length()==0)return;
		state=true;
		name=str;
		readonly=isReadOnly.getSelection();
		dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void cancelMouseDown(MouseEvent evt){
		dialogShell.close();
	}
	/**
	 * @return Returns the name.
	 */
	public String getName() {
		return name;
	}
	/**
	 * @return Returns the readonly.
	 */
	public boolean isReadonly() {
		return readonly;
	}
	/**
	 * @return Returns the state.
	 */
	public boolean isState() {
		return state;
	}
	/**
	 * @param dialogContext The dialogContext to set.
	 */
	public void setDialogContext(String dialogContext) {
		this.dialogContext = dialogContext;
	}
	/**
	 * @param dialogType The dialogType to set.
	 */
	public void setDialogType(String dialogType) {
		this.dialogType = dialogType;
	}
	/**
	 * @param idlTypeTable The idlTypeTable to set.
	 */
	public void setIdlTypeTable(Hashtable idlTypeTable) {
		this.idlTypeTable = idlTypeTable;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			String str=nameTxt.getText().trim();
			if(str.length()==0)return;
			state=true;
			name=str;
			readonly=isReadOnly.getSelection();
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
