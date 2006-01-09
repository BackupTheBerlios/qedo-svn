package ccm.property;

import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.SoftwarePackage;
 

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class SoftwarePackagePropertySource extends ContainedPropertySource {

    
  //  private String[] values=new String[]{"false","true"};
    
    protected SoftwarePackage abstObj;
   // private List absItfs ;
   // private List allItfs;
   // private String[]absItfNames;
   // private ModelFactory mf=new ModelFactory();
    // private CCMModelFactory factory =CCMModelManager.getFactory();
   // protected ModuleDef root;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public SoftwarePackagePropertySource(Contained element) {
        	super(element);
        	abstObj=(SoftwarePackage) element;
        	//root= mf.getRootModule(abstObj);
        	//allItfs= new ArrayList(mf.getAllContained(root,InterfaceDef.class));
        	 
          
         	    
        	//absItfs= mf.getAllContained(root,AbstractInterfaceDef.class);
        	//absItfs.remove(abstObj);
        	//int size=absItfs.size();
        	//homeImpls=new HomeImplDef[size];
        	//homeImplNames= new String[size+1];
        	//homeImplNames[0]="none";
        	
        	//for (int i=0 ;i<size;i++){
        		//homeImpls[i]=(HomeImplDef)homeImplList.get(i);
        		//homeImplNames[i+1]=((HomeImplDef)homeImplList.get(i)).getIdentifier();
        		 
        	//}
        	
    }
	
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
     */
    public IPropertyDescriptor[] getPropertyDescriptors() {
    	 propertyDescriptors=super.getPropertyDescriptors();
         Collection	descriptors = new Vector();
        
         for(int i=0;i<propertyDescriptors.length;i++){
             descriptors.add(propertyDescriptors[i]);
         }
         
    	String cat="local";
   		//if(object!=null)cat=cat+ object.eClass().getName();
        
         // Create a descriptor and set a category
    	PropertyDescriptor licensekey = new TextPropertyDescriptor(Integer.toString(100), "licensekey");
    	licensekey.setCategory(cat);
        descriptors.add(licensekey);
        
        PropertyDescriptor licenseTxtRef = new TextPropertyDescriptor(Integer.toString(101), "licenseTxtRef");
        licenseTxtRef.setCategory(cat);
        descriptors.add(licenseTxtRef);
        PropertyDescriptor tiltel = new TextPropertyDescriptor(Integer.toString(102), "tiltel");
        tiltel.setCategory(cat);
      	descriptors.add(tiltel);
      	PropertyDescriptor autor = new TextPropertyDescriptor(Integer.toString(103), "autor");
      	autor.setCategory(cat);
      	descriptors.add(autor);
      	PropertyDescriptor type = new TextPropertyDescriptor(Integer.toString(104), "type");
      	type.setCategory(cat);
      	descriptors.add(type);
      	PropertyDescriptor idlFile = new PropertyDescriptor(Integer.toString(105), "idlFile");
      	idlFile.setCategory(cat);
      	descriptors.add(idlFile);
      	 
        
        
        cat="links";
        // Create a descriptor and set a category
       
       PropertyDescriptor derived = new  PropertyDescriptor(
            Integer.toString(106),
               "realized component " );
       derived.setCategory(cat);
       descriptors.add(derived);
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	List Interfaces;
    	int size;
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       return abstObj.getLicensekey();
	    case 101:
	    	 return abstObj.getLicensetextref();   
	   
	    case 102:
	    	 return abstObj.getTitle();
	    case 103:
	    	 return abstObj.getAutor();
	    case 104:
	    	 return abstObj.getType();
	    case 105:
	    	if(abstObj.getIdlFile()!=null)
	    	 return abstObj.getIdlFile().getIdentifier();
	    	else return "";
	    case 106:
	    	 return abstObj.getComponent().getIdentifier();
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       abstObj.setLicensekey((String)value);
	    	 
	    	break;
	    case 101:     
	    	 abstObj.setLicensetextref((String)value);
    		break;
	    case 102:     
	    	 abstObj.setTitle((String)value);
    		break;
	    case 103:     
	    	 abstObj.setAutor((String)value);
   		break;
	    case 104:     
	    	 abstObj.setType((String)value);
   		break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
