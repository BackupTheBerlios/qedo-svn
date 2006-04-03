/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 * 
 */
package ccm.figures;

import org.eclipse.draw2d.BorderLayout;
import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.swt.graphics.Image;

import ccm.CCMConstants;
import ccm.CCMEditorPlugin;


public class ContainerFigure extends Figure{
    
    
	protected ChopboxAnchor incomingConnectionAnchor;
	protected ChopboxAnchor outgoingConnectionAnchor;
	
	// the Label for the classifier-head 
	protected Label identifierLabel;

	
	// this figure consists of two compartment-figures:
	// one for the classifier-head (class- and variable-name)
	// and one for the list of attributes
	private CompartmentFigure labelsPanel = new CompartmentFigure();
	private CompartmentPanel figuresPanel;
	private CompartmentFigure classFigure = new CompartmentFigure();

	
	/**
	 * Constructor of the ClassifierRoleFigure:
	 * Creates a Figure for a class with a class-name,
	 * a variable-name (optional - may be empty, but not null),
	 * and attributes and place them inside a UML-like
	 * box for classes.
	 * @param identifier   - the identifier for this class-instance
	 */
	public ContainerFigure(String identifier,String imageName){
		figuresPanel = new CompartmentPanel();
		// The classlabel with <@img><varname>: <classname> and the font specified above
		identifierLabel = new Label(identifier,new Image(null,
		        CCMEditorPlugin.class.getResourceAsStream(imageName)));
		identifierLabel.setFont(CCMConstants.font);
		identifierLabel.setLabelAlignment(PositionConstants.CENTER);
		classFigure.add(identifierLabel);
		
		
		// place everything inside a ToolbarLayout
		// and a LineBorder
		ModBorderLayout layout = new ModBorderLayout();
		setLayoutManager(layout);
		setBorder(new LineBorder(ColorConstants.black,1));
		setBackgroundColor(CCMConstants.classColor);
		setOpaque(true);

		// add the nested components to the figure
		add(classFigure,BorderLayout.TOP);
		add(labelsPanel,BorderLayout.CENTER);
		add(figuresPanel,BorderLayout.BOTTOM);
		
		incomingConnectionAnchor = new ChopboxAnchor(this);
		outgoingConnectionAnchor = new ChopboxAnchor(this);
	}
	public ContainerFigure(String identifier,String imageName, boolean XYLayout){
		figuresPanel = new CompartmentPanel(XYLayout);
		// The classlabel with <@img><varname>: <classname> and the font specified above
		identifierLabel = new Label(identifier,new Image(null,
		        CCMEditorPlugin.class.getResourceAsStream(imageName)));
		identifierLabel.setFont(CCMConstants.font);
		identifierLabel.setLabelAlignment(PositionConstants.CENTER);
		classFigure.add(identifierLabel);
		
		
		// place everything inside a ToolbarLayout
		// and a LineBorder
		ModBorderLayout layout = new ModBorderLayout();
		setLayoutManager(layout);
		setBorder(new LineBorder(ColorConstants.black,1));
		setBackgroundColor(CCMConstants.classColor);
		setOpaque(true);

		// add the nested components to the figure
		add(classFigure,BorderLayout.TOP);
		add(labelsPanel,BorderLayout.CENTER);
		add(figuresPanel,BorderLayout.BOTTOM);
		
		incomingConnectionAnchor = new ChopboxAnchor(this);
		outgoingConnectionAnchor = new ChopboxAnchor(this);
	}
	
	/**
	 * Overwritten method, indicates that a local
	 * coordinate system is used.
	 */
	protected boolean useLocalCoordinates() {return true;}

	/**
	 * Retrieving the minimum Dimension
	 * @see getPreferredSize()
	 */
	public Dimension getMinimumSize(int wHint, int hHint) {return getPreferredSize();}

	/**
	 * Retrieving the wanted Dimension for this figure.
	 * It is calculated by the sum of the dimension of the
	 * classFigure (at the top) and the dimension for the
	 * attributeFigure (bottom) in y-axis, and the max of
	 * the values from both for x-axis.
	 */
	public Dimension getPreferredSize(int wHint, int hHint) {
		int width = Math.max(labelsPanel.getPreferredSize(0,0).width,
				classFigure.getPreferredSize(0,0).width); 
		width = Math.max(figuresPanel.getPreferredSize(0,0).width,
				width);
		
		int height = labelsPanel.getPreferredSize(0,0).height
			+ classFigure.getPreferredSize(0,0).height
			+ figuresPanel.getPreferredSize(0,0).height;
		
		return new Dimension(width,height);
	}
	
	/**
	 * This method will set the ClassVarName of this 
	 * classifier in the graphical view.
	 */
	public void setIdentifier(String identifier) {
		identifierLabel.setText(identifier);
	}
    /**
     * @return Returns the attributeFigure.
     */
    public CompartmentFigure getPaneFigure() {
        return labelsPanel;
    }
    /**
     * @return Returns the figuresPanel.
     */
    public IFigure getFiguresPanel() {
        return figuresPanel.getPane();
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
}
