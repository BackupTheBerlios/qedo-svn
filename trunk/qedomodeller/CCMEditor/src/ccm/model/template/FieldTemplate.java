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
public class FieldTemplate {
    
    private String identifier;
	//private int idlTypeNumber=0;
    private IDLTemplate idlType=new IDLTemplate(IDLKind.IDL_LITERAL);
    
    public FieldTemplate(String identifier){
        this.identifier=identifier;
    }
    

    
    public FieldTemplate(String identifier,IDLTemplate idlType){
        this.identifier=identifier;
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
