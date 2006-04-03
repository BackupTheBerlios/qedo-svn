package ccm.dialogs;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
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
public class AddMembersToEnumDialog extends org.eclipse.swt.widgets.Dialog  implements KeyListener{
	private Shell dialogShell;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	private Label nameLb;
	private Text nameTxt;
	private Composite composite2;
	//private Label label1;
	//private Composite composite1;
	private String text;
	private String member=""; 
	private boolean state=false;
	
	public AddMembersToEnumDialog(Shell parent, int style,String text) {
		super(parent, style);
		this.text=text;
	}

	/** Auto-generated event handler method */
	protected void cancelMouseUp(MouseEvent evt){
	    dialogShell.close();
	}

	/** Auto-generated event handler method */
	protected void enterMouseDown(MouseEvent evt){
	    member=nameTxt.getText();
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
			nameTxt = new Text(composite2,SWT.BORDER);
			nameLb = new Label(composite2,SWT.NULL);
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText(text);
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(304,88));
	
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			final Font nameLbfont = new Font(Display.getDefault(),"Tahoma",8,1);
			//final Font label1font = new Font(Display.getDefault(),"Tahoma",12,1);
			 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 296;
			composite2LData.heightHint = 40;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(296,40));
	
			FormData nameTxtLData = new FormData();
			nameTxtLData.height = 21;
			nameTxtLData.width = 212;
			nameTxtLData.left =  new FormAttachment(228, 1000, 0);
			nameTxtLData.right =  new FormAttachment(988, 1000, 0);
			nameTxtLData.top =  new FormAttachment(225, 1000, 0);
			nameTxtLData.bottom =  new FormAttachment(830, 1000, 0);
			nameTxt.setLayoutData(nameTxtLData);
		//	final Font nameTxtfont = new Font(Display.getDefault(),"Tahoma",10,0);
			nameTxt.setFont(nameLbfont);
			nameTxt.setSize(new org.eclipse.swt.graphics.Point(212,13));
			nameTxt.setFocus();
	
			FormData nameLbLData = new FormData();
			nameLbLData.height = 20;
			nameLbLData.width = 60;
			nameLbLData.left =  new FormAttachment(18, 1000, 0);
			nameLbLData.right =  new FormAttachment(221, 1000, 0);
			nameLbLData.top =  new FormAttachment(265, 1000, 0);
			nameLbLData.bottom =  new FormAttachment(700, 1000, 0);
			nameLb.setLayoutData(nameLbLData);
			nameLb.setText("Name:");
			nameLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
			
			nameLb.setFont(nameLbfont);
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
			cancelLData.height = 18;
			cancelLData.width = 75;
			cancelLData.left =  new FormAttachment(735, 1000, 0);
			cancelLData.right =  new FormAttachment(954, 1000, 0);
			cancelLData.top =  new FormAttachment(6, 1000, 0);
			cancelLData.bottom =  new FormAttachment(733, 1000, 0);
			cancel.setLayoutData(cancelLData);
			cancel.setText("CANCEL");
			cancel.setSize(new org.eclipse.swt.graphics.Point(75,18));
			cancel.setFont(nameLbfont);
			cancel.addMouseListener( new MouseAdapter() {
				public void mouseUp(MouseEvent evt) {
					cancelMouseUp(evt);
				}
			});
	
			FormData enterLData = new FormData();
			enterLData.height = 18;
			enterLData.width = 75;
			enterLData.left =  new FormAttachment(443, 1000, 0);
			enterLData.right =  new FormAttachment(671, 1000, 0);
			enterLData.top =  new FormAttachment(6, 1000, 0);
			enterLData.bottom =  new FormAttachment(733, 1000, 0);
			enter.setLayoutData(enterLData);
			enter.setText("ENTER");
			enter.setSize(new org.eclipse.swt.graphics.Point(75,18));
			enter.setFont(nameLbfont);
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
					//nameTxtfont.dispose();
					nameLbfont.dispose();
				}
			});
			Rectangle bounds = dialogShell.computeTrim(0, 0, 304,88);
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
	    nameTxt.setText(member);
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
			AddMembersToEnumDialog inst = new AddMembersToEnumDialog(shell, SWT.NULL,"");
			inst.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
    /**
     * @return Returns the member.
     */
    public String getMember() {
        return member;
    }
    /**
     * @param member The member to set.
     */
    public void setMember(String member) {
        this.member = member;
    }
    /**
     * @return Returns the state.
     */
    public boolean isState() {
        return state;
    }

	/* (non-Javadoc)
	 * @see org.eclipse.swt.events.KeyListener#keyPressed(org.eclipse.swt.events.KeyEvent)
	 */
	public void keyPressed(KeyEvent e) {
		if(e.character == SWT.CR){
			member=nameTxt.getText();
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
