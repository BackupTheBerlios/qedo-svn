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

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.swt.graphics.Image;

import ccm.CCMConstants;
import ccm.CCMEditorPlugin;


public class ContainedWithMembersFigure extends Figure{
	
	// the Label for the classifier-head 
	protected Label identifierLabel;

	
	// this figure consists of two compartment-figures:
	// one for the classifier-head (class- and variable-name)
	// and one for the list of attributes
	private CompartmentFigure parameterFigure = new CompartmentFigure();
	private CompartmentFigure classFigure = new CompartmentFigure();
	private String identifier;
	
	/**
	 * Constructor of the ClassifierRoleFigure:
	 * Creates a Figure for a class with a class-name,
	 * a variable-name (optional - may be empty, but not null),
	 * and attributes and place them inside a UML-like
	 * box for classes.
	 * @param shell     - the shell where the figure is drawn on
	 * @param varname   - the variable-name for this class-instance
	 * @param classname - the class name
	 */
	public ContainedWithMembersFigure(String identifier){
		
			
		// The classlabel with <@img><varname>: <classname> and the font specified above
		identifierLabel = new Label(identifier );
						// new Image(null, 
		                 //      ClassifierRoleLabel.class.getResourceAsStream("gif/class_obj.gif")));
		identifierLabel.setFont(CCMConstants.font);
		identifierLabel.setLabelAlignment(PositionConstants.LEFT);
		classFigure.add(identifierLabel);
		
		
		// place everything inside a ToolbarLayout
		// and a LineBorder
		ToolbarLayout layout = new ToolbarLayout();
		setLayoutManager(layout);
		setBorder(new LineBorder(ColorConstants.black,1));
		setBackgroundColor(CCMConstants.classColor);
		setOpaque(true);
		
		// add the nested components to the figure
		add(classFigure);
		add(parameterFigure);
	}
	/**
	 * Constructor of the ClassifierRoleFigure:
	 * Creates a Figure for a class with a class-name,
	 * a variable-name (optional - may be empty, but not null),
	 * and attributes and place them inside a UML-like
	 * box for classes.
	 * @param shell     - the shell where the figure is drawn on
	 * @param varname   - the variable-name for this class-instance
	 * @param classname - the class name
	 */
	public ContainedWithMembersFigure(String identifier,String imageFile){
		
			
		// The classlabel with <@img><varname>: <classname> and the font specified above
		identifierLabel = new Label(identifier ,new Image(null, 
		                      CCMEditorPlugin.class.getResourceAsStream(imageFile)));
		identifierLabel.setFont(CCMConstants.font);
		identifierLabel.setLabelAlignment(PositionConstants.LEFT);
		classFigure.add(identifierLabel);
		
		
		// place everything inside a ToolbarLayout
		// and a LineBorder
		ToolbarLayout layout = new ToolbarLayout();
		setLayoutManager(layout);
		setBorder(new LineBorder(ColorConstants.gray,1));
		setBackgroundColor(CCMConstants.classColor);
		setOpaque(true);
		
		// add the nested components to the figure
		add(classFigure);
		add(parameterFigure);
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
		Dimension dim1 = classFigure.getPreferredSize(0,0);
		Dimension dim2 = parameterFigure.getPreferredSize(0,0);	
		int x = Math.max(dim1.width,dim2.width);
		int y = dim1.height + dim2.height;
		return new Dimension(x, y);
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
        return parameterFigure;
    }
}
