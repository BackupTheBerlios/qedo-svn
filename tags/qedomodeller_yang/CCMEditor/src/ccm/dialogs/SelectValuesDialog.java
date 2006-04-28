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
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Shell;

import CCMModel.Contained;

/**
 * @autor siegercn
*/
public class SelectValuesDialog extends org.eclipse.swt.widgets.Dialog implements KeyListener{
 
	private Combo idlTypeCmb;
	private Label label2;
	private Button enter;
	private Button cancel;
	private Composite composite3;
	//private Label label1;
	private Button removeP; 
	//private Label contextLb;
	private List par;	 
	private Composite composite2;
	//private Composite composite1;
	private Shell dialogShell;
	private boolean state=false;
	private String discription="";
	private java.util.List values=new LinkedList();
	private java.util.List allvalues=new LinkedList();
	 
//	private java.util.List newvalues=new LinkedList();
	//private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
	//private String absName="";
	
	public SelectValuesDialog(Shell parent, int style) {
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
			 
			idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
			label2 = new Label(composite2,SWT.NULL);
			removeP = new Button(composite2,SWT.PUSH| SWT.CENTER);
			 
			//contextLb = new Label(composite2,SWT.NULL);
			 
			par = new List(composite2,SWT.BORDER|SWT.V_SCROLL);
			 
			composite3 = new Composite(dialogShell,SWT.NULL);
			cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
			enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
	
			dialogShell.setText("");
			dialogShell.setSize(new org.eclipse.swt.graphics.Point(300,180));
	
			 
			final Color composite1background = new Color(Display.getDefault(),255,255,255);
			 
	
		 
	
			GridData composite2LData = new GridData();
			composite2LData.verticalAlignment = GridData.CENTER;
			composite2LData.horizontalAlignment = GridData.BEGINNING;
			composite2LData.widthHint = 290;
			composite2LData.heightHint = 130;
			composite2LData.horizontalIndent = 0;
			composite2LData.horizontalSpan = 1;
			composite2LData.verticalSpan = 1;
			composite2LData.grabExcessHorizontalSpace = false;
			composite2LData.grabExcessVerticalSpace = false;
			composite2.setLayoutData(composite2LData);
			composite2.setSize(new org.eclipse.swt.graphics.Point(290,130));
	
			 
			final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
			 
			final Font repositoryIDTxtfont = new Font(Display.getDefault(),"Tahoma",8,0);
		 
		 
	
			FormData idlTypeCmbLData = new FormData();
			idlTypeCmbLData.height = 20;
			idlTypeCmbLData.width = 180;
			idlTypeCmbLData.left =  new FormAttachment(377, 1000, 0);
			idlTypeCmbLData.right =  new FormAttachment(998, 1000, 0);
			idlTypeCmbLData.top =  new FormAttachment(50, 1000, 0);
			idlTypeCmbLData.bottom =  new FormAttachment(270, 1000, 0);
			idlTypeCmb.setLayoutData(idlTypeCmbLData);
			idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(180,20));
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
			label2LData.right =  new FormAttachment(361, 1000, 0);
			label2LData.top =  new FormAttachment(58, 1000, 0);
			label2LData.bottom =  new FormAttachment(278, 1000, 0);
			label2.setLayoutData(label2LData);
			label2.setText("Select Value: ");
			label2.setSize(new org.eclipse.swt.graphics.Point(90,20));
			label2.setFont(idlBtnfont);
	
			FormData removePLData = new FormData();
			removePLData.height = 18;
			removePLData.width = 70;
			removePLData.left =  new FormAttachment(13, 1000, 0);
			removePLData.right =  new FormAttachment(361, 1000, 0);
			removePLData.top =  new FormAttachment(320, 1000, 0);
			removePLData.bottom =  new FormAttachment(495, 1000, 0);
			removeP.setLayoutData(removePLData);
			removeP.setText("REMOVE");
			removeP.setSize(new org.eclipse.swt.graphics.Point(70,18));
			final Font removePfont = new Font(Display.getDefault(),"Tahoma",8,1);
			removeP.setFont(removePfont);
			removeP.addMouseListener( new MouseAdapter() {
				public void mouseDown(MouseEvent evt) {
					removePMouseDown(evt);
				}
			});
	 
	
			FormData contextLbLData = new FormData();
			contextLbLData.height = 20;
			contextLbLData.width = 90;
			contextLbLData.left =  new FormAttachment(13, 1000, 0);
			contextLbLData.right =  new FormAttachment(261, 1000, 0);
			contextLbLData.top =  new FormAttachment(325, 1000, 0);
			contextLbLData.bottom =  new FormAttachment(384, 1000, 0);
			//contextLb.setLayoutData(contextLbLData);
			//contextLb.setText("Context:");
			//contextLb.setSize(new org.eclipse.swt.graphics.Point(90,20));
			//contextLb.setFont(idlBtnfont);
	
		 
	 
	
			FormData parLData = new FormData();
			parLData.height = 150;
			parLData.width = 213;
			parLData.left =  new FormAttachment(377, 1000, 0);
			parLData.right =  new FormAttachment(998, 1000, 0);
			parLData.top =  new FormAttachment(290, 1000, 0);
			parLData.bottom =  new FormAttachment(990, 1000, 0);
			par.setLayoutData(parLData);
			par.setFont(repositoryIDTxtfont);
			par.setSize(new org.eclipse.swt.graphics.Point(213,150));
	 
			FormLayout composite2Layout = new FormLayout();
			composite2.setLayout(composite2Layout);
			composite2Layout.marginWidth = 0;
			composite2Layout.marginHeight = 0;
			composite2Layout.spacing = 0;
			composite2.layout();
	
			GridData composite3LData = new GridData();
			composite3LData.verticalAlignment = GridData.CENTER;
			composite3LData.horizontalAlignment = GridData.BEGINNING;
			composite3LData.widthHint = 290;
			composite3LData.heightHint = 34;
			composite3LData.horizontalIndent = 0;
			composite3LData.horizontalSpan = 1;
			composite3LData.verticalSpan = 1;
			composite3LData.grabExcessHorizontalSpace = false;
			composite3LData.grabExcessVerticalSpace = false;
			composite3.setLayoutData(composite3LData);
			composite3.setSize(new org.eclipse.swt.graphics.Point(290,34));
			composite3.setFont(idlBtnfont);
	
			FormData cancelLData = new FormData();
			cancelLData.height = 23;
			cancelLData.width = 77;
			cancelLData.left =  new FormAttachment(725, 1000, 0);
			cancelLData.right =  new FormAttachment(998, 1000, 0);
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
			enterLData.left =  new FormAttachment(377, 1000, 0);
			enterLData.right =  new FormAttachment(645, 1000, 0);
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
			Rectangle bounds = dialogShell.computeTrim(0, 0, 300,180);
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
	    
	    Iterator it=values.iterator();
	    while(it.hasNext()){
	        Contained c=(Contained) it.next();
	        par.add(c.getIdentifier());
	    }
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        
	    }else{
	        par.select(0);
	    }
	    it=allvalues.iterator();
	    while(it.hasNext()){
	        Contained c2=(Contained) it.next();
	        idlTypeCmb.add(c2.getIdentifier());
	    }
	    dialogShell.setText(discription);
	}

	 public void setDiscription(String discription) {
        this.discription = discription;
    }
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
			SelectValuesDialog inst = new SelectValuesDialog(shell, SWT.NULL);
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

 
	protected void cancelMouseUp(MouseEvent evt){
		dialogShell.close();
	}

	 
	protected void removePMouseDown(MouseEvent evt){
	    deleteParameter();
	}
	 
 
	protected void idlTypeCmbWidgetSelected(SelectionEvent evt){
		Contained c= (Contained)allvalues.get(idlTypeCmb.getSelectionIndex());
		if (!values.contains(c))
		   values.add(c);
		par.add(c.getIdentifier());
		 
	}
	private void deleteParameter(){
	    int index=par.getSelectionIndex();
	    if(index==-1)return;
	    values.remove(index);
	    par.remove(index);
	    if(par.getItemCount()==0){
	        removeP.setEnabled(false);
	        
	    }
	}
	
   
    /**
     * @return Returns the list.
     */
    public java.util.List getValues() {
        return values;
    }
    /**
     * @param list The list to set.
     */
    public void setValues(java.util.List list) {
        this.values.clear();
        this.values.addAll(list);
    }
    /**
     * @param idlTList The idlTList to set.
     */
    public void setAllValues(java.util.List idlTList) {
        this.allvalues.clear();
        this.allvalues.addAll(idlTList);
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

 