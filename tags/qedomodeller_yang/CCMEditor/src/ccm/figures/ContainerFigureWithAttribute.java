 /**
  * (c) Copyright group ccm
  *
  * All rights reserved. This program and the accompanying materials 
  * are made available under the terms of the Common Public License v1.0 
  * which accompanies this distribution
  * @author Siegercn
  *  

  * 
  */
 package ccm.figures;

 import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;

import ccm.CCMConstants;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;


 public class ContainerFigureWithAttribute  extends Figure{
     
 	public static Color classColor = new Color(null,255,255,206);
 	
     
 	protected ChopboxAnchor incomingConnectionAnchor;
 	protected ChopboxAnchor outgoingConnectionAnchor;
 	// the Label for the classifier-head 
 	protected Label identifierLabel;
 	protected Label[] attributeLabel;
 	protected String[]attributtes;
// 	private CompartmentFigure labelsPanel = new CompartmentFigure();
 	private CompartmentFigure figuresPanel= new CompartmentFigure();
 	protected ContainedWithMembersFigure memberFigure;
 	//	private CompartmentFigure classFigure = new CompartmentFigure();

 	
 	/**
 	 * Constructor of the ClassifierRoleFigure:
 	 * Creates a Figure for a class with a class-name,
 	 * a variable-name (optional - may be empty, but not null),
 	 * and attributes and place them inside a UML-like
 	 * box for classes.
 	 * @param identifier   - the identifier for this class-instance
 	 */
 	public ContainerFigureWithAttribute (String identifier,String imageName,String[]attributtes){
 		// The classlabel with <@img><varname>: <classname> and the font specified above
 		setLayoutManager(new ToolbarLayout());
 		setBorder(new LineBorder(ColorConstants.black,1));
 		//setBackgroundColor(classColor);
 		//setBackgroundColor(classColor);
 		//setOpaque(true);
 		incomingConnectionAnchor = new ChopboxAnchor(this);
 		outgoingConnectionAnchor = new ChopboxAnchor(this);
 		memberFigure=new ContainedWithMembersFigure(identifier,imageName);
 		//identifierLabel = new Label(identifier,new Image(null,
 		//       CCMEditorPlugin.class.getResourceAsStream(imageName)));
 		//identifierLabel.setFont(CCMConstants.font);
 		//identifierLabel.setLabelAlignment(PositionConstants.LEFT);
 		//identifierLabel.setBackgroundColor(classColor);
 		//classFigure.add(identifierLabel);
 		//figuresPanel=memberFigure.getPaneFigure();
 		if(attributtes!=null){
 		  int size=attributtes.length;
 		  attributeLabel= new Label[size];
 		  for(int i=0;i<size;i++){
 			attributeLabel[i]= new Label(attributtes[i],new Image(null,
 					      CCMEditorPlugin.class.getResourceAsStream(ProjectResources.MEMBER_S))) ;
 			attributeLabel[i].setFont(CCMConstants.font1);
 			attributeLabel[i].setLabelAlignment(PositionConstants.LEFT);
 			figuresPanel.add(attributeLabel[i]);
 			
 		  }
 		}
 		Dimension mDim = memberFigure.getSize();
 		add(memberFigure);
 		//add(identifierLabel);
 		add(figuresPanel);
 		 
 	}
 	
 	/**
 	 * Overwritten method, indicates that a local
 	 * coordinate system is used.
 	 */
 	public Dimension getPreferredSize(Dimension parentDim) {
 		Dimension dim = new Dimension(memberFigure.getPreferredSize(0,0));
 		return dim.union(parentDim).union(new Dimension(0,0));
 		//return dim;
 	}
 	
 	public void refresh(Rectangle r) {
 		
 		this.setConstraint(memberFigure,
 				new Rectangle(0,0,r.width,32));
 	}

 	/**
 	 * sets the displayed name of the component
 	 * @param name
 	 */
 	public void setName(String name) {
 	    memberFigure.setIdentifier(name);
 	}
 	
     /**
      * @return
      */
     public IFigure getAttributeFigure() {
         return memberFigure.getPaneFigure();
     }

     /**
      * @return Returns the incomingConnectionAnchor.
      */
     public ChopboxAnchor getIncomingConnectionAnchor() {
         return incomingConnectionAnchor;
     }
     /**
      * @param incomingConnectionAnchor The incomingConnectionAnchor to set.
      */
     public void setIncomingConnectionAnchor(
             ChopboxAnchor incomingConnectionAnchor) {
         this.incomingConnectionAnchor = incomingConnectionAnchor;
     }
     /**
      * @return Returns the outgoingConnectionAnchor.
      */
     public ChopboxAnchor getOutgoingConnectionAnchor() {
         return outgoingConnectionAnchor;
     }
     /**
      * @param outgoingConnectionAnchor The outgoingConnectionAnchor to set.
      */
     public void setOutgoingConnectionAnchor(
             ChopboxAnchor outgoingConnectionAnchor) {
         this.outgoingConnectionAnchor = outgoingConnectionAnchor;
     }

 	/**
 	 * @param strings
 	 */
 	public void setAttributeLabels(String[] strings) {
 		for (int i=0;i<attributeLabel.length;i++){
 			figuresPanel.remove(attributeLabel[i]);
 		}
 		attributeLabel= new Label[strings.length];
 		for(int i=0;i<strings.length;i++){
 			attributeLabel[i]= new Label(strings[i],new Image(null,
 					      CCMEditorPlugin.class.getResourceAsStream(ProjectResources.MEMBER_S))) ;
 			attributeLabel[i].setFont(CCMConstants.font1);
 			attributeLabel[i].setLabelAlignment(PositionConstants.LEFT);
 			attributeLabel[i].setBorder(new LineBorder(ColorConstants.black,1));
 			figuresPanel.add(attributeLabel[i]);
 			
 		  }
 		 
 	}
 }
