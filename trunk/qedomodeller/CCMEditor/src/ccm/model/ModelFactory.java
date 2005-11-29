/**
 * Created on 18.01.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model;


import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.IFigure;

import CCMModel.AliasDef;
import CCMModel.ComponentDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.EmitsDef;
import CCMModel.EnumDef;
import CCMModel.HomeDef;
import CCMModel.IDLTypeContainer;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.PrimitiveDef;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.UsesDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import ccm.figures.EmitsSourceLabel;
import ccm.figures.EventSinkLabel;
import ccm.figures.EventSourceLabel;
import ccm.figures.FacetLabel;
import ccm.figures.ReceptacleLabel;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ModelFactory {
	
	public IFigure getFigure(Object obj){
		if(obj==null) return new Figure();
		return setType(obj,null);
	}
	
	public IFigure setType(Object obj,IFigure fig){
	    if(obj instanceof ProvidesDef){
			if(fig==null)fig=new FacetLabel();
			((FacetLabel) fig).setText(((ProvidesDef)obj).getIdentifier());
			return fig;
		}else if(obj instanceof UsesDef){
			if(fig==null)fig=new ReceptacleLabel();
			((ReceptacleLabel) fig).setText(((UsesDef)obj).getIdentifier());
			return fig;
		}else if(obj instanceof PublishesDef){
			if(fig==null)fig=new EventSourceLabel();
			((EventSourceLabel) fig).setText(((PublishesDef)obj).getIdentifier());
			return fig;
		}
		else if(obj instanceof ConsumesDef){
			if(fig==null)fig=new EventSinkLabel();
			((EventSinkLabel) fig).setText(((ConsumesDef)obj).getIdentifier());
			return fig;
		}
		else if(obj instanceof EmitsDef){
			if(fig==null)fig=new EmitsSourceLabel();
			((EmitsSourceLabel) fig).setText(((EmitsDef)obj).getIdentifier());
			return fig;
		}
		return null;

	}
	
	public ModuleDef getRootModule(Contained contained){
	    ModuleDef root=null;
	    ModuleDef module=null;
	    Contained con=contained;
	    while(root==null){
	        if(con instanceof ModuleDef){
	            module=(ModuleDef)con;
	            if(module.getDefinedIn() == null)
	                root=module;
	            else con=con.getDefinedIn();
	        }else{
	            con=con.getDefinedIn(); 
	        }
	    }	    
	    return root;
	}
	
	public  List getAllContained(Contained contained, Class type){
		
		ModuleDef root=getRootModule(contained);
		return getAllContained(root,type);
		
	}
	public List getAllContained(ModuleDef root, Class type){
		List contents=root.getContents();
		List containeds=new ArrayList();
    	for (Iterator it= contents.iterator();it.hasNext();){
    	  Object o= it.next();
    	  if (  type.isInstance(o))
    	  	containeds.add(o);
    	  if (o instanceof ModuleDef)
    	  	containeds.addAll(getAllContained((ModuleDef)o,type));
    	  
    	}
     
    	return containeds;
		
	}
	public List getAllViews(ModuleDef root ){
		List contents=root.getContents();
		List views=root.getView();
    	for (Iterator it= contents.iterator();it.hasNext();){
    	  Object o= it.next();
    	   
    	  if (o instanceof ModuleDef)
    	  	views.addAll(getAllViews((ModuleDef)o ));
    	  
    	}
     
    	return views;
		
	}
	public List getIDLTypes(Contained contained){
	    List list=new LinkedList();
	    ModuleDef root=getRootModule(contained);	    
	    IDLTypeContainer idlContainer=root.getCCM().getIdlContainer();
	    list.addAll(idlContainer.getPrimitiveTypes());
	    list.addAll(getIDLFromModuleDef(root));
	    return list;
	}
	
	private List getIDLFromModuleDef(Container m){
	    List list=new LinkedList();
	    Iterator it=m.getContents().iterator();
	    while(it.hasNext()){
	        Contained con=(Contained) it.next();
	        if(con instanceof ComponentDef ||
	           con instanceof HomeDef ||
	           con instanceof UnionDef ||
	           con instanceof StructDef ||
	           con instanceof EnumDef ||
	           con instanceof AliasDef ||
	           con instanceof ValueBoxDef ||
	           con instanceof ValueDef){
	            list.add(con);
	        }else if(con instanceof InterfaceDef){
	            list.add(con);
	            InterfaceDef itf=(InterfaceDef) con;
	            list.addAll(getIDLFromModuleDef(itf));
	        }else if(con instanceof ModuleDef){
	            ModuleDef md=(ModuleDef) con;
	            list.addAll(getIDLFromModuleDef(md));
	        }
	    }
	    return list;
	}
	
	public List getIDLTypesNames(Contained contained){
	    return getIDLTTypedNames(getIDLTypes(contained));
	}
	
	public List getIDLTTypedNames(List idlList){
	    List nameList=new LinkedList();
	    Iterator it=idlList.iterator();
	    while(it.hasNext()){
	        Object o=it.next();
	        if(o instanceof PrimitiveDef){
	            PrimitiveDef idl=(PrimitiveDef)o;
	            nameList.add(idl.getKind().getName().substring(3));   
	        }else{
	            Contained idl=(Contained) o;
	            String name=idl.getAbsoluteName()+":"+idl.getIdentifier();
	            nameList.add(name);
	        }
	    }
	    return nameList;
	}
	
}
