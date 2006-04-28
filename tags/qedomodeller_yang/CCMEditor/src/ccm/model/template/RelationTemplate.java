/*
 * Created on 27.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model.template;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class RelationTemplate {
    
    private int kind=0;
    
    public RelationTemplate(){}
    
    public RelationTemplate(int kind){
        this.kind=kind;
    }

    /**
     * @return Returns the kind.
     */
    public int getKind() {
        return kind;
    }
    /**
     * @param kind The kind to set.
     */
    public void setKind(int kind) {
        this.kind = kind;
    }
}
