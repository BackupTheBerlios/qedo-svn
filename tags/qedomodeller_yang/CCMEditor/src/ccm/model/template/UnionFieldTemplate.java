/**
 * Created on 04.03.2005
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model.template;



/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class UnionFieldTemplate {
    
    private String identifier;
    private String label;
	private IDLTemplate idlType=new IDLTemplate(IDLKind.IDL_LITERAL);
    
    public UnionFieldTemplate(String identifier){
        this.identifier=identifier;
        this.label="";
    }
    
    public UnionFieldTemplate(String identifier,String label){
        this.identifier=identifier;
        this.label=label;
    }

    
    public UnionFieldTemplate(String identifier, String label,IDLTemplate idlType){
        this.identifier=identifier;
        this.label=label;
        this.idlType=idlType;
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
     * @return Returns the label.
     */
    public String getLabel() {
        return label;
    }
    /**
     * @param label The label to set.
     */
    public void setLabel(String label) {
        this.label = label;
    }
    /**
     * @return Returns the idlType.
     */
    public IDLTemplate getIdlType() {
        return idlType;
    }
    /**
     * @param idlType The idlType to set.
     */
    public void setIdlType(IDLTemplate idlType) {
        this.idlType = idlType;
    }
}
