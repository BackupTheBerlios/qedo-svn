/**
 * Created on 04.03.2005
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model.template;

import CCMModel.ParameterMode;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ParameterTemplate {
    
    private String identifier;
    private ParameterMode mode;
	private IDLTemplate idlType=new IDLTemplate(IDLKind.IDL_LITERAL);
    
    public ParameterTemplate(String identifier){
        this.identifier=identifier;
        mode=ParameterMode.PARAM_IN_LITERAL;
    }
    
    public ParameterTemplate(String identifier,ParameterMode mode){
        this.identifier=identifier;
        this.mode=mode;
    }
    
    public ParameterTemplate(String identifier,ParameterMode mode,IDLTemplate idlType){
        this.identifier=identifier;
        this.mode=mode;
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
     * @return Returns the mode.
     */
    public ParameterMode getMode() {
        return mode;
    }
    /**
     * @param mode The mode to set.
     */
    public void setMode(ParameterMode mode) {
        this.mode = mode;
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
