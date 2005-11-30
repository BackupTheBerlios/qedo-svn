package ccmio.repository;

import java.io.FileInputStream;
import java.io.IOException;

import org.omg.CORBA.COMM_FAILURE;
import org.omg.CORBA.ORB;

import M2C.MOFRepository.MofRepositoryException;
import M2C.MOFRepository.RepositoryRoot;
import M2C.MOFRepository.RepositoryRootHelper;
import MDE.CCMPackageFactory;
import MDE.CCMPackageFactoryHelper;
import MDE._CCMPackage;
import MDE._CCMPackageHelper;
import Reflective.MofError;
import Reflective.RefPackageFactory;
import Reflective._RefPackage;
import Reflective.RefPackageFactorySetHelper;

/**
 *	This Class represent a repository import from a ccmrepository to a ccm-model-file:
 *
 * 	To connect to a repository:
 * 		repository = new CCMRepository("RepositoryRoot.ref - filename");
 */
public class CCMRepository {
	/**
	 * Referenz to the MDE-Package of the repository.
	 */
	private _CCMPackage mdepackage;
	/**
	 * returns the MDE-Package of the repository.
	 * @return the MDE-Package of the repository.
	 */
	public _CCMPackage getMDE()
	{
		return mdepackage;
	}
	/**
	 * Construktor of the CCMRepository.
	 * @param refRepRootFile = the RepositoryRoot.ref - file
	 */
	public CCMRepository(String	refRepRootFile) throws MofError,IOException,COMM_FAILURE{
        boolean packageinRepository=false;
		// init ORB:
		ORB orb = ORB.init(new String[]{},null);
		
		// get Repository-Reference from RepositoryRoot.ref-File
		String refRepRoot =	getRefFromFile(refRepRootFile);

		// cast Repository-Reference-String to CORBA.Object
		org.omg.CORBA.Object repository = orb.string_to_object(refRepRoot);

		// get Repository-Root
		RepositoryRoot repositoryRoot = RepositoryRootHelper.narrow(repository);
		try{	
			//RefPackageFactorySet_var packageFactory = RefPackageFactorySetHelper.narrow( repositoryRoot.get_root_package_factories());
			CCMPackageFactory packageFactory= null;
			RefPackageFactory[] refPkgFactories=repositoryRoot.get_root_package_factories();
			for (int i = 0 ;i<refPkgFactories.length;i++){
				 try{
					packageFactory = CCMPackageFactoryHelper.narrow(refPkgFactories[i]);
				    break;
				 }catch (Exception e){}
					 
			}
		
			_RefPackage[] packages = repositoryRoot.list_root_packages();
			for (int i = 0 ;i<packages.length;i++){
				 try{
				 	mdepackage = _CCMPackageHelper.narrow(packages[i]);
				 	packageinRepository= true;
			     }catch (Exception e){}
			}
			if (!packageinRepository)
				mdepackage = packageFactory.create_ccm_package();		 
			
	}catch( MofRepositoryException e1){
		e1.printStackTrace();
		
	}
		
	}
	/**
	 * gets the reference from the .ref - file.
	 * @param file = full path of the .ref - file
	 */
	private static String getRefFromFile(String file) throws IOException
	{
		FileInputStream fileInputStream = new FileInputStream(file);
		StringBuffer ret = new StringBuffer();
		int c; 
		
		while ((c = fileInputStream.read()) != -1)
			ret.append(new String(new byte[] {(byte) c}));
		
		fileInputStream.close();
		return ret.toString();
	}
}
