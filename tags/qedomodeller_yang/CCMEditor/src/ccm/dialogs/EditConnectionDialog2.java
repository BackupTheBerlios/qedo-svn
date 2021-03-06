package ccm.dialogs;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
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
import org.eclipse.swt.widgets.Text;

import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.CCMInstantiation;
import CCMModel.CCMModelFactory;
import CCMModel.ComponentFeature;
import CCMModel.ComponentInstantiation;
import CCMModel.ConnectionEnd;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.EmitsDef;
import CCMModel.EventDef;
import CCMModel.FinderServiceKind;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;
import CCMModel.MediaType;
import CCMModel.ProcessCollocation;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.SourceDef;
import CCMModel.StreamProtDef;
import CCMModel.UsesDef;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
*@author Siegercn
*/
public class EditConnectionDialog2 extends org.eclipse.swt.widgets.Dialog {
		private CCMModelFactory factory=CCMModelManager.getFactory();
		private Combo objectrefTxt;
		private Label objectRefLb;
		private Combo constValueTxt;
		private Label constValueLb;
		private Shell dialogShell;
		private Button enter;
		private Button cancel;
		private Composite composite3;
		private Label idLb;
		private Label repositoryIdLb;
		private Label versionLb;
		private Text identifierTxt;
		private Text versionTxt;
		private Text repositoryIdTxt;
		private Label idlTypeLb;
		private Combo idlTypeCmb;
		private Label implLb;
		private Combo implCmb;
		private List sources= new ArrayList();
		private CCMInstantiation source;
		private List targets= new ArrayList();
		private ComponentInstantiation target;
		private List sourceFeatures= new ArrayList();
		private ComponentFeature sourceFeature;
		private List targetFeatures= new ArrayList();
		private ComponentFeature targetFeature;
	 	private FinderServiceKind service;
		private FinderServiceKind[] services={FinderServiceKind.HOMEFINDER_LITERAL,FinderServiceKind.NAMING_LITERAL,FinderServiceKind.TRADING_LITERAL,FinderServiceKind.UNDEFINED_LITERAL};
		private Composite composite2;
		 
	    private int cardinality;
		private String identifier="";
		private String repositoryId="";
		private String version="";
		private boolean state=false;
		private String constValue;
		private java.util.List idlTList=new LinkedList();
		private IDLTemplate idlTemp=new IDLTemplate(IDLKind.IDL_LITERAL);
	    private String absName;
		private String objectRef;
		private String regName;
	    private Shell parent ;
		private Assembly ass;
		private AssemblyConnection aConnection=null;
		
		public EditConnectionDialog2(Shell parent, int style) {
			super(parent, style);
			this.parent=parent;
		}

		/** Auto-generated event handler method */
		protected void cancelMouseDown(MouseEvent evt){
		    dialogShell.close();
		}

		/** Auto-generated event handler method */
		protected void enterMouseDown(MouseEvent evt){
			aConnection=factory.createAssemblyConnection();
    	 	ConnectionEnd targetEnd=factory.createConnectionEnd();
    	 	ConnectionEnd sourceEnd=factory.createConnectionEnd();
    	 	targetEnd.setInstance(target);
    	    targetEnd.setFeature(targetFeature);
		    identifier=identifierTxt.getText();
		    version=versionTxt.getText();
		   // constValue=constValueTxt.getText();
		    aConnection.setIdentifier(identifier);
			aConnection.setVersion(version);
			aConnection.setRepositoryId(this.getRepositoryId());
		    
		    if(targetFeature instanceof UsesDef){
		    	 UsesDef receptacel=(UsesDef)targetFeature;
		    	 InterfaceDef itf=receptacel.getInterface();
		    	 if(itf==null){
		    	 	aConnection=null;
		    	 	 invalidConnection();
		    	 	 return;
		    	 }
		    	 if(source instanceof HomeInstantiation 
		    	 		&&((HomeInstantiation)source).getDeploymentUnit()!=null
						&&((HomeInstantiation)source).getDeploymentUnit().getComposition()!=null
						&&((HomeInstantiation)source).getDeploymentUnit().getComposition().getHomeImpl()!=null
						&&((HomeInstantiation)source).getDeploymentUnit().getComposition().getHomeImpl().getHome()!=null
						&&((HomeInstantiation)source).getDeploymentUnit().getComposition().getHomeImpl().getHome().getHomeSupports_itf()!=null
		    	 		&&((HomeInstantiation)source).getDeploymentUnit().getComposition().getHomeImpl().getHome().getHomeSupports_itf().contains(itf))
		    	 {
		    	 	
		    	 	
		    	    
		    	  
		    	    sourceEnd.setInstance(source);
		    	    //sourceEnd.setFeature(targetFeature);
		    	    
		    	    aConnection.getContents().add(targetEnd);
		    	    aConnection.getContents().add(sourceEnd);
		    	    aConnection.setSource(sourceEnd);
		            aConnection.setTarget(targetEnd);
		            state=true;
		            dialogShell.close();
		            return;
		    	 }
		    	 if(source instanceof ComponentInstantiation &&
		    	 		 sourceFeature instanceof ProvidesDef &&((ProvidesDef)sourceFeature).getInterface().equals(itf))
						 
		    	 				//(ComponentInstantiation)source )
		    	 {  sourceEnd.setInstance(source);
		    	    sourceEnd.setFeature(sourceFeature);
		    	    
		    	    aConnection.getContents().add(targetEnd);
		    	    aConnection.getContents().add(sourceEnd);
		    	    aConnection.setSource(sourceEnd);
		            aConnection.setTarget(targetEnd);
		            state=true;
		            dialogShell.close();
		            return;
		    	 }
		    	 if(source instanceof ComponentInstantiation &&
		    	 		((ComponentInstantiation)source).getType()!=null
						&&((ComponentInstantiation)source).getType().getComponent()!=null
						&&((ComponentInstantiation)source).getType().getComponent()==sourceFeature
						&&((ComponentInstantiation)source).getType().getComponent().getComponentSupports_itf()!=null
						&&((ComponentInstantiation)source).getType().getComponent().getComponentSupports_itf().contains(itf))
						 
		    	 				//(ComponentInstantiation)source )
		    	 {  sourceEnd.setInstance(source);
		    	    sourceEnd.setFeature(((ComponentInstantiation)source).getType().getComponent());
		    	    
		    	    aConnection.getContents().add(targetEnd);
		    	    aConnection.getContents().add(sourceEnd);
		    	    aConnection.setSource(sourceEnd);
		            aConnection.setTarget(targetEnd);
		            state=true;
		            dialogShell.close();
		            return;
		    	 	
		    	 }
		    	 aConnection=null;
		    	  invalidConnection(); 
		    	  return;
		    }
		    if(targetFeature instanceof ConsumesDef){
		    	ConsumesDef sink=(ConsumesDef)targetFeature;
		    	 EventDef event=sink.getEvent();
		    	 if(event==null){
		    	 	aConnection=null;
		    	 	 invalidConnection();
		    	 	 return;
		    	 }
		    	 if(source instanceof ComponentInstantiation &&
		    	 		( (sourceFeature instanceof PublishesDef &&((PublishesDef)sourceFeature).getEvent().equals(event))
		    	 		 || (sourceFeature instanceof EmitsDef &&((EmitsDef)sourceFeature).getEvent().equals(event))))
						 
		    	 				//(ComponentInstantiation)source )
		    	 {  sourceEnd.setInstance(source);
		    	    sourceEnd.setFeature(sourceFeature);
		    	    
		    	    aConnection.getContents().add(targetEnd);
		    	    aConnection.getContents().add(sourceEnd);
		    	    aConnection.setSource(sourceEnd);
		            aConnection.setTarget(targetEnd);
		            state=true;
		            dialogShell.close();
		            return;
		    	 } 
		    	 invalidConnection(); 
		    	  return;
		    }
		    if(targetFeature instanceof SinkDef||targetFeature instanceof SiSouDef){
		    	StreamProtDef sink=(StreamProtDef)targetFeature;
		    	 MediaType type=sink.getType();
		    	 if(type==null){
		    	 	aConnection=null;
		    	 	 invalidConnection();
		    	 	 return;
		    	 }
		    	 if(source instanceof ComponentInstantiation &&
		    	 		 (sourceFeature instanceof SourceDef &&((SourceDef)sourceFeature).getType().equals(type))
		    	 		 || (sourceFeature instanceof SiSouDef &&((SiSouDef)sourceFeature).getType().equals(type)))
						 
		    	 				//(ComponentInstantiation)source )
		    	 {  sourceEnd.setInstance(source);
		    	    sourceEnd.setFeature(sourceFeature);
		    	    
		    	    aConnection.getContents().add(targetEnd);
		    	    aConnection.getContents().add(sourceEnd);
		    	    aConnection.setSource(sourceEnd);
		            aConnection.setTarget(targetEnd);
		            state=true;
		            dialogShell.close();
		            return;
		    	 } 
		    	 aConnection=null;
		    	 invalidConnection(); 
		    	  return;
		    }
		    aConnection=null;
		    invalidConnection(); 
		    //dialogShell.close();
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
				//idlBtn = new Button(composite2,SWT.PUSH| SWT.CENTER);
				constValueTxt = new Combo(composite2,SWT.READ_ONLY);
				constValueLb = new Label(composite2,SWT.NULL);
				//cardinalityString =new Text(composite2,SWT.BORDER);
				idlTypeCmb = new Combo(composite2,SWT.READ_ONLY);
				idlTypeLb = new Label(composite2,SWT.NULL);
				implLb = new Label(composite2,SWT.NULL);
				implCmb = new Combo(composite2,SWT.READ_ONLY);
				
				objectrefTxt= new Combo(composite2,SWT.READ_ONLY);
				objectRefLb= new Label(composite2,SWT.NULL);
				
				repositoryIdTxt = new Text(composite2,SWT.BORDER);
				versionTxt = new Text(composite2,SWT.BORDER);
				identifierTxt = new Text(composite2,SWT.BORDER);
				versionLb = new Label(composite2,SWT.NULL);
				repositoryIdLb = new Label(composite2,SWT.NULL);
				idLb = new Label(composite2,SWT.NULL);
				composite3 = new Composite(dialogShell,SWT.NULL);
				cancel = new Button(composite3,SWT.PUSH| SWT.CENTER);
				enter = new Button(composite3,SWT.PUSH| SWT.CENTER);
		
				dialogShell.setText("Edit Connection");
				dialogShell.setSize(new org.eclipse.swt.graphics.Point(476,205));
		
			 
			 
		
				GridData composite2LData = new GridData();
				composite2LData.verticalAlignment = GridData.CENTER;
				composite2LData.horizontalAlignment = GridData.BEGINNING;
				composite2LData.widthHint = 464;
				composite2LData.heightHint = 160;
				composite2LData.horizontalIndent = 0;
				composite2LData.horizontalSpan = 1;
				composite2LData.verticalSpan = 1;
				composite2LData.grabExcessHorizontalSpace = false;
				composite2LData.grabExcessVerticalSpace = false;
				composite2.setLayoutData(composite2LData);
				composite2.setSize(new org.eclipse.swt.graphics.Point(464,160));
		
				 
				final Font idlBtnfont = new Font(Display.getDefault(),"Tahoma",8,1);
				final Font constValueTxtfont = new Font(Display.getDefault(),"Tahoma",7,0);
		
				FormData CmbLData = new FormData();
				 CmbLData.height = 20;
				 CmbLData.width = 306;
				 CmbLData.left =  new FormAttachment(269, 1000, 0);
				 CmbLData.right =  new FormAttachment(996, 1000, 0);
				 CmbLData.top =  new FormAttachment(1040, 1200, 0);
				 CmbLData.bottom =  new FormAttachment(1200, 1200, 0);
				implCmb.setLayoutData( CmbLData);
				implCmb.setSize(new org.eclipse.swt.graphics.Point(306,20));
				implCmb.setFont(constValueTxtfont);
				implCmb.addSelectionListener( new SelectionAdapter() {
					public void widgetSelected(SelectionEvent evt) {
						implCmbWidgetSelected(evt);
					}
				});
		
				FormData idlTypeLbLData1 = new FormData();
				idlTypeLbLData1.height = 20;
				idlTypeLbLData1.width = 60;
				idlTypeLbLData1.left =  new FormAttachment(9, 1000, 0);
				idlTypeLbLData1.right =  new FormAttachment(268, 1000, 0);
				idlTypeLbLData1.top =  new FormAttachment(1045, 1200, 0);
				idlTypeLbLData1.bottom =  new FormAttachment(1200, 1200, 0);
				implLb.setLayoutData(idlTypeLbLData1);
				implLb.setText("Target Feature:");
				implLb.setSize(new org.eclipse.swt.graphics.Point(60,20));
				implLb.setFont(idlBtnfont);
				
				
				FormData  TxtLData = new FormData();
				 TxtLData.height = 13;
				 TxtLData.width = 342;
				 TxtLData.left =  new FormAttachment(269, 1000, 0);
				 TxtLData.right =  new FormAttachment(996, 1000, 0);
				 TxtLData.top =  new FormAttachment(870, 1200, 0);
				 TxtLData.bottom =  new FormAttachment(1030, 1200, 0);
				 constValueTxt.setLayoutData( TxtLData);		
				 constValueTxt.setFont(constValueTxtfont);
				 constValueTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
				 constValueTxt.addSelectionListener( new SelectionAdapter() {
					public void widgetSelected(SelectionEvent evt) {
						tInstanceCmbWidgetSelected(evt);
					}
				});
		
				 FormData  LbLData = new FormData();
				 LbLData.height = 20;
				 LbLData.width = 100;
			     LbLData.left =  new FormAttachment(11, 1000, 0);
				 LbLData.right =  new FormAttachment(268, 1000, 0);
				 LbLData.top =  new FormAttachment(878, 1200, 0);
				 LbLData.bottom =  new FormAttachment(1030, 1200, 0);
				constValueLb.setLayoutData( LbLData);
				constValueLb.setText("Target Instance:");
				constValueLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
				constValueLb.setFont(idlBtnfont);
				
				
				FormData constValueTxtLData = new FormData();
				constValueTxtLData.height = 13;
				constValueTxtLData.width = 342;
				constValueTxtLData.left =  new FormAttachment(269, 1000, 0);
				constValueTxtLData.right =  new FormAttachment(996, 1000, 0);
				constValueTxtLData.top =  new FormAttachment(525, 1200, 0);
				constValueTxtLData.bottom =  new FormAttachment(672, 1200, 0);
				objectrefTxt.setLayoutData(constValueTxtLData);		
				objectrefTxt.setFont(constValueTxtfont);
				objectrefTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
				objectrefTxt.addSelectionListener( new SelectionAdapter() {
					public void widgetSelected(SelectionEvent evt) {
						sInstanceCmbWidgetSelected(evt);
					}
				});
		
				FormData constValueLbLData = new FormData();
				constValueLbLData.height = 20;
				constValueLbLData.width = 100;
				constValueLbLData.left =  new FormAttachment(11, 1000, 0);
				constValueLbLData.right =  new FormAttachment(268, 1000, 0);
				constValueLbLData.top =  new FormAttachment(538, 1200, 0);
				constValueLbLData.bottom =  new FormAttachment(672, 1200, 0);
				objectRefLb.setLayoutData(constValueLbLData);
				objectRefLb.setText("Source Instance:");
				objectRefLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
				objectRefLb.setFont(idlBtnfont);
		
				FormData idlTypeCmbLData = new FormData();
				idlTypeCmbLData.height = 27;
				idlTypeCmbLData.width = 306;
				idlTypeCmbLData.left =  new FormAttachment(269, 1000, 0);
				idlTypeCmbLData.right =  new FormAttachment(996, 1000, 0);
				idlTypeCmbLData.top =  new FormAttachment(700, 1200, 0);
				idlTypeCmbLData.bottom =  new FormAttachment(840, 1200, 0);
				idlTypeCmb.setLayoutData(idlTypeCmbLData);
				idlTypeCmb.setSize(new org.eclipse.swt.graphics.Point(306,27));
				idlTypeCmb.setFont(constValueTxtfont);
				idlTypeCmb.addSelectionListener( new SelectionAdapter() {
					public void widgetSelected(SelectionEvent evt) {
						serviceCmbWidgetSelected(evt);
					}
				});
		
				FormData idlTypeLbLData = new FormData();
				idlTypeLbLData.height = 27;
				idlTypeLbLData.width = 60;
				idlTypeLbLData.left =  new FormAttachment(11, 1000, 0);
				idlTypeLbLData.right =  new FormAttachment(268, 1000, 0);
				idlTypeLbLData.top =  new FormAttachment(702, 1200, 0);
				idlTypeLbLData.bottom =  new FormAttachment(840, 1200, 0);
				idlTypeLb.setLayoutData(idlTypeLbLData);
				idlTypeLb.setText("Source Feature:");
				idlTypeLb.setSize(new org.eclipse.swt.graphics.Point(60,27));
				idlTypeLb.setFont(idlBtnfont);
		
				FormData repositoryIdTxtLData = new FormData();
				repositoryIdTxtLData.height = 13;
				repositoryIdTxtLData.width = 342;
				repositoryIdTxtLData.left =  new FormAttachment(269, 1000, 0);
				repositoryIdTxtLData.right =  new FormAttachment(996, 1000, 0);
				repositoryIdTxtLData.top =  new FormAttachment(202, 1200, 0);
				repositoryIdTxtLData.bottom =  new FormAttachment(349, 1200, 0);
				repositoryIdTxt.setLayoutData(repositoryIdTxtLData);
				repositoryIdTxt.setDoubleClickEnabled(false);
				repositoryIdTxt.setFont(constValueTxtfont);
				repositoryIdTxt.setEditable(false);
				repositoryIdTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
				repositoryIdTxt.setEnabled(false);
		
				FormData versionTxtLData = new FormData();
				versionTxtLData.height = 13;
				versionTxtLData.width = 342;
				versionTxtLData.left =  new FormAttachment(269, 1000, 0);
				versionTxtLData.right =  new FormAttachment(996, 1000, 0);
				versionTxtLData.top =  new FormAttachment(363, 1200, 0);
				versionTxtLData.bottom =  new FormAttachment(511, 1200, 0);
				versionTxt.setLayoutData(versionTxtLData);
				versionTxt.setFont(constValueTxtfont);
				versionTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
				versionTxt.addKeyListener( new KeyAdapter() {
					public void keyReleased(KeyEvent evt) {
						versionTxtKeyReleased(evt);
					}
				});
		
				FormData identifierTxtLData = new FormData();
				identifierTxtLData.height = 13;
				identifierTxtLData.width = 342;
				identifierTxtLData.left =  new FormAttachment(269, 1000, 0);
				identifierTxtLData.right =  new FormAttachment(996, 1000, 0);
				identifierTxtLData.top =  new FormAttachment(37, 1200, 0);
				identifierTxtLData.bottom =  new FormAttachment(187, 1200, 0);
				identifierTxt.setLayoutData(identifierTxtLData);
				identifierTxt.setFont(constValueTxtfont);
				identifierTxt.setFocus();
				identifierTxt.setSize(new org.eclipse.swt.graphics.Point(342,13));
				identifierTxt.addKeyListener( new KeyAdapter() {
					public void keyReleased(KeyEvent evt) {
						identifierTxtKeyReleased(evt);
					}
				});
		
				FormData versionLbLData = new FormData();
				versionLbLData.height = 20;
				versionLbLData.width = 100;
				versionLbLData.left =  new FormAttachment(11, 1000, 0);
				versionLbLData.right =  new FormAttachment(248, 1000, 0);
				versionLbLData.top =  new FormAttachment(373, 1200, 0);
				versionLbLData.bottom =  new FormAttachment(511, 1200, 0);
				versionLb.setLayoutData(versionLbLData);
				versionLb.setText("Version:");
				versionLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
				versionLb.setFont(idlBtnfont);
		
				FormData repositoryIdLbLData = new FormData();
				repositoryIdLbLData.height = 20;
				repositoryIdLbLData.width = 100;
				repositoryIdLbLData.left =  new FormAttachment(11, 1000, 0);
				repositoryIdLbLData.right =  new FormAttachment(248, 1000, 0);
				repositoryIdLbLData.top =  new FormAttachment(212, 1200, 0);
				repositoryIdLbLData.bottom =  new FormAttachment(349, 1200, 0);
				repositoryIdLb.setLayoutData(repositoryIdLbLData);
				repositoryIdLb.setText("Repository ID:");
				repositoryIdLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
				repositoryIdLb.setFont(idlBtnfont);
		
				FormData idLbLData = new FormData();
				idLbLData.height = 20;
				idLbLData.width = 100;
				idLbLData.left =  new FormAttachment(11, 1000, 0);
				idLbLData.right =  new FormAttachment(248, 1000, 0);
				idLbLData.top =  new FormAttachment(40, 1200, 0);
				idLbLData.bottom =  new FormAttachment(187, 1200, 0);
				idLb.setLayoutData(idLbLData);
				idLb.setText("Identifier:");
				idLb.setSize(new org.eclipse.swt.graphics.Point(100,20));
				idLb.setFont(idlBtnfont);
				FormLayout composite2Layout = new FormLayout();
				composite2.setLayout(composite2Layout);
				composite2Layout.marginWidth = 0;
				composite2Layout.marginHeight = 0;
				composite2Layout.spacing = 0;
				composite2.layout();
		
				GridData composite3LData = new GridData();
				composite3LData.verticalAlignment = GridData.CENTER;
				composite3LData.horizontalAlignment = GridData.BEGINNING;
				composite3LData.widthHint = 464;
				composite3LData.heightHint = 45;
				composite3LData.horizontalIndent = 0;
				composite3LData.horizontalSpan = 1;
				composite3LData.verticalSpan = 1;
				composite3LData.grabExcessHorizontalSpace = false;
				composite3LData.grabExcessVerticalSpace = false;
				composite3.setLayoutData(composite3LData);
				composite3.setSize(new org.eclipse.swt.graphics.Point(464,45));
		
				FormData cancelLData = new FormData();
				cancelLData.height = 24;
				cancelLData.width = 80;
				cancelLData.left =  new FormAttachment(816, 1000, 0);
				cancelLData.right =  new FormAttachment(988, 1000, 0);
				cancelLData.top =  new FormAttachment( 6, 1000, 0);
				cancelLData.bottom =  new FormAttachment(580, 1000, 0);
				cancel.setLayoutData(cancelLData);
				cancel.setText("CANCEL");
				cancel.setSize(new org.eclipse.swt.graphics.Point(80,24));
				cancel.setFont(idlBtnfont);
				cancel.addMouseListener( new MouseAdapter() {
					public void mouseDown(MouseEvent evt) {
						cancelMouseDown(evt);
					}
				});
		
				FormData enterLData = new FormData();
				enterLData.height = 24;
				enterLData.width = 79;
				enterLData.left =  new FormAttachment(623, 1000, 0);
				enterLData.right =  new FormAttachment(795, 1000, 0);
				enterLData.top =  new FormAttachment( 6, 1000, 0);
				enterLData.bottom =  new FormAttachment(580, 1000, 0);
				enter.setLayoutData(enterLData);
				enter.setText("ENTER");
				enter.setSize(new org.eclipse.swt.graphics.Point(79,24));
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
						constValueTxtfont.dispose();
					}
				});
				Rectangle bounds = dialogShell.computeTrim(0, 0, 476,205);
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
		/**
		 * @param evt
		 */
		protected void sInstanceCmbWidgetSelected(SelectionEvent evt) {
			 source=(CCMInstantiation)sources.get(objectrefTxt.getSelectionIndex());
			 idlTypeCmb.removeAll();
			 if(source instanceof ComponentInstantiation){
			 	sourceFeatures.clear();
			 	sourceFeatures.addAll(((ComponentInstantiation)source).getFacet());
			 	sourceFeatures.addAll(((ComponentInstantiation)source).getEmitss());
			 	sourceFeatures.addAll(((ComponentInstantiation)source).getPublishesDef());
			 	sourceFeatures.addAll(((ComponentInstantiation)source).getSourcess());
			 	sourceFeatures.addAll(((ComponentInstantiation)source).getSiSouss());
			 
			 	Iterator it=sourceFeatures.iterator();
				 	while(it.hasNext()){
						Object o=it.next();
						idlTypeCmb.add(((Contained)o).getIdentifier());
				 	}
			}
	
		}

		/**
		 * @param evt
		 */
		protected void tInstanceCmbWidgetSelected(SelectionEvent evt) {
			implCmb.removeAll();
			if(targets.get(constValueTxt.getSelectionIndex()) instanceof ComponentInstantiation){
				target=(ComponentInstantiation)targets.get(constValueTxt.getSelectionIndex());
				targetFeatures.clear();
				targetFeatures.addAll(target.getReceptacle());
				targetFeatures.addAll(target.getConsumess());
				targetFeatures.addAll(target.getSinkss());
				targetFeatures.addAll(target.getSourcess());
				
				Iterator it=targetFeatures.iterator();
				 	while(it.hasNext()){
						Object o=it.next();
						implCmb.add(((Contained)o).getIdentifier());
				 	}
			}
		}

		/**
		 * @param evt
		 */
		protected void implCmbWidgetSelected(SelectionEvent evt) {
			targetFeature=(ComponentFeature)targetFeatures.get(implCmb.getSelectionIndex());
			
		}

		/**
		 * @param implementation
		 */
		public void setAssembly(Assembly ass) {
			this.ass=ass;
			List processes=ass.getProcessCollocation();
			for (Iterator it =processes.iterator();it.hasNext();){
				List homes=((ProcessCollocation)it.next()).getHomeInstances();
				for (Iterator hit =homes.iterator();hit.hasNext();){
					HomeInstantiation home=(HomeInstantiation)hit.next();
					sources.add(home);
					List comps=home.getComp();
					for (Iterator cit =comps.iterator();cit.hasNext();){
						ComponentInstantiation comp=(ComponentInstantiation)cit.next(); 
						sources.add(comp);
						targets.add(comp);
					}
					
					
				}
				
			}
		}

		/**
		 * @param evt
		 */
		protected void objectrefTxtKeyReleased(KeyEvent evt) {
			try{
				cardinality= Integer.parseInt(objectrefTxt.getText());
			}
			catch(NumberFormatException e){
				MessageDialog.openError(parent, "Error",  " the type of cardinality is Integer " ); 
				}
			
		}
		private void invalidConnection(){
			MessageDialog.openError(parent, "Error",  " invalid Connection " ); 
	
		}
		/**
		 * @param evt
		 */
		protected void constValueTxtKeyReleased(KeyEvent evt) {
			regName=constValueTxt.getText();
			
		}

		/**
		 * @param evt
		 */
		protected void serviceCmbWidgetSelected(SelectionEvent evt) {
			 
			sourceFeature=(ComponentFeature)this.sourceFeatures.get(idlTypeCmb.getSelectionIndex());
			
		}

		/**
		 * @param kind
		 */
		private void setService(FinderServiceKind kind) {
			service=kind;
			
		}

		/**
		 * @param evt
		 */
	//	protected void cardinalityTxtKeyReleased(KeyEvent evt) {
	//		try{
	//			cardinality= Integer.parseInt(cardinalityString.getText());
	//		}
	//		catch(NumberFormatException e){
	//			MessageDialog.openError(parent, "Error",  " the type of cardinality is Integer " ); }
	//		
	//	}

		/** Add your pre-init code in here 	*/
		public void preInitGUI(){
		}

		/** Add your post-init code in here 	*/
		public void postInitGUI(){
		    repositoryIdTxt.setText(repositoryId);
		    versionTxt.setText(version);
		    identifierTxt.setText(identifier);
		    Iterator it=this.sources.iterator();
		 	while(it.hasNext()){
				Object o=it.next();
				objectrefTxt.add(((Contained)o).getIdentifier());
		 	}
		 	 
		 	it=this.targets.iterator();
		 	while(it.hasNext()){
				Object o=it.next();
				constValueTxt.add(((Contained)o).getIdentifier());
		 	}
		 	 if(aConnection!=null){
		    	source=aConnection.getSource().getInstance();
		    	target=(ComponentInstantiation)aConnection.getTarget().getInstance();
		    	sourceFeature=aConnection.getSource().getFeature();
		    	targetFeature=aConnection.getTarget().getFeature();
		    	objectrefTxt.select(sources.indexOf(source));
		    	constValueTxt.select(targets.indexOf(target));
		    	if(source instanceof ComponentInstantiation){
				 	sourceFeatures.clear();
				 	sourceFeatures.add(((ComponentInstantiation)source).getType().getComponent());
				 	sourceFeatures.addAll(((ComponentInstantiation)source).getFacet());
				 	sourceFeatures.addAll(((ComponentInstantiation)source).getEmitss());
				 	sourceFeatures.addAll(((ComponentInstantiation)source).getPublishesDef());
				 	sourceFeatures.addAll(((ComponentInstantiation)source).getSourcess());
				 	sourceFeatures.addAll(((ComponentInstantiation)source).getSiSouss());
				 	idlTypeCmb.removeAll();
				 	Iterator sit=sourceFeatures.iterator();
					while(sit.hasNext()){
						Object o=sit.next();
						idlTypeCmb.add(((Contained)o).getIdentifier());
					}
					idlTypeCmb.select(sourceFeatures.indexOf(sourceFeature)) ;	
				}
		    	//target=(ComponentInstantiation)targets.get(constValueTxt.getSelectionIndex());
				targetFeatures.clear();
				targetFeatures.addAll(target.getReceptacle());
				targetFeatures.addAll(target.getConsumess());
				targetFeatures.addAll(target.getSinkss());
				targetFeatures.addAll(target.getSourcess());
				implCmb.removeAll();
				Iterator cit=targetFeatures.iterator();
				while(cit.hasNext()){
					Object o=cit.next();
					implCmb.add(((Contained)o).getIdentifier());
				}
				implCmb.select(targetFeatures.indexOf(targetFeature)) ;	
		    	
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
				EditConnectionDialog2 inst = new EditConnectionDialog2(shell, SWT.NULL);
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
	    /**
	     * @return Returns the state.
	     */
	    public boolean isState() {
	        return state;
	    }
	    /**
	     * @param discription The discription to set.
	     */
	    
	  
	    public int getcardinality() {
	        return cardinality;
	    }
	    public FinderServiceKind getService() {
	        return service;
	    }
	    public String getregName() {
	        return regName;
	    }
	    /**
	     * @param idlTList The idlTList to set.
	     */
	    public void setIdlTList(java.util.List idlTList) {
	        this.idlTList.clear();
	        this.idlTList.addAll(idlTList);
	    }

		/** Auto-generated event handler method */
		protected void versionTxtKeyReleased(KeyEvent evt){
		    version=versionTxt.getText();
		    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
		    repositoryIdTxt.setText(repositoryId);
		}

		/** Auto-generated event handler method */
		protected void identifierTxtKeyReleased(KeyEvent evt){
		    identifier=identifierTxt.getText();
		    repositoryId = CCMConstants.getRepositoryIdString(absName,identifier,version);
		    repositoryIdTxt.setText(repositoryId);
		}

		 
	    /**
	     * @return Returns the idlTemp.
	     */
	    public AssemblyConnection getConnection() {
	        return aConnection;
	    }
	    /**
	     * @param idlTemp The idlTemp to set.
	     */
	    public void setIdlTemp(IDLTemplate idlTemp) {
	        this.idlTemp = idlTemp;
	    }

		/**
		 * @param repositoryId2
		 */
		public void setRepositoryID(String repositoryId) {
			this.repositoryId=repositoryId;
			
		}
	   public void setConnection(AssemblyConnection aConnection){
	   	 this.aConnection=aConnection;
	   }
	}
  
