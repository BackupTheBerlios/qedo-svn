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
package ccm.commands.constraints;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.FigureUtilities;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Image;

import CCMModel.ComponentDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.EmitsDef;
import CCMModel.Node;
import CCMModel.PortLocation;
import CCMModel.PortNode;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.UsesDef;
import CCMModel.View;
import ccm.CCMConstants;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;



/**
 * The <code>SetConstraintCommand</code> allows WorkflowElements to be moved and resized
 * @author eduardw
 *
 */
public class ConstraintForComponentDefNode
	extends org.eclipse.gef.commands.Command
{
	private static final String Command_Label_Location = "change location command";
	private static final String Command_Label_Resize = "resize command";
	
	private Point newPos;
	private Point oldPos;
	private Node part;
	private boolean isInstance=false;
	private Dimension newSize=new Dimension(0,0);
	private Dimension oldSize=new Dimension(0,0);
	
	private List portNodes=new LinkedList();
	public ConstraintForComponentDefNode(boolean isInstance){
		super();
		this.isInstance=isInstance;
	}
	/**
	 * Execution of this command node and resizes 
	 * a constraint
	 */
	public void execute() {
		oldPos  = new Point( part.getX(), part.getY() );
		oldSize=new Dimension(part.getWidth(),part.getHeight());
		
		portNodes.clear();
	    View view=part.getView();
	    List pNodes;
	    if(!isInstance)
	    	pNodes=view.getNode();
	    else
	    	pNodes=part.getDefineIn().getContents();
	  
		for(Iterator pit=pNodes.iterator();pit.hasNext();){
		    Node pnode=(Node) pit.next();
		    Contained con=pnode.getContained();
		    if(pnode instanceof PortNode &&((PortNode)pnode).getHostNode().equals(part))
				portNodes.add(pnode);
		  }
	    
	 
		Iterator it=portNodes.iterator();
		while(it.hasNext()){
		    Node n=(Node) it.next();
		    
		    if(n.getLocation().getValue()==PortLocation.TOP ||
		    		n.getLocation().getValue()==PortLocation.LEFT) {
		    	n.setX(n.getX()-(oldPos.x-newPos.x)/*-(oldSize.width-newSize.width)*/);
		    	n.setY(n.getY()-(oldPos.y-newPos.y)/*-(oldSize.height-newSize.height)*/);
		    }
		    else {
		    	n.setX(n.getX()-(oldPos.x-newPos.x)-(oldSize.width-newSize.width));
		    	n.setY(n.getY()-(oldPos.y-newPos.y)-(oldSize.height-newSize.height));

		    }
		    
			Dimension minimum= FigureUtilities.getTextExtents(n.getContained().getIdentifier()
					, CCMConstants.font);	
			Image image=new Image(null,
					CCMEditorPlugin.class.getResourceAsStream(
							ProjectResources.getPortIconPath(n.getContained(),n.getLocation().getValue())));
			Dimension imageDim=new Dimension(image.getBounds().width,image.getBounds().height);
		    
		    if(n.getX()<newPos.x-minimum.width-imageDim.width)
		    	n.setX(newPos.x-minimum.width-imageDim.width);
			if(n.getX()>newPos.x+newSize.width)
				n.setX(newPos.x+newSize.width);
			if(n.getY()<newPos.y-minimum.height/*-imageDim.height*/)
				n.setY(newPos.y-minimum.height-imageDim.height);
			if(n.getY()>newPos.y+newSize.height)
				n.setY(newPos.y+newSize.height);
		}
		if(!oldSize.equals(newSize)){
			oldSize = new Dimension(part.getWidth(),part.getHeight());	
			part.setWidth(newSize.width);
			part.setHeight(newSize.height);
		}
		part.setX(newPos.x);
		part.setY(newPos.y);
	}
	
	/**
	 * Returns the label for this command
	 * as string-value
	 */
	public String getLabel(){
		return Command_Label_Resize;
	}
	
	/**
	 * Redos a previous undone action
	 */
	public void redo() {
		portNodes.clear();
	    View view=part.getView();
		ComponentDef obj=(ComponentDef) part.getContained();
		 Iterator it=view.getNode().iterator();
		 while(it.hasNext()){
		        Node n=(Node) it.next();
		        if(n.getContained() instanceof ProvidesDef ||
		        		n.getContained() instanceof UsesDef ||
						n.getContained() instanceof EmitsDef ||
						n.getContained() instanceof ConsumesDef ||
						n.getContained() instanceof PublishesDef)
		            if(n.getContained().eContainer().equals(obj))
		            	portNodes.add(n);
		  }

		it=portNodes.iterator();
		while(it.hasNext()){
		    Node n=(Node) it.next();
		    
		    if(n.getLocation().getValue()==PortLocation.TOP ||
		    		n.getLocation().getValue()==PortLocation.LEFT) {
		    	n.setX(n.getX()-(oldPos.x-newPos.x)/*-(oldSize.width-newSize.width)*/);
		    	n.setY(n.getY()-(oldPos.y-newPos.y)/*-(oldSize.height-newSize.height)*/);
		    }
		    else {
		    	n.setX(n.getX()-(oldPos.x-newPos.x)-(oldSize.width-newSize.width));
		    	n.setY(n.getY()-(oldPos.y-newPos.y)-(oldSize.height-newSize.height));

		    }
		    
			Dimension minimum= FigureUtilities.getTextExtents(n.getContained().getIdentifier()
					, CCMConstants.font);	
			Image image=new Image(null,
					CCMEditorPlugin.class.getResourceAsStream(
							ProjectResources.getPortIconPath(n.getContained(),n.getLocation().getValue())));
			Dimension imageDim=new Dimension(image.getBounds().height,image.getBounds().height);
		    
		    if(n.getX()<newPos.x-minimum.width-imageDim.width)
		    	n.setX(newPos.x-minimum.width-imageDim.width);
			if(n.getX()>newPos.x+newSize.width)
				n.setX(newPos.x+newSize.width);
			if(n.getY()<newPos.y-minimum.height/*-imageDim.height*/)
				n.setY(newPos.y-minimum.height-imageDim.height);
			if(n.getY()>newPos.y+newSize.height)
				n.setY(newPos.y+newSize.height);
		}
		
		if(!oldSize.equals(newSize)){
			part.setWidth(newSize.width);
			part.setHeight(newSize.height);
		}
		part.setX(newPos.x);
		part.setY(newPos.y);
	}
	
	/**
	 * Sets the location of the node
	 * @param r - a rectangle holding the new location
	 */
	public void setRectangle(Rectangle r){
		setLocation(r.getLocation());
		newSize=r.getSize();
	}

	/**
	 * Sets the location of the node
	 * @param p - a point holding the new location
	 */	
	public void setLocation(Point p) {
		newPos = p;
	}
	
	/**
	 * Sets a new part to layout
	 * @param part - a constraint
	 */
	public void setPart(Node part) {
		this.part = part;

	}
	

	/**
	 * Invalidates an action previously done
	 * by this command.
	 */
	public void undo() {
		
		portNodes.clear();
	    View view=part.getView();
		ComponentDef obj=(ComponentDef) part.getContained();
		 Iterator it=view.getNode().iterator();
		 while(it.hasNext()){
		        Node n=(Node) it.next();
		        if(n.getContained() instanceof ProvidesDef ||
		        		n.getContained() instanceof UsesDef ||
						n.getContained() instanceof EmitsDef ||
						n.getContained() instanceof ConsumesDef ||
						n.getContained() instanceof PublishesDef)
		            if(n.getContained().eContainer().equals(obj))portNodes.add(n);
		  }

		it=portNodes.iterator();
		while(it.hasNext()){
		    Node n=(Node) it.next();
		    
		    if(n.getLocation().getValue()==PortLocation.TOP ||
		    		n.getLocation().getValue()==PortLocation.LEFT) {
		    	n.setX(n.getX()+(oldPos.x-newPos.x)/*-(oldSize.width-newSize.width)*/);
		    	n.setY(n.getY()+(oldPos.y-newPos.y)/*-(oldSize.height-newSize.height)*/);
		    }
		    else {
		    	n.setX(n.getX()+(oldPos.x-newPos.x)+(oldSize.width-newSize.width));
		    	n.setY(n.getY()+(oldPos.y-newPos.y)+(oldSize.height-newSize.height));

		    }
		    
			Dimension minimum= FigureUtilities.getTextExtents(n.getContained().getIdentifier()
					, CCMConstants.font);	
			Image image=new Image(null,
					CCMEditorPlugin.class.getResourceAsStream(
							ProjectResources.getPortIconPath(n.getContained(),n.getLocation().getValue())));
			Dimension imageDim=new Dimension(image.getBounds().height,image.getBounds().height);
		    
		    if(n.getX()<oldPos.x-minimum.width-imageDim.width)
		    	n.setX(oldPos.x-minimum.width-imageDim.width);
			if(n.getX()>oldPos.x+oldSize.width)
				n.setX(oldPos.x+oldSize.width);
			if(n.getY()<oldPos.y-minimum.height/*-imageDim.height*/)
				n.setY(oldPos.y-minimum.height-imageDim.height);
			if(n.getY()>oldPos.y+oldSize.height)
				n.setY(oldPos.y+oldSize.height);
		}
		
		if(!oldSize.equals(newSize)){
			part.setWidth(oldSize.width);
			part.setHeight(oldSize.height);	
		}
		part.setX(oldPos.x);
		part.setY(oldPos.y);
	}

}
