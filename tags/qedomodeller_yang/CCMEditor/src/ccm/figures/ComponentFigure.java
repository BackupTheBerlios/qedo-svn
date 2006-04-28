package ccm.figures;
import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Color;

import ccm.ProjectResources;

/*
 * Created on 30.11.2004
 */

/**
 * @author holger
 */
public class ComponentFigure extends Figure {
	
	public static Color classColor = new Color(null,255,255,206);
	
    
	protected ChopboxAnchor incomingConnectionAnchor;
	protected ChopboxAnchor outgoingConnectionAnchor;
	
	protected ContainedWithMembersFigure memberFigure;
	
	public ComponentFigure() {
		setLayoutManager(new ToolbarLayout());
		setBorder(new LineBorder(ColorConstants.black,1));
		setBackgroundColor(classColor);
		setOpaque(true);
		
		incomingConnectionAnchor = new ChopboxAnchor(this);
		outgoingConnectionAnchor = new ChopboxAnchor(this);
		
		memberFigure=new ContainedWithMembersFigure("",ProjectResources.COMPONENT_S);
		//Dimension mDim = memberFigure.getSize();
		add(memberFigure);
	}
	
	/**
	 * Retrieving the wanted Dimension for this figure.
	 * as a sideeffect, the offset values are calculated by iterating
	 * over the port labels.
	 */
	public Dimension getPreferredSize(Dimension parentDim) {
		Dimension dim = new Dimension(memberFigure.getPreferredSize(0,0));
		return dim.union(parentDim).union(new Dimension(80,60));
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
}
