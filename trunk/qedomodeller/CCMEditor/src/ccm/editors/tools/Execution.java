/**
 * Created on 04.03.2005
 *

 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.editors.tools;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Shell;

import CCMModel.ComponentDef;
import CCMModel.HomeDef;
import CCMModel.IDLType;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
import CCMModel.WstringDef;

import ccm.CCMConstants;
import ccm.commands.create.model.CreateAliasDefCommand;
import ccm.commands.create.model.CreateComponentDefCommand;
import ccm.commands.create.model.CreateComponentImplDefCommand;
import ccm.commands.create.model.CreateCompositionDefCommand;
import ccm.commands.create.model.CreateConstantDefCommand;
import ccm.commands.create.model.CreateEnumDefCommand;
import ccm.commands.create.model.CreateEventDefCommand;
import ccm.commands.create.model.CreateExceptionDefCommand;
import ccm.commands.create.model.CreateHomeDefCommand;
import ccm.commands.create.model.CreateHomeImplDefCommand;
import ccm.commands.create.model.CreateInterfaceDefCommand;
import ccm.commands.create.model.CreateModuleDefCommand;
import ccm.commands.create.model.CreateStructDefCommand;
import ccm.commands.create.model.CreateUnionDefCommand;
import ccm.commands.create.model.CreateValueBoxDefCommand;
import ccm.commands.create.model.CreateValueDefCommand;
import ccm.commands.create.visual.CreateDiagramCommand;
import ccm.commands.create.visual.CreateNodeForAliasDefCommand;
import ccm.commands.create.visual.CreateNodeForAssemblyCommand;
import ccm.commands.create.visual.CreateNodeForComponentDefCommand;
import ccm.commands.create.visual.CreateNodeForComponentImplCommand;
import ccm.commands.create.visual.CreateNodeForCompositionCommand;
import ccm.commands.create.visual.CreateNodeForConstantDefCommand;
import ccm.commands.create.visual.CreateNodeForDeploymentUnitCommand;
import ccm.commands.create.visual.CreateNodeForEnumDefCommand;
import ccm.commands.create.visual.CreateNodeForExceptionDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeImplCommand;
import ccm.commands.create.visual.CreateNodeForInterfaceDefCommand;
import ccm.commands.create.visual.CreateNodeForModuleDefCommand;
import ccm.commands.create.visual.CreateNodeForSoftwarePackageCommand;
import ccm.commands.create.visual.CreateNodeForStructDefCommand;
import ccm.commands.create.visual.CreateNodeForUnionDefCommand;
import ccm.commands.create.visual.CreateNodeForValueBoxDefCommand;
import ccm.commands.create.visual.CreateNodeForValueDefCommand;
import ccm.commands.create.visual.adds.AddAliasDefCommand;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddConstantDefCommand;
import ccm.commands.create.visual.adds.AddEmitsSourceCommand;
import ccm.commands.create.visual.adds.AddEnumDefCommand;
import ccm.commands.create.visual.adds.AddEventSinkCommand;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.commands.create.visual.adds.AddExceptionDefCommand;
import ccm.commands.create.visual.adds.AddFacetCommand;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.create.visual.adds.AddReceptacleCommand;
import ccm.commands.create.visual.adds.AddStructDefCommand;
import ccm.commands.create.visual.adds.AddUnionDefCommand;
import ccm.commands.create.visual.adds.AddValueBoxDefCommand;
import ccm.commands.create.visual.adds.AddValueMemberDefCommand;
import ccm.commands.dnd.AddModel2DiagramCommand;
import ccm.commands.edit.EditOperationCommand;
import ccm.dialogs.AddOperationDialog;
import ccm.dialogs.AddPortDialog;
import ccm.dialogs.AddReceptacleDialog;
import ccm.dialogs.CreateAbstractInterfaceDefDialog;
import ccm.dialogs.CreateAssemblyDialog;
import ccm.dialogs.CreateAttributeDefDialog;
import ccm.dialogs.CreateComponentImplDialog;
import ccm.dialogs.CreateCompositionDialog;
import ccm.dialogs.CreateConstantDefDialog;
import ccm.dialogs.CreateContainedDialog;
import ccm.dialogs.CreateSoftwarePackageUnitDialog;
import ccm.dialogs.CreateDiagramDialog;
import ccm.dialogs.CreateEnumDefDialog;
import ccm.dialogs.CreateExceptionDefDialog;
import ccm.dialogs.CreateHomeImplDialog;
import ccm.dialogs.CreateModuleDefDialog;
import ccm.dialogs.CreateStructDefDialog;
import ccm.dialogs.CreateUnionDefDialog;
import ccm.dialogs.CreateValueBoxOrAliasDefDialog;
import ccm.dialogs.CreateValueDefDialog;
import ccm.dialogs.CreateValueMemberDefDialog;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class Execution {
    
	public boolean canExecute(CreateNodeForSoftwarePackageCommand command,Shell shell){
		CreateSoftwarePackageUnitDialog createDialog=new CreateSoftwarePackageUnitDialog(shell,SWT.NULL);
	 	//ComponentDef component=command.getComponent();
	 	createDialog.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
	    createDialog.setVersion(command.getVersion());
	   // createDialog.setDiscription("Add ComponentImpl for component "+component.getIdentifier());
	    createDialog.open();
        if(!createDialog.isState() )
        	return false;
        command.setVersion(createDialog.getVersion());
        command.setIdentifier(createDialog.getIdentifier());
        command.setLicenseKey(createDialog.getLicenseKey());
        command.setLicenseTextRef(createDialog.getLicenseTxtRef());
    //    command.setUUID(createDialog.getUUID());
        
		return true;
	}
	public boolean canExecute(CreateNodeForDeploymentUnitCommand command,Shell shell){
		CreateAssemblyDialog createDialog=new CreateAssemblyDialog(shell,SWT.NULL);
	 	//ComponentDef component=command.getComponent();
	 	createDialog.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
	    createDialog.setVersion(command.getVersion());
	    createDialog.setDiscription("Add Implementation");
	   // createDialog.setDiscription("Add ComponentImpl for component "+component.getIdentifier());
	    createDialog.open();
        if(!createDialog.isState() )
        	return false;
        command.setVersion(createDialog.getVersion());
        command.setIdentifier(createDialog.getIdentifier());
      //  command.setLicenseKey(createDialog.getLicenseKey());
      //  command.setLicenseTextRef(createDialog.getLicenseTxtRef());
        command.setUUID(createDialog.getUUID());
        
        return true; 
    }
	public boolean canExecute(CreateNodeForAssemblyCommand command,Shell shell){
		CreateAssemblyDialog createDialog=new CreateAssemblyDialog(shell,SWT.NULL);
	 	//ComponentDef component=command.getComponent();
	 	createDialog.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
	    createDialog.setVersion(command.getVersion());
	   // createDialog.setDiscription("Add ComponentImpl for component "+component.getIdentifier());
	    createDialog.open();
        if(!createDialog.isState() )
        	return false;
        command.setIdentifier(createDialog.getIdentifier());
        command.setVersion(createDialog.getVersion());
        command.setUUID(createDialog.getUUID());
        return true; 
    }
    public boolean canExecute(AddFacetCommand command,Shell shell){
    	AddPortDialog d=new AddPortDialog(shell, 0, "Add Facet");
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        return true;  
    }
    
    public boolean canExecute(AddReceptacleCommand command,Shell shell){
    	AddReceptacleDialog d=new AddReceptacleDialog(shell, 0, "Add Receptacle");
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMultipleItf(d.isMultipleItf());
        return true;  
    }
    
    public boolean canExecute(AddEventSinkCommand command,Shell shell){
    	AddPortDialog d=new AddPortDialog(shell, 0, "Add Event Sink");
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        return true;  
    }
    
    public boolean canExecute(AddEventSourceCommand command,Shell shell){
    	AddPortDialog d=new AddPortDialog(shell, 0, "Add Event Source");
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        return true;  
    }
    
    public boolean canExecute(AddEmitsSourceCommand command,Shell shell){
    	AddPortDialog d=new AddPortDialog(shell, 0, "Add Emits Source");
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        return true;  
    }
     public boolean canExecute(AddOperationDefCommand command,Shell shell){
        AddOperationDialog d=new AddOperationDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setContext(d.getContext());
        command.setVersion(d.getVersion());
        command.setParameters(d.getPameterList());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(CreateNodeForExceptionDefCommand command,Shell shell){
        CreateExceptionDefDialog d=new CreateExceptionDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setTypeCode(d.getTypeCode());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    public boolean canExecute(AddExceptionDefCommand command,Shell shell){
        CreateExceptionDefDialog d=new CreateExceptionDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setTypeCode(d.getTypeCode());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    public boolean canExecute(CreateNodeForUnionDefCommand command,Shell shell){
        CreateUnionDefDialog d=new CreateUnionDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setUnionMembers(d.getMemberList());
        command.setDiscrType(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(AddUnionDefCommand command,Shell shell){
        CreateUnionDefDialog d=new CreateUnionDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setUnionMembers(d.getMemberList());
        command.setDiscrType(d.getIdlTemp());
        return true;  
    }
    public boolean canExecute(CreateNodeForStructDefCommand command,Shell shell){
        CreateStructDefDialog d=new CreateStructDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    public boolean canExecute(AddStructDefCommand command,Shell shell){
        CreateStructDefDialog d=new CreateStructDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    public boolean canExecute(CreateNodeForEnumDefCommand command,Shell shell){
        CreateEnumDefDialog d=new CreateEnumDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    
    public boolean canExecute(AddEnumDefCommand command,Shell shell){
        CreateEnumDefDialog d=new CreateEnumDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    public boolean canExecute(CreateNodeForValueBoxDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add ValueBox");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.setDiscription("Add value box");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
    public boolean canExecute(AddValueBoxDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add ValueBox");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.setDiscription("Add value box");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
    public boolean canExecute(CreateNodeForAliasDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add Alias");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.setDiscription("Add alias");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
    public boolean canExecute(AddAliasDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add Alias");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.setDiscription("Add alias");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
    public boolean canExecute(CreateNodeForConstantDefCommand command,Shell shell){
        CreateConstantDefDialog d=new CreateConstantDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setConstValue(d.getConstValue());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(AddConstantDefCommand command,Shell shell){
        CreateConstantDefDialog d=new CreateConstantDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setConstValue(d.getConstValue());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(AddAttributeDefCommand command,Shell shell){
        CreateAttributeDefDialog d=new CreateAttributeDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setReadonly(d.isReadonly());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(AddValueMemberDefCommand command,Shell shell){
        CreateValueMemberDefDialog d=new CreateValueMemberDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setPublicMember(d.isPublicMember());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
    
    public boolean canExecute(CreateNodeForModuleDefCommand command,Shell shell){
        CreateModuleDefDialog d=new CreateModuleDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setPrefix(d.getPrefix());
        command.setVersion(d.getVersion());
        return true;  
    }
    
    public boolean canExecute(CreateNodeForHomeDefCommand command,Shell shell){
        CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDiscription("Add Home");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setLocal(d.isLocal());
        return true;  
    }
    
    public boolean canExecute(CreateNodeForInterfaceDefCommand command,Shell shell){
        CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDiscription("Add Interface");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setLocal(d.isLocal());
        return true;  
    }
    public boolean canExecute(CreateNodeForValueDefCommand command,Shell shell){
        CreateValueDefDialog d=new CreateValueDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        if(command.isEvent)
        	d.setDescription("Add Event");
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setCustom(d.isCustom());
        command.setTruncat(d.isTruncatable());
        return true;  
    }
    
    public boolean canExecute(CreateNodeForComponentDefCommand command,Shell shell){
        CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDiscription("Add Component");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setLocal(d.isLocal());
        return true;  
    }
    
    public boolean canExecute(CreateDiagramCommand command,Shell shell){
    	CreateDiagramDialog d=new CreateDiagramDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        //d.setDiscription("Add Diagram");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        return true;  
    }
    
    public boolean canExecute(CreateComponentDefCommand command,Shell shell){
    	 CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
         d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
         d.setVersion(command.getVersion());
         d.setDiscription("Add Component");
         d.open();
         if(!d.isState())return false;
         command.setIdentifier(d.getIdentifier());
         command.setVersion(d.getVersion());
         command.setAbstract(d.isAbstract());
         command.setLocal(d.isLocal());
         return true;  
    }
    
    public boolean canExecute(CreateModuleDefCommand command,Shell shell){
        CreateModuleDefDialog d=new CreateModuleDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setPrefix(d.getPrefix());
        command.setVersion(d.getVersion());
        return true;  
    }
    
    public boolean canExecute(CreateValueDefCommand command,Shell shell){
        CreateValueDefDialog d=new CreateValueDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setCustom(d.isCustom());
        command.setTruncatable(d.isTruncatable());
        return true;  
    }
    
    public boolean canExecute(CreateExceptionDefCommand command,Shell shell){
        CreateExceptionDefDialog d=new CreateExceptionDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setTypeCode(d.getTypeCode());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
    
    public boolean canExecute(CreateEventDefCommand command,Shell shell){
        CreateValueDefDialog d=new CreateValueDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDescription( "Add Event");
        //d.setDescription("Add Event");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setCustom(d.isCustom());
        command.setTruncatable(d.isTruncatable());
        return true;  
    }
    
    public boolean canExecute(CreateInterfaceDefCommand command,Shell shell){
        CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDiscription("Add Interface");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setLocal(d.isLocal());
        return true;  
    }
  
    public boolean canExecute(CreateHomeDefCommand command,Shell shell){
        CreateAbstractInterfaceDefDialog d=new CreateAbstractInterfaceDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setDiscription("Add Home");
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setAbstract(d.isAbstract());
        command.setLocal(d.isLocal());
        return true;  
    }

	public boolean canExecute(CreateConstantDefCommand command,Shell shell){
        CreateConstantDefDialog d=new CreateConstantDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setConstValue(d.getConstValue());
        command.setIdlTemplate(d.getIdlTemp());
        return true;  
    }
	
    public boolean canExecute(CreateEnumDefCommand command,Shell shell){
        CreateEnumDefDialog d=new CreateEnumDefDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
	
    public boolean canExecute(CreateValueBoxDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add Value Box");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
       //d.setDiscription("Add value box");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
	
    public boolean canExecute(CreateAliasDefCommand command,Shell shell){
        CreateValueBoxOrAliasDefDialog d=new CreateValueBoxOrAliasDefDialog(shell, 0,"Add Alias");
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setIdlTList(command.getIDLTypesName());
        d.setVersion(command.getVersion());
       // d.setDiscription("Add Alias");
        d.setIdlTemplate(command.getIdlTemplate());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setIdlTemplate(d.getIdlTemplate());
        return true;  
    }
	
	public boolean canExecute(CreateStructDefCommand command,Shell shell){
        CreateStructDefDialog d=new CreateStructDefDialog(shell, 0);
        d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setMembers(d.getMemberList());
        return true;  
    }
	
	 public boolean canExecute(CreateUnionDefCommand command,Shell shell){
	        CreateUnionDefDialog d=new CreateUnionDefDialog(shell, 0);
	        d.setIdlTList(command.getIDLTypesName());
	        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
	        d.setVersion(command.getVersion());
	        d.open();
	        if(!d.isState())return false;
	        command.setIdentifier(d.getIdentifier());
	        command.setVersion(d.getVersion());
	        command.setUnionMembers(d.getMemberList());
	        command.setDiscrType(d.getIdlTemp());
	        return true;  
	    }
	 
	 
	 public boolean canExecute(CreateNodeForCompositionCommand command,Shell shell){
	 	CreateCompositionDialog d=new CreateCompositionDialog(shell, 0);
        //d.setIdlTList(command.getIDLTypesName());
    	
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());	
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setCategory(d.getCategory());
        //command.setRectangle(new Rectangle(location,new Dimension(90,50)));
       // command.setUnionMembers(d.getMemberList());
       // command.setDiscrType(d.getIdlTemp());
        return true;  
    }
	 public boolean canExecute(CreateCompositionDefCommand command,Shell shell){
	 	CreateCompositionDialog d=new CreateCompositionDialog(shell, 0);
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());	
        d.open();
        if(!d.isState())return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setCategory(d.getCategory());
       // command.setUnionMembers(d.getMemberList());
       // command.setDiscrType(d.getIdlTemp());
        return true;  
    }
	 public boolean canExecute(CreateNodeForComponentImplCommand command,Shell shell){
	 	CreateComponentImplDialog d=new CreateComponentImplDialog(shell, 0);
        //d.setIdlTList(command.getIDLTypesName()); 
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setComponents(command.getComponentDefs());
        d.open();
        if(!d.isState()||d.getComponent()==null)return false;
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
        command.setCategory(d.getCategory());
        command.setComponent(d.getComponent());
        
       // command.setUnionMembers(d.getMemberList());
       // command.setDiscrType(d.getIdlTemp());
        return true;  
    }
	 public boolean canExecute(CreateNodeForHomeImplCommand command,Shell shell){
	 	CreateHomeImplDialog d=new CreateHomeImplDialog(shell, 0);
        //d.setIdlTList(command.getIDLTypesName());
        d.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
        d.setVersion(command.getVersion());
        d.setHomes(command.getHomeDefs());
        d.open();
        if(!d.isState()||d.getHome()==null)return false;
        
        command.setIdentifier(d.getIdentifier());
        command.setVersion(d.getVersion());
         
        command.setHome(d.getHome());
       // command.setUnionMembers(d.getMemberList());
       // command.setDiscrType(d.getIdlTemp());
        return true;  
    }
	 public boolean canExecute(CreateHomeImplDefCommand command,Shell shell){
	 	CreateContainedDialog createDialog=new CreateContainedDialog(shell,SWT.NULL);
	 	HomeDef home=command.getHome();
	 	createDialog.setRepositoryId(home.getAbsoluteName(),"",home.getVersion());
	    createDialog.setVersion(home.getVersion());
	    createDialog.setDiscription("Add HomeImpl for Home "+home.getIdentifier());
	    createDialog.open();
        if(!createDialog.isState() )
        	return false;
        command.setIdentifier(createDialog.getIdentifier());
        command.setVersion(createDialog.getVersion());
      
        return true;  
    }
	 public boolean canExecute(CreateComponentImplDefCommand command,Shell shell){
	 	CreateContainedDialog createDialog=new CreateContainedDialog(shell,SWT.NULL);
	 	ComponentDef component=command.getComponent();
	 	createDialog.setRepositoryId(component.getAbsoluteName(),"",component.getVersion());
	    createDialog.setVersion(component.getVersion());
	    createDialog.setDiscription("Add ComponentImpl for component "+component.getIdentifier());
	    createDialog.open();
        if(!createDialog.isState() )
        	return false;
        command.setIdentifier(createDialog.getIdentifier());
        command.setVersion(createDialog.getVersion());
      
        return true; 
    }

	/**
	 * @param command
	 * @param shell
	 * @return
	 */
	public boolean canExecute(EditOperationCommand command, Shell shell) {
		// System.out.println("can excute: "+ command);
         OperationDef op =command.getOperationDef();
		 AddOperationDialog d=new AddOperationDialog(shell, 0);
	     d.setIdlTList(command.getIDLTypesName());
	     d.setRepositoryId("IDL:"+op.getAbsoluteName()+":",op.getIdentifier()+":",op.getVersion());
	     d.setVersion(op.getVersion());
	     d.setContext(op.getContext());
	     d.setIdentifier(op.getIdentifier());
	     List paraList = op.getParameters();
	     List paraTemList= new ArrayList();
	     for (Iterator it = paraList.iterator();it.hasNext();){
	        	ParameterDef para =(ParameterDef)it.next();
	        	ParameterMode paraMode=para.getDirection();
	        	String paraName=para.getIdentifier();
	        	IDLType paraType =para.getIDLType();
	        	IDLTemplate paraTypetemplate=CCMConstants.getIDLTemplate(paraType,command.getIDLTypes()); ;
	        	ParameterTemplate paraTem= new ParameterTemplate(paraName,paraMode,paraTypetemplate);
	        	paraTemList.add(paraTem);
	     }
	     d.setPameterList(paraTemList);
	     
	    // IDLTemplate template=IDLTemplate.getTemlateFromIDLType(op.getIDLType());
	     IDLTemplate template=CCMConstants.getIDLTemplate(op.getIDLType(),command.getIDLTypes()); 
	     d.setIdlTemp(template);
	     
	     d.open();
	     if(!d.isState())
	        	return false;
	         
	     command.setIdentifier(d.getIdentifier());
	     command.setContext(d.getContext());
	     command.setVersion(d.getVersion());
	     command.setParameters(d.getPameterList());
	     command.setIdlTemplate(d.getIdlTemp());
		 return true;
	}
}
