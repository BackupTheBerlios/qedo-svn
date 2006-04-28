/*
 * Created on 23.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.editors;

import org.eclipse.gef.ui.parts.TreeViewer;

import CCMModel.View;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class CCMTreeViewer extends TreeViewer {

    private TypeOutlinePage toPage; 

    
    public void setContentsToGraphical(View view){
        toPage.getTpviewer().setContents(view); 
    }
    
    /**
     * @return Returns the toPage.
     */
    public TypeOutlinePage getToPage() {
        return toPage;
    }
    /**
     * @param toPage The toPage to set.
     */
    public void setToPage(TypeOutlinePage toPage) {
        this.toPage = toPage;
    }
}
