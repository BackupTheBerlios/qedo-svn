/*
 * Created on Jun 2, 2005
 */
package ccm.commands.create.model;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.gef.commands.Command;

import CCMModel.ArrayDef;
import CCMModel.CCMModelFactory;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.FixedDef;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.Typed;
import CCMModel.WstringDef;
import CCMModel.impl.NodeImpl;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

/**
 * @author kinscher
 */
public class CreateModelCommand extends Command {
	
	// parent of the new model object
	protected Container container;
	
	// the new object
	protected Contained newObject;
	
	//the root module
	private ModuleDef rootModule;
	
	// type of the new object
	private Class type;
	
	protected List idlTypes=new LinkedList();
	
	protected String identifier="";
	protected String version="";

	
	protected CCMModelFactory factory=CCMModelManager.getFactory();
	
	/**
	 * Constructor of this command, 
	 */
	public CreateModelCommand(Class type) {
		super();
		this.type=type;
	}

	/**
	 * The execution of this command creates a new Contained
	 * (Simple or Collection)
	 */
	public void execute() {
		super.execute();
		newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	    if(! (container instanceof ModuleDef))
	    	container = (Container)container.getDefinedIn();
	    	
	    container.getContents().add(newObject);
	   
	}
	
	
	/**
	 * Redoes a previously made undo of this command
	 */
	public void redo() { 
		container.getContents().add(newObject);	
	}
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {
		container.getContents().remove(newObject);
	}

	
	protected void setIDLTyped(Typed typed,IDLTemplate idlTemplate){
	    switch(idlTemplate.getIdlKind().getValue()){
	    case IDLKind.IDL:
	        typed.setIDLType((IDLType)idlTypes.get(idlTemplate.getIndexOfIDLType()));
	    	break;
	    case IDLKind.WSTRING:
	        WstringDef wstring=factory.createWstringDef();
	    	wstring.setBound(idlTemplate.getBound());
	    	getRootModule().getCCM().getIdlContainer().getWstrings().add(wstring);
	    	typed.setIDLType(wstring);
	    	break;
	    case IDLKind.ARRAY:
	        ArrayDef arr=factory.createArrayDef();
    		arr.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getArrays().add(arr);
    		typed.setIDLType(arr);
    		break;
	    case IDLKind.STRING:
	        StringDef string=factory.createStringDef();
    		string.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getStrings().add(string);
    		typed.setIDLType(string);
    		break;
	    case IDLKind.FIXED:
	        FixedDef fixed=factory.createFixedDef();
    		fixed.setDigits((new Integer(idlTemplate.getDigits())).shortValue());
    		fixed.setScale((new Integer(idlTemplate.getScale())).shortValue());
    		getRootModule().getCCM().getIdlContainer().getFixeds().add(fixed);
    		typed.setIDLType(fixed);
    		break;
	    case IDLKind.SEQUENCE:
	        SequenceDef seq=factory.createSequenceDef();
    		seq.setBound(idlTemplate.getBound());
    		getRootModule().getCCM().getIdlContainer().getSequences().add(seq);
    		typed.setIDLType(seq);
	    }
	}
	
	protected void unSetIDLTyped(Typed typed,IDLTemplate idlTemplate){
	    switch(idlTemplate.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	    	getRootModule().getCCM().getIdlContainer().getWstrings().remove(typed.getIDLType());
	    	break;
	    case IDLKind.ARRAY:
    		getRootModule().getCCM().getIdlContainer().getArrays().remove(typed.getIDLType());
    		break;
	    case IDLKind.STRING:
    		getRootModule().getCCM().getIdlContainer().getStrings().remove(typed.getIDLType());
    		break;
	    case IDLKind.FIXED:
    		getRootModule().getCCM().getIdlContainer().getFixeds().remove(typed.getIDLType());
    		break;
	    case IDLKind.SEQUENCE:
    		getRootModule().getCCM().getIdlContainer().getSequences().remove(typed.getIDLType());
	    }
	    typed.setIDLType(null);
	}
	
	/**
	 * @param newObject The modelObject to set.
	 */
	public void setNewObject(Contained modelObj) {
		this.newObject = modelObj;
	}

	/**
	 * @param modelParent The modelParent to set.
	 */
	public void setContainer(Container container) {
		this.container = container;
	}

	  /**
     * @return Returns the idlTypes.
     */
    public List getIDLTypesName() {
        ModelFactory mf=new ModelFactory();
        setIdlTypes(mf.getIDLTypes(getRootModule()));
		return mf.getIDLTTypedNames(idlTypes);
		}

    /**
     * @return Returns the repositoryId.
     */
    public String getAbsoluteName() {    
		if(container.getAbsoluteName().trim().length()!=0)
		    return container.getAbsoluteName() + ":" + container.getIdentifier();
		else
		    return container.getIdentifier();
    }

    /**
     * @return Returns the version.
     */
    public String getVersion() {
        return container.getVersion();
    }
    /**
     * @param version The version to set.
     */
    public void setVersion(String version) {
        this.version = version;
    }
    /**
     * @param identifier The identifier to set.
     */
    public void setIdentifier(String identifier) {
        this.identifier = identifier;
    }
    /**
     * @return Returns the rootModule.
     */
    public ModuleDef getRootModule() {
        return (ModuleDef)container;
    }
    /**
     * @param rootModule The rootModule to set.
     */
    public void setRootModule(ModuleDef rootModule) {
        this.rootModule = rootModule;
    }
    /**
     * @param idlTypes The idlTypes to set.
     */
    public void setIdlTypes(List idlTypes) {
        this.idlTypes.clear();
        this.idlTypes.addAll(idlTypes);
    }
}
