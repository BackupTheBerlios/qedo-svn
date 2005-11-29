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


package ccm.model;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IPath;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.XMIResource;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import CCMModel.CCM;
import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.impl.CCMModelPackageImpl;





/**
 * Drives the model. Acts as the model entry point.
 * @author eduardw
 *
 */
public class CCMModelManager {
	/**
	 * For the purpose of the simple editor, a file can only contain a workflow.
	 * In EMF, a resource provides the way to have access to the model content.
	 */
	public  Resource resource = null;

	/**
	 * Contains the factory associated with the model.
	 */
	private static CCMModelFactory ccmFactory = null;
	
	/**
	 * Gives access to the top level workflow contained in the resource.
	 */
	private CCM ccm = null;
	
	private String version;

	private InitilizeModel initm=null;
	/**
	 * Returns the resource containing the workflow. Uses lazy initialization.
	 * @param path
	 * @return
	 */
	public Resource getResource(IPath path) {
		if (resource == null) {
			ResourceSet resSet = getResourceSet();
			resource =
				resSet.getResource(
					URI.createPlatformResourceURI(path.toString()),
					true);
		}
		return resource;
	}

	/**
	 * Returns the resource containing the workflow. Throw a runtime exception 
	 * if the resource does not exist.
	 * @param path
	 * @return
	 */
	public Resource getResource() {
		if (resource == null) {
			throw new RuntimeException("Ressource supposed to be already created");
		}
		return resource;
	}
	
	private void loadVersionAndRepID(IPath path){
	    IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IResource res = root.findMember(path);
	    IFile f=(IFile) res;
	    try {
            BufferedReader d= new BufferedReader(new InputStreamReader(((IFile) res).getContents()));
            int bytein;
            StringBuffer strbuff=new StringBuffer(100);
            while((bytein=d.read())!=-1){
                strbuff.append((char)bytein);
            }
            version=strbuff.toString().trim();
            d.close();
        }catch (CoreException e) {}catch (IOException e1) {}
	}

	/**
	 * Creates a resource to contain the workflow. The resource file does not exist yet.
	 * @param path
	 * @return
	 */
	private Resource createResource(IPath path) {
		if (resource == null) {
			ResourceSet resSet = getResourceSet();
			resource =
				resSet.createResource(URI.createPlatformResourceURI(path.toString()));
		}
		return resource;
	}

	/**
	 * Returns the resource set.
	 * @param 
	 * @return
	 */
	private ResourceSet getResourceSet() {
		// Initialize the NavExpression package
		CCMModelPackageImpl.init();
		// Register the XMI resource factory for the .ocl extension
		Resource.Factory.Registry reg = Resource.Factory.Registry.INSTANCE;
		Map m = reg.getExtensionToFactoryMap();
		m.put("ccm", new XMIResourceFactoryImpl());
		// Obtain a new resource set
		return new ResourceSetImpl();
	}

	/**
	 * Returns the factory associated with the model.
	 * Object creation are made through that factory.
	 * @return
	 */
	static public CCMModelFactory getFactory() {
		if (ccmFactory == null) {
			// Access the factory (needed to create instances)
			Map registry = EPackage.Registry.INSTANCE;
			String ccmURI = CCMModelPackage.eNS_URI;
			CCMModelPackage ccmPackage =
				(CCMModelPackage) registry.get(ccmURI);
			ccmFactory = ccmPackage.getCCMModelFactory();
		}
		return ccmFactory;
	}

	/**
	 * Creates a new navexpression.
	 * @param 
	 * @return
	 */
	public CCM createModelView(IFile file) {
		IPath path=file.getFullPath();
		String filename=file.getName().trim();
		String rootName=filename.substring(0,filename.length()-4);
		 
		createResource(path);
	    loadVersionAndRepID(path);
		// Create a new NavExp model
		Map registry = EPackage.Registry.INSTANCE;
		String navURI = CCMModelPackage.eNS_URI;
		CCMModelPackage ccmPackage = (CCMModelPackage) registry.get(navURI);
		ccmFactory = ccmPackage.getCCMModelFactory();
		ccm = ccmFactory.createCCM();
		initm=new InitilizeModel(ccm,version);
		initm.createRootModule(ccmFactory,rootName);
		initm.initType(ccmFactory);
		EList list=resource.getContents();
		list.add(ccm);
		return ccm;
	}
	
	/**
	 * Loads the content of the model from the file.
	 * @param path
	 */
	public void load(IPath path) throws IOException {
		getResource(path);
		Map options = new HashMap();
		options.put(XMIResource.OPTION_DECLARE_XML, Boolean.TRUE);
		resource.load(options);
	}

    /**
     * reloads the content of the model from the file.
     * @param path
     */
    public void reload(IPath path) throws IOException {
        getResource(path).unload();
        load(path);
    }

	/**
	 * Saves the content of the model to the file.
	 * @param path
	 */
	public void save(IPath path) throws IOException {
		// Nothing is done of the path if the resource already exist...
		// Not really what we would expect, but ok for the NavExpression application.
		// A second save() method with no argument should be added.
		getResource(path);
		Map options = new HashMap();
		options.put(XMIResource.OPTION_DECLARE_XML, Boolean.TRUE);
		//resource.save(options);
	    resource.save(options);
	}

	/**
	 * Gets the top level navexpression model.
	 * @return
	 */
	public CCM getModel() {
		if (null == ccm) {
			EList l = resource.getContents();
			Iterator i = l.iterator();
			while (i.hasNext()) {
				Object o = i.next();
				if (o instanceof CCM)
				ccm = (CCM) o;
			}
		}
		return ccm;
	}
	
}
